//Программа обрабатывать сигнал SIGRTMIN, вместе с которым передается некоторое беззнаковой 32-битное целое число N.
//Все остальные сигналы нужно игнорировать.
//При получении очередного сигнала нужно уменьшить это число на единицу и отправить его обратно тому процессу, который его послал (используя тот же самый сигнал).
//Взаимодействие останавливается при получении значения N==0, после чего нужно корректно завершить работу.
//Запрещается использовать signalfd, программа будет компилироваться без поддержки Linux-специфичных расширений.

#include <sys/signalfd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static void handler(int sig, siginfo_t *si, void* skip)
{ 
	if (si->si_value.sival_int == 0) {
		_exit(0);
	}
	
	si->si_value.sival_int--;
	sigqueue(si->si_pid, SIGRTMIN, si->si_value);
}

int main (int argc, char *argv[]) {

	sigset_t mask_to_block;
	sigfillset (&mask_to_block);
	sigdelset (&mask_to_block, SIGRTMIN);
	sigprocmask (SIG_BLOCK, &mask_to_block, NULL);

	struct sigaction sa;
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGRTMIN, &sa, NULL);

	while(1) {
		pause();
	}		
	
	return 0;
}




