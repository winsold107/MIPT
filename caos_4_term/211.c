//Программа читает со стандартного потока последовательность лексем - имен хостов.
//Необходимо для каждого имени сформировать UDP-запрос к DNS-серверу 8.8.8.8 для того,
//чтобы получить IP-адрес сервера для записи типа A. 
//Далее - получить ответ от сервера и вывести IP-адрес на стандартный поток вывода.
//Гарантируется, что для каждого запроса существует ровно 1 IP-адрес.
//Указание: используйте инструменты dig и wireshark для того, чтобы исследовать формат запросов и ответов.

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

int main() {
    char host_name[4096];
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(-1 == sockfd) {
        perror("socket");
        abort();
    }

    struct sockaddr_in addr = {
            .sin_family = AF_INET,
            .sin_addr = inet_addr("8.8.8.8"),
            .sin_port = htons(53)
    };

    char section[4096];
    char request[4096];
    char header[12] = {0xAA, 0xAA, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    char ending[5] = {0x00, 0x00, 0x01, 0x00, 0x01};

    while(scanf("%s", host_name) > 0) {
        memset(request, 0, sizeof(request));
        memset(section, 0, sizeof(section));

        int global_iter = 0;
        while(global_iter < 12) {
            request[global_iter] = header[global_iter];
            global_iter++;
        }

        int i = 0;
        int j = 0;
        while(i < strlen(host_name)) {
            if(host_name[i] == '.') {
                int iter = 0;
                request[global_iter] = strlen(section);
                global_iter++;
                while(iter < strlen(section)) {
                    request[global_iter] = section[iter];
                    iter++;
                    global_iter++;
                }

                memset(section, 0, sizeof(section));
                i++;
                j = 0;
                continue;
            }

            section[j] = host_name[i];
            j++;
            i++;
        }

        int iter = 0;
        request[global_iter] = strlen(section);
        global_iter++;
        while(iter < strlen(section)) {
            request[global_iter] = section[iter];
            iter++;
            global_iter++;
        }


        for(int k = 0; k < 5; k++) {
            request[global_iter] = ending[k];
            global_iter++;
        }

        ssize_t bytes = sendto(sockfd,
                               &request, global_iter,
                               0,
                               (const struct sockaddr*)&addr, sizeof(addr));



        unsigned char answer[4096];
        size_t ans_size = sizeof(answer);
        recvfrom(sockfd,
                 &answer, ans_size,
                 0,
                 NULL, NULL);
        printf("%d.%d.%d.%d\n", answer[global_iter+12], answer[global_iter+13], answer[global_iter+14], answer[global_iter+15]);
    }
    close(sockfd);
    return 0;
}
