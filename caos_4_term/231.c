//Единственным аргументом программы является целое число N>1 - число потоков, которые нужно создать.
//На стандартном потоке ввода задается последовательность целых чисел.
//Реализуйте программу, которая запускает N потоков, каждый из которых читает числа со стандартного потока ввода, и вычисляет частичные суммы.
//На стандартный поток вывода необходимо вывести итоговую сумму всех чисел.
//Минимизируйте объем используемой памяти настолько, насколько это возможно. Обратите внимание на ограничение по памяти.

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static void* thread_func(void* arg) {
	int value;
	int partial_summary = 0;
	while (scanf("%d", &value) >= 1) {
		partial_summary += value;
	}
	int* ret;
	ret = (int*) partial_summary;
	return ret;
}

int main(int argc, char* argv[]) {
	int i = 0;
	int answer = 0;
	int part = 0;
	pthread_t thread[100];
	while(i < atoi(argv[1])) {
		pthread_attr_t attr;
		pthread_attr_setguardsize(&attr, 0);
		pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
		pthread_attr_init(&attr);
		pthread_create(&thread[i], NULL, thread_func, 0);
		pthread_attr_destroy(&attr);
		i++;
	}
	i = 0;
	int real_answer = 0;
	while(i < atoi(argv[1])) {
		pthread_join(thread[i], (void*) &part);
		answer += part;
		fflush(stdout);
		i++;
		real_answer += answer;
	}
	printf("%d ", answer);
	return 0;
}
