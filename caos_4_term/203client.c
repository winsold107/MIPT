// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <inttypes.h>

#define SPLITTER "\r\n"

void read_element(int sfd, char* buf) {
	int i = 2;
	if (read(sfd, buf, 2) != 2) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	
	while (!(buf[i-2] == '\r' && buf[i-1] == '\n')) {
		if (read(sfd, buf+i, 1) != 1) {
			perror("read");
			exit(EXIT_FAILURE);
		}
		
		i++;
	}
	buf[i-2] = '\0';
	fsync(sfd);
}

#define PORT 8888
   
int main(int argc, char const *argv[]) 
{ 
	setbuf(stdout, 0);
    int sock = 0; 
    struct sockaddr_in serv_addr; 

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

	char key[255];
	char serial[255];
	
	read_element(sock, key);
	read_element(sock, serial);

	printf("Key: %s; serial: %s\n", key, serial);

	char buf[255];
	int32_t max = 35;
	printf("max:");
	scanf("%d", &max);
	dprintf(sock, "%" SCNd32 SPLITTER, max);
	fsync(sock);
	read_element(sock, buf);
	fsync(sock);
	
	
	while(1) {
		printf("received [%s]\n", buf);
		int32_t num;
		scanf("%d", &num);
		dprintf(sock, "%d"SPLITTER, num);
		read_element(sock, buf);
		if (buf[0] == '-' && buf[1] == '1') {
			printf("end\n");
			exit(EXIT_FAILURE);
		}
		fsync(sock);
	}
    return 0; 
} 
