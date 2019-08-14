//Программе передается единственный аргумент - начальное значение 0<N≤100.
//Необходимо создать два потока:
//Принимает число, уменьшает его значение на 3, выводит его на стандартный поток вывода, и передает другому потоку.
//Принимает число, увеличивает его значение на 5, выводит его на стандартный поток вывода, и передает другому потоку.
//Начально значение передается первому потоку.
//Взаимодействие прекращается, когда значение будет равно 0, либо станет строго больше 100. 
//Последний поток, который получит число 0 или число >100, должен вывести его на стандартный поток вывода, и завершить работу.
//Для передачи чисел между потоками используйте пару сокетов (man socketpair).

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#define terminate_condition(r) (r > 100 || r == 0)

static const int FINISH = -100;

void* child(void* arg) {
	int socket = *(int*) arg;
	int recv_num;
	while(1) {
		read(socket, &recv_num, sizeof(recv_num));
		if (recv_num == FINISH)
			return NULL;
			
		recv_num += 5;
		printf("%d\n", recv_num);
		if(terminate_condition(recv_num)) {	
			write(socket, &FINISH, sizeof(FINISH));
			return NULL;
		}
		
		write(socket, &recv_num, sizeof(recv_num));
	} 
}

void parent(int socket, int recv_num, pthread_t child) {
	int first = 1;
	while(1) {
		if (!first)
			read(socket, &recv_num, sizeof(recv_num));
		else
			first = 0;
			
		if (recv_num == FINISH)
			return;
		
		recv_num -= 3;
		printf("%d\n", recv_num);
		if(terminate_condition(recv_num)) {
			write(socket, &FINISH, sizeof(FINISH));
			return;
		}
		
		write(socket, &recv_num, sizeof(recv_num));
	} 
}

void run(int start_value) {
    int fd[2];
    socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);
	pthread_t thread;
	pthread_create(&thread, NULL, child, &fd[1]);
	parent(fd[0], start_value, thread);
	pthread_join(thread, NULL);
	close(fd[0]);
	close(fd[1]);
}

int main(int argc, char* argv[]) {
	int start_value;
	sscanf(argv[1], "%d", &start_value);
	run(start_value);
}
