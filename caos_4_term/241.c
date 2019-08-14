//Программа принимает три аргумента: два 64-битных числа A и B, и 32-битное число N.
//Затем создается дополнительный поток, которые генерирует простые числа в диапазоне от A до B включительно, и сообщает об этом основному потоку, с которого началось выполнение функции main.
//Главный поток выводит на стандартный поток вывода каждое полученное число и завершает свою работу после того, как получит N чисел.
//Запрещено использовать глобальные переменные.

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <inttypes.h>

struct Argument {
	int64_t A, B;
	int32_t N;
	pthread_cond_t condvar1;
	pthread_mutex_t mutex1;
	pthread_cond_t condvar2;
	pthread_mutex_t mutex2;
	int64_t answer;
};

int64_t is_prime(int64_t num) {
	if (num <= 1) return 0;
	if (num % 2 == 0 && num > 2) return 0;
	for(int i = 3; i < num / 2; i+= 2) {
		if (num % i == 0) return 0;
	}
	return 1;
}

int64_t next_prime(int64_t current) {
	for (int64_t i = current + 1; ; ++i) {
		if (is_prime(i)) {
			return i;
		}
	}
}

static void* thread_func(void* arg) {
	struct Argument* casted = (struct Argument*) arg;
	pthread_mutex_lock(&(casted->mutex2));
	int64_t cur = casted->A - 1;
	int64_t i = 0;
	while (i < casted->N) {
		pthread_mutex_lock(&(casted->mutex1));
		cur = next_prime(cur);
		casted->answer = cur;
		pthread_mutex_unlock(&(casted->mutex1));	
		pthread_cond_signal(&(casted->condvar1));
		pthread_cond_wait(&(casted->condvar2), &(casted->mutex2));
		i++;
	}
	return NULL;
}

int main(int argc, char* argv[]) {
    struct Argument args;
	sscanf(argv[1], "%"SCNd64, &args.A);
	sscanf(argv[2], "%"SCNd64, &args.B);
	sscanf(argv[3], "%"SCNd32, &args.N);
	
	pthread_t thread;

	pthread_cond_init(&args.condvar1, NULL);
	pthread_mutex_init(&args.mutex1, NULL);
	pthread_cond_init(&args.condvar2, NULL);
	pthread_mutex_init(&args.mutex2, NULL);
	
	pthread_mutex_lock(&args.mutex1);
	pthread_create(&thread, NULL, thread_func, &args);
	
	int64_t i = 0;
	
	while(i < args.N){
	pthread_cond_wait(&args.condvar1, &args.mutex1);
	pthread_mutex_lock(&args.mutex2);
		printf("%"SCNd64"\n", args.answer);
		i++;
	pthread_mutex_unlock(&args.mutex2);
	pthread_cond_signal(&args.condvar2);	
	}
	
	pthread_mutex_unlock(&args.mutex1);
	pthread_join(thread, NULL);
	
	pthread_mutex_destroy(&args.mutex1);
	pthread_mutex_destroy(&args.mutex2);
	pthread_cond_destroy(&args.condvar1);
	pthread_cond_destroy(&args.condvar2);
	return 0;
}

