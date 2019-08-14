//Программа при запуске сообщает на стандартный поток вывода свой PID, 
//после чего читает со стандартного потока вывода целое число - начальное значение, которое затем будет изменяться.
//При поступлении сигнала SIGUSR1 увеличить текущее значение на 1 и вывести его на стандартный поток вывода.
//При поступлении сигнала SIGUSR2 - умножить текущее значение на -1 и вывести его на стандартный поток вывода.
//Семантика повединия сигналов (Sys-V или BSD) считается не определенной.
//Не забывайте выталкивать буфер вывода.
//Программа должна корректно завершить работу в ответ на сигнал SIGTERM.

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t counter = 0;
volatile sig_atomic_t must_exit = 0;
volatile sig_atomic_t sigusr1_flag = 0;
volatile sig_atomic_t sigusr2_flag = 0;

void handle_sigusr1 (int signum) {
		counter++;
		sigusr1_flag = 1;
}

void handle_sigusr2 (int signum) {
		counter *= (-1);
		sigusr2_flag = 1;
}

void handle_sigterm (int signum) {
		must_exit = 1;
}

int main () {
		struct sigaction action_usr1;
		memset(&action_usr1, 0, sizeof(action_usr1));
		action_usr1.sa_handler = handle_sigusr1;
		action_usr1.sa_flags = SA_RESTART;
		sigaction(SIGUSR1, &action_usr1, NULL);
		
		struct sigaction action_usr2;
		memset(&action_usr2, 0, sizeof(action_usr2));
		action_usr2.sa_handler = handle_sigusr2;
		action_usr2.sa_flags = SA_RESTART;
		sigaction(SIGUSR2, &action_usr2, NULL);
		
		struct sigaction action_term;
		memset(&action_term, 0, sizeof(action_term));
		action_term.sa_handler = handle_sigterm;
		action_term.sa_flags = SA_RESTART;
		sigaction(SIGTERM, &action_term, NULL);
		
		printf("%d\n", getpid());
		fflush(stdout);
		scanf("%d", &counter);
		
		while(!must_exit) {
			if(sigusr1_flag || sigusr2_flag) {
				sigusr1_flag = 0;
				sigusr2_flag = 0;
				printf("%d\n", counter);
				fflush(stdout);
			}
			pause();
		}
		return 0;
}

