/*
 * Problem inf20-3: from_blackav/server-2
 * В аргументах командной строки задается номер порта PORT и некоторый строковый параметр KEY. 
 * Программа должна слушать входящие TCP-соединения на порту PORT. 
 * Для каждого подключающегося клиента создается отдельный процесс, взаимодействующий с этим клиентом, а отец продолжает ожидать подключений.
 * 
 * Взаимодействие клиента и сервера выполняется в текстовом виде, в конце каждого элемента протокола передается пара символов \r\n. 
 * Длина элемента протокола включая символы \r\n не превышает 255 байт.
 * 
 * Каждому подключившемуся клиенту пересылается сначала строка KEY, затем порядковый номер клиента SERIAL, 
 * начинающийся с 1, то есть первый клиент получает номер 1, второй 2, третий 3 и т. д. 
 * Номера клиентов не должны повторяться. Клиент отправляет серверу положительное 32-битное целое число MAX. 
 * В ответ сервер отправляет клиенту то же самое число MAX.
 * 
 * Далее выполняется цикл обмена клиента и сервера. На каждой итерации цикла клиент пересылает серверу положительное 32-битное целое число NUM. 
 * Если NUM > MAX или NUM + SERIAL не представим 32-битным знаковым целым типом, сервер пересылает клиенту число -1 и закрывает соединение. 
 * В противном случае сервер пересылает клиенту число NUM + SERIAL. Клиент может закрыть соединение в любой момент времени.
 * 
 * Если сервер получает сигнал SIGTERM, должны быть закрыты соединения со всеми подключенными в данный момент клиентами. 
 * Родитель завершается с кодом завершения 0 после завершения всех процессов, созданных для взаимодействия с клиентами.
 * 
 * Предполагайте, что клиент строго соблюдает протокол взаимодействия.
 * 
 * Не забывайте устанавливать опции SO_REUSEADDR и SO_REUSEPORT!
 * 
 * Ошибка Presentation Error означает нарушение протокола взаимодействия со стороны сервера, которое было распознано клиентом.
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
#include <sys/wait.h>

#define try(r) if ((r) < 0) { exit(EXIT_FAILURE); }

#define SPLITTER "\r\n"

pid_t children[8096];
int sfd;
int serial = 0;
int server_fd;

void read_element(int sock, char* buf) {
	int i = 2;
	if (read(sock, buf, 2) != 2) {
		//perror("read");
		exit(EXIT_FAILURE);
	}
	
	while (!(buf[i-2] == '\r' && buf[i-1] == '\n')) {
		if (read(sock, buf+i, 1) != 1) {
			//perror("read");
			exit(EXIT_FAILURE);
		}
		
		i++;
	}
	buf[i-2] = '\0';
	//printf("read %d bytes [%s]\n", i, buf);
	fsync(sock);
}

void do_child(const char* key, int serial) {
	char buf[255];
	
	dprintf(sfd, "%s"SPLITTER"%d" SPLITTER, key, serial);
	fsync(sfd);
	
	int32_t max;
	read_element(sfd, buf);
	//printf("received: [%s] --> max\n", buf);
	sscanf(buf, "%"SCNd32, &max);
	
	try(dprintf(sfd, "%s" SPLITTER, buf));
	fsync(sfd);
	
	int32_t num;
	while (1) {
		read_element(sfd, buf);
		sscanf(buf, "%" SCNd32, &num);
		
		if (num > max || (num + serial < num)) {
			try(dprintf(sfd, "-1" SPLITTER));
			close(sfd);
			exit(0);
		}
		
		try(dprintf(sfd, "%" SCNd32 SPLITTER, num+serial));
	}
	
}

void handle_sigterm (int sig) {
	// Only parent handles this
	for (int i = 0; i < serial; ++i) {
		kill(children[i], SIGINT);
		waitpid(children[i], NULL, 0);
	}
	
	close(server_fd);
	
	_exit(0);
}

void handle_sigint(int sig) {
	// Only child handles this
	close(sfd);
	_exit(0);
}

int main(int argc, char* argv[]) {
	signal(SIGTERM, handle_sigterm);
	signal(SIGINT, handle_sigint);
	
	if (argc != 3) {
		//perror("args");
		exit(EXIT_FAILURE);
	}
	 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    int PORT = htons(atoi(argv[1]));   

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        //perror("socket failed"); 
        exit(EXIT_FAILURE);
    }
    
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        //perror("setsockopt"); 
        close(server_fd);
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    {
        //perror("bind failed"); 
        close(server_fd);
        exit(EXIT_FAILURE); 
    }
    if (listen(server_fd, 3) < 0) 
    { 
        //perror("listen"); 
        close(server_fd);
        exit(EXIT_FAILURE); 
    } 
    
    while(1) {
		if ((sfd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) 
		{ 
			//perror("accept"); 
			close(server_fd);
			exit(EXIT_FAILURE); 
		}
		
		if ((children[serial++] = fork()) != 0) {
			// parent
			close(sfd);
			continue;
		}
		
		// child
		close(server_fd);
		do_child(argv[2], serial);
		exit(0);
	}
    
	return 0;
}

