//Программа при запуске сообщает на стандартный поток вывода свой PID, 
//выталкивает буфер вывода с помощью fflush, после чего начинает обрабатывать поступающие сигналы.
//При поступлении сигнала SIGTERM необходимо вывести на стандартный поток вывода целое число: 
//количество ранее поступивших сигналов SIGINT и завершить свою работу.
//Семантика повединия сигналов (Sys-V или BSD) считается не определенной.

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t counter = 0;
volatile sig_atomic_t must_exit = 0;

void handle_sigint (int signum) {
		counter ++;
}

void handle_sigterm (int signum) {
		must_exit = 1;
}

int main () {
		struct sigaction action_int;
		memset(&action_int, 0, sizeof(action_int));
		action_int.sa_handler = handle_sigint;
		action_int.sa_flags = SA_RESTART;
		sigaction(SIGINT, &action_int, NULL);
		
		struct sigaction action_term;
		memset(&action_term, 0, sizeof(action_term));
		action_term.sa_handler = handle_sigterm;
		action_term.sa_flags = SA_RESTART;
		sigaction(SIGTERM, &action_term, NULL);
		
		printf("%d\n", getpid());
		fflush(stdout);
		
		while(!must_exit) {
			pause();
		}
		
		printf("%d\n", counter);
		return 0;
}
