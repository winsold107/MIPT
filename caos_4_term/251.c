//В аргументах командной строки передаются: 1) имя сервера; 2) путь к скрипту на сервере, начинающийся с символа /; 3) имя локального файла для отправки.
//Необходимо выполнить HTTP-POST запрос к серверу, в котором отправить содержимое файла.
//На стандартный поток ввода вывести ответ сервера (исключая заголовки).
//Запрещено использовать сторонние библиотеки.

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
	char* host_name = argv[1];
	char* script_path = argv[2];
	char* file_name = argv[3];
	
	signal(SIGPIPE, SIG_IGN);
	
	struct addrinfo addr_hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM };
	struct addrinfo *addr_result = NULL;
	getaddrinfo(host_name, "http", &addr_hints, &addr_result);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(0 != connect(sock, addr_result->ai_addr, addr_result->ai_addrlen)) {
			perror("connect");
			exit(1);
	}
	
	FILE* outer_file = fopen(file_name, "r");
	fseek(outer_file, 0, SEEK_END);
	long fsize = ftell(outer_file);
	fseek(outer_file, 0, SEEK_SET);  /* same as rewind(f); */
	

	char *string = malloc(fsize + 1);
	fread(string, 1, fsize, outer_file);
	string[fsize] = '\0';

	int content_length = fsize;
	int buf_size = fsize + 4096;
	char* request = (char*) malloc((buf_size)*sizeof(char));	
	snprintf(request, buf_size,
			"POST %s HTTP/1.1\r\n"
			"Host: %s\r\n"
			"Content-Type: multipart/form-data\r\n"
			"Connection: close\r\n"
			"Content-Length: %d\r\n\r\n"
			"%s\r\n"
			"\r\n",
			script_path, host_name, content_length, string);
	write(sock, request, strnlen(request, buf_size));
	FILE* in = fdopen(sock, "r");
	
	char minibuf[65536];
	int headers_completed = 0;
	
	while(fgets(minibuf, sizeof(minibuf), in)) {
		if(0 == strcmp(minibuf, "\n") || 0 == strcmp(minibuf, "\r\n")) {
			headers_completed = 1;
			continue;
		}
		if(headers_completed) {
			printf("%s", minibuf);
		}
	};
	fclose(outer_file);
	fclose(in);
	free(string);
	free(request);
}

