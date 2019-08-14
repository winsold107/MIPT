//На стандартный поток ввода подаются текстовые строки, не превышающие в длину 1000 символов. Каждая текстовая строка содержит имя хоста и имя сервиса, каждое из которых является символьными строками.
//Для каждой пары HOST SERVICE на стандартный поток вывода напечатайте адрес IPv4 и номер порта.
//Если имя HOST отображается в несколько IP-адресов, выводите IP-адрес, представление которого в локальном порядке байт (32 бита) минимально.
//Если при отображении возникла ошибка, на стандартный поток вывода напечатайте текстовое сообщение об ошибке.
//Используйте функции getaddrinfo, gai_strerror, freeaddrinfo, inet_ntoa, ntohs, ntohl.
//Примечание. Текущий IP-адрес хоста google.com может отличаться от приведенного в примере.
//Input
//google.com https
//go.go 25
//Output
//173.194.32.128:443
//No address associated with hostname

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main (int argc, char* argv[]) {
		char buf[1024], node[sizeof(buf)], service[sizeof(buf)];
		while(fgets(buf, sizeof(buf), stdin)) {
				if(sscanf(buf, "%s%s", node, service) != 2) {
						fprintf(stderr, "failed to parse line\n");
						exit(1);
				}
				struct addrinfo hints = {.ai_family = AF_INET, .ai_socktype = SOCK_STREAM};
				struct addrinfo *result = NULL;
				int err = getaddrinfo(node, service, &hints, &result);
				if(err) {
						printf("%s\n", gai_strerror(err));
				} 
				else {
						if(result) {
								const struct sockaddr_in *minp = NULL;
								for(struct addrinfo *p = result; p; p = p->ai_next) {
										const struct sockaddr_in *addr = (const struct sockaddr_in*) p->ai_addr;
										if(!minp) {
												minp = addr;
										}
										else if (ntohl(addr->sin_addr.s_addr) < ntohl(minp->sin_addr.s_addr)) {
												minp = addr;
										}
								}
								if(minp) {
										printf("%s:%d\n", inet_ntoa(minp->sin_addr), ntohs(minp->sin_port));
								}
						}
						freeaddrinfo(result);
				}
		}
		return 0;
}
