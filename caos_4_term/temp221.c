//Программе задается единственный аргумент - номер TCP-порта.
//Необходимо принимать входящие соединения на TCP/IPv4 для сервера localhost, читать данные от клиентов в текстовом виде, 
//и отправлять их обратно в текстовом виде, заменяя все строчные буквы на заглавные. Все обрабатываемые символы - из кодировки ASCII.
//Одновременных подключений может быть много. Использовать несколько потоков или процессов запрещено.
//Сервер должен корректно завершать работу при получении сигнала SIGTERM.
//Указание: используйте неблокирующий ввод-вывод.

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
#include <sys/epoll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <ctype.h>

#define server "127.0.0.1"
#define MAXEVENTS 500

static int socket_fd, epoll_fd;

void handle_term () {
	_exit(0);
}

static void socket_create_bind_local(char port[])
{
	struct sockaddr_in server_addr;
	int opt = 1;

        if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        if (setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int)) == -1) {
            perror("Setsockopt");
            exit(1);
        }
       
        server_addr.sin_family = AF_INET;        
        server_addr.sin_port = htons(atoi(port)); 
        server_addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
            perror("Unable to bind");
            exit(1);
        }

}

static int make_socket_non_blocking(int sfd)
{
	int flags = fcntl(sfd, F_GETFL, 0);
	if (flags == -1) {
		perror("fcntl");
		return -1;
	}

	flags |= O_NONBLOCK;
	if (fcntl(sfd, F_SETFL, flags) == -1) {
		perror("fcntl");
		return -1;
	}

	return 0;
}

void accept_and_add_new(char port[])
{
	struct epoll_event event;
	struct sockaddr in_addr;
	socklen_t in_len = sizeof(in_addr);
	int infd;
	char hbuf[NI_MAXHOST];

	while ((infd = accept(socket_fd, &in_addr, &in_len)) != -1) {
    getnameinfo(&in_addr, in_len,
				hbuf, sizeof(hbuf),
				port, strlen(port),
				NI_NUMERICHOST | NI_NUMERICHOST);
		
		//Make the incoming socket non-block and add it to list of fds to monitor
		if (make_socket_non_blocking(infd) == -1) {
			_exit(0);
		}

		event.data.fd = infd;
		event.events = EPOLLIN | EPOLLET;
		if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, infd, &event) == -1) {
			perror("epoll_ctl");
			_exit(0);
		}
		in_len = sizeof(in_addr);
	}

	if (errno != EAGAIN && errno != EWOULDBLOCK)
		perror("accept");
	// else We have processed all incomming connectioins
}

void process_new_data(int fd)
{
	ssize_t count;
	char buf[1024];

	while ((count = read(fd, buf, sizeof(buf) - 1))) {
		if (count == -1) {
			/* EAGAIN, read all data */
			if (errno == EAGAIN)
				return;

			perror("read");
			break;
		}

		/* Write buffer to stdout */
		buf[count] = '\0';
		for(int i = 0; i < count; i++) {
			if (islower(buf[i]))
            {
                buf[i] = toupper(buf[i]);
            }
		}
		
		dprintf(fd, "%s \n", buf);
		fsync(fd);
		//printf("%s \n", buf);
	}

	close(fd);
}

int main(int argc, char* argv[])
{
	struct epoll_event event, *events;

	struct sigaction action_term;
	memset(&action_term, 0, sizeof(action_term));
	action_term.sa_handler = handle_term;
	action_term.sa_flags = SA_RESTART;
	sigaction(SIGTERM, &action_term, NULL);

	socket_create_bind_local(argv[1]);

	if (make_socket_non_blocking(socket_fd) == -1)
		exit(1);
       
    if (listen(socket_fd, 5) == -1) {
        perror("Listen");
        exit(1);
    }
 
	epoll_fd = epoll_create1(0);
	if (epoll_fd == -1) {
		perror("epoll_create1");
		exit(1);
	}

	event.data.fd = socket_fd;
	event.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event) == -1) {
		perror("epoll_ctl");
		exit(1);
	}

	events = calloc(MAXEVENTS, sizeof(event));

	while(1) {
		int n, i;
		n = epoll_wait(epoll_fd, events, MAXEVENTS, -1);
		for (i = 0; i < n; i++) {
			if (events[i].events & EPOLLERR || events[i].events & EPOLLHUP ||
			    !(events[i].events & EPOLLIN)) {
				/* An error on this fd or socket not ready */
				perror("epoll error");
				close(events[i].data.fd);
			} else if (events[i].data.fd == socket_fd) {
				/* New incoming connection */
				accept_and_add_new(argv[1]);
			} else {
				/* Data incoming on fd */
				process_new_data(events[i].data.fd);
			}
		}
	}

	free(events);
	close(socket_fd);
	return 0;
}
