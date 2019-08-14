//Программе в качестве аргументов передаются N имен текстовых файлов.
//Программа должна обрабатывать множество сигналов от SIGRTMIN до SIGRTMAX,
//причем номер сигнала в диапазоне от SIGRTMIN+1 определяет порядковый номер файла из аргументов:
//x = signo - SIGRTMIN; // SIGRTMIN <= signo <= SIGRTMAX
                      // 1 <= x <= SIGRTMAX-SIGRTMIN
//При получении очередного сигнала необходимо прочитать одну строку 
//из определенного файла и вывести её на стандартный поток вывода.
//При получении сигнала с номером SIGRTMIN, т.е. при номере аргумента, 
//равным 0, - корректно завершить свою работу с кодом 0.
//Все остальные сигналы нужно игнорировать.
//Если для вывода используются высокоуровневые функции стандартной библиотеки Си, 
//то необходимо выталкивать буфер обмена после вывода каждой строки.

#include <sys/signalfd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void transfer_line (FILE *from) {
	char buffer [4096];
	memset (buffer, 0, sizeof(buffer));
	fgets(buffer, sizeof(buffer), from);
	fputs(buffer, stdout);
	fflush(stdout);
}

int main (int argc, char *argv[]) {
		FILE * files[argc - 1];
		for (int i = 1; i < argc; ++i) {
				files[i - 1] = fopen (argv[i], "r");
		}
		sigset_t mask_to_block, mask_to_catch;
		sigfillset (&mask_to_block);
		sigemptyset (&mask_to_catch);
		for (int i = 0; i < argc; ++i) {
				sigaddset (&mask_to_catch, SIGRTMIN + i);
		}
		sigprocmask (SIG_BLOCK, &mask_to_block, NULL);
		int fd = signalfd(-1, &mask_to_catch, 0);
		struct signalfd_siginfo si;
		int index;
		while(1) {
				read (fd, &si, sizeof (si));
				index = si.ssi_signo - SIGRTMIN;
				if (0 == index) {
						break;
				}
				else {
						transfer_line (files[index - 1]);
				}
		}
		close (fd);
		for (int i = 1; i < argc; ++i) {
				fclose (files [i - 1]);
		}
}


