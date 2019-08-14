// В аргументах командной строки задаются имя хоста HOST, имя сервиса (номер порта) SERVICE и некоторый строковый параметр KEY. 
// Программа должна подключиться к заданному хосту и сервису по протоколу TCP. Программа отправляет на сервер строку KEY. 
// В ответ сервер посылает клиенту целое число K > 0. Клиент отправляет серверу числа от 0 до K включительно, 
// после чего ждет ответа от сервера - целого беззнакового 64-битного числа, которое выводит на стандартный поток вывода, после чего завершает работу.
// Обмен данными клиента и сервера ведется в текстовом виде. Не забывайте выводить разделитель и сбрасывать буфер.
// При разрыве соединения клиент должен завершить работу с кодом завершения 0.

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

int main(int argc, char* argv[]) {	
	if(argc != 4) {
		fprintf(stderr, "args\n");
		fflush(stderr);
		exit(1);
	}

	const char* host = argv[1];
	const char* service = argv[2];
	const char* key = argv[3];
	
	struct sigaction action_pipe;
	memset(&action_pipe, 0, sizeof(action_pipe));
	action_pipe.sa_handler = handle_pipe;
	action_pipe.sa_flags = SA_RESTART;
	sigaction(SIGPIPE, &action_pipe, NULL);
	
	struct addrinfo hints = {.ai_family = AF_INET, .ai_socktype = SOCK_STREAM};
	struct addrinfo *result = NULL;
	int err = getaddrinfo(host, service, &hints, &result);
	
	if(err) {
		fprintf(stderr, "bad host name\n");
		exit(1);
	}
	
	if (!result) {
		exit(1);
	}

	int sfd;	
	if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		fflush(stderr);
		exit(0);
	}


	if(connect(sfd, (struct sockaddr*) result->ai_addr, sizeof(struct sockaddr_in)) < 0) {
		perror("connect");
		fflush(stdout);
		exit(0);
	}

	dprintf(sfd, "%s ", key);
	fsync(sfd);

	char buf[1024];
	int bytes = read(sfd, buf, sizeof(buf));
	if (bytes <= 0) {
		close(sfd);
		exit(0);
	}
	fsync(sfd);
	
	buf[bytes] = '\0';
	
	int k = atoi(buf);
	
	for(int i = 0; i <= k; i++) {
		if (dprintf(sfd, "%d ", i) < 0) {
			close(sfd);
			exit(0);
		}
		fsync(sfd);
	}
	
	
	bytes = read(sfd, buf, sizeof(buf));
	if (bytes <= 0) {
		close(sfd);
		exit(0);
	}
	
	uint64_t final_ans = strtoull(buf, NULL, 10);
	
	printf("%" PRIu64 "\n", final_ans);
	fflush(stdout);			
	
	close(sfd);
	return 0;
}
