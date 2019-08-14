//Программе в качестве аргумента передается имя файла программы на языке Си.
//Необходимо попытаться её скомпилировать с помощью штатного компилятора gcc,
//после чего вывести на стандартный поток вывода: количество строк программы с ошибками (error),
//и количество строк программы с предупреждениями (warning).
//В одной строке может быть найдено несколько ошибок или предупреждений, - нужно вывести именно количество строк.
//В процессе работы нельзя создавать файлы, юзать каналы.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <memory.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
    setbuf(stdout, 0);

	int input = open(argv[1], O_RDONLY);
	dup2(input, 0);
	close(input);

	int fds_pair[2];
	pipe(fds_pair);
    pid_t pid = fork();
    if (pid == 0) {
        dup2(fds_pair[1], 2);
        close(fds_pair[1]);
        execlp("gcc", "gcc", argv[1], "-Wall", "-fsyntax-only", NULL);
        perror("exec");
        exit(-1);
    }
    else if (pid == -1) {
		perror("fork");
		exit(-1);
	}


	close(fds_pair[1]);

	char string[1000];

	int errorAm = 0;
	int warningAm = 0;

	int prev_str_num = -1;
	int war_prev_str_num = -1;


	FILE* file = fdopen(fds_pair[0], "r");

	while(fgets(string, sizeof(string), file)) {
		int cur_str_num = 0;
		int war_cur_str_num = 0;

		int len = strlen(argv[1]);
		
		if(strncmp(string, argv[1], len) != 0) {
			continue;
		}

		int i = len;
		if (string[len] != ':') {
			continue;
		} else {
			i++;
		}

		while (isdigit(string[i])) {
			cur_str_num *= 10;
			cur_str_num += (string[i] - '0');
			war_cur_str_num *= 10;
			war_cur_str_num += (string[i] - '0');
			i++;
		}

		if (string[i] == ':') {
			i++;
			while(isdigit(string[i])) {
				i++;
			}

			if (string[i] == ':') {
				const char* wordStart = string + i + 2;
				if (strncmp(wordStart, "error", 5) == 0 ||
						strncmp(wordStart, "fatal error", strlen("fatal error")) == 0) {
					if (cur_str_num != prev_str_num) {
						errorAm++;
					}
					prev_str_num = cur_str_num;
				}
				
				else if (strncmp(wordStart, "warning", 7) == 0) {
					if (war_prev_str_num != war_cur_str_num) {
						warningAm++;
					}
					war_prev_str_num = war_cur_str_num;
				}
			}
		}
	}
	waitpid(pid, NULL, 0);
	printf("%d\n%d\n", errorAm, warningAm);
    return 0;
}
