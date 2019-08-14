/*
 * Problem inf20-2: from_blackav/server-1
 * В аргументах командной строки задаётся номер порта PORT. Программа должна слушать входящие TCP-соединения на порту PORT. 
 * Предполагается, что клиенты подключаются к серверу последовательно, то есть не требуется взаимодействовать с несколькими клиентами одновременно.
 * 
 * После подключения каждый клиент посылает на сервер знаковое 32-битное целое число в бинарном виде в сетевом порядке байт и закрывает соединение. Последний клиент посылает на сервер число 0.
 * 
 * После обработки всех клиентов, то есть после закрытия соединения от клиента, который передал число 0, сервер печатает сумму всех чисел на стандартный поток вывода и завершает работу.
 * 
 * Гарантируется, что все результаты операций представимы 32-битным целым типом.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include <inttypes.h>


void handle_pipe () {
	_exit(0);
}

int main(int argc, char const *argv[]) 
{ 
	if(argc != 2) {
		fprintf(stderr, "args\n");
		fflush(stderr);
		exit(1);
	}

	struct sigaction action_pipe;
	memset(&action_pipe, 0, sizeof(action_pipe));
	action_pipe.sa_handler = handle_pipe;
	action_pipe.sa_flags = SA_RESTART;
	sigaction(SIGPIPE, &action_pipe, NULL);
	
	int PORT = atoi(argv[1]);
    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
       
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    
    int32_t value = 1;
    int32_t summary = 0;
    while(value != 0) {
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
		{ 
			perror("accept"); 
			exit(EXIT_FAILURE); 
		}		
		if(read(new_socket, &value, sizeof(value)) <= 0) {
			exit(EXIT_FAILURE);
		}
		fsync(new_socket);	
		value = ntohl(value);
	
		summary += value;
		close(new_socket);
	}
	printf("%" PRId32 "\n", summary);
	fflush(stdout);
	
	close(server_fd);
    return 0; 
} 
