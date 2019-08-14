//Программа запускается с двумя целочисленными аргументами: N>0 - количество итераций; и k>0 - количество потоков.
//Необходимо создать массив из k вещественных чисел, после чего запустить k потоков, каждый из которых работает со своим элементом массива и двумя соседними.
//Каждый поток N раз увеличивает значение своего элемента на 1, увеличивает значение соседа слева на 0.99, и увеличивает значение соседа справа на 1.01.
//Для потоков, у которых нет соседей справа (k-1) или слева (0), соседними считать первое и последнее значение массива соответственно.
//После того, как все потоки проведут N итераций, необходимо вывести значения всех элементов.
//Запрещено использовать глобальные переменные.
//Для вывода используйте формат %.10g.

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double *array;
    pthread_mutex_t *mutex;
    pthread_t thread;
    size_t N;
    size_t k;
    size_t index;
} context_t;

void* func(void *arg) {
    const context_t* ctx = arg;
    const size_t me = ctx->index;
    const size_t left = 0 == me? ctx->k - 1 : me - 1;
    const size_t right = ctx->k - 1 == me? 0 : me + 1;
    const double add_left = 0.99;
    const double add_me = 1;
    const double add_right = 1.01;
    for (size_t i = 0; i < ctx->N; ++i) {
        pthread_mutex_lock(ctx->mutex);
        ctx->array[left] += add_left;
        ctx->array[me] += add_me;
        ctx->array[right] += add_right;
        pthread_mutex_unlock(ctx->mutex);
    }
    return 0;
}

int main(int argc, char* argv[]) {
    int N = strtol(argv[1], NULL, 10);
    int k = strtol(argv[2], NULL, 10);
    
    context_t threads[k];
    double array[k];
    memset(array, 0 , sizeof(array));
    
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_attr_t attr;
    pthread_attr_init (&attr);
    pthread_attr_setguardsize(&attr, 0);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    
    for (int i = 0; i < k; ++i) {
        threads[i].k = k;
        threads[i].N = N;
        threads[i].index = i;
        threads[i].mutex = &mutex;
        threads[i].array = array;
        pthread_create(&threads[i].thread, &attr, func, &threads[i]);
    }
    
    pthread_attr_destroy(&attr);
    for (int i = 0; i < k; ++i) {
        pthread_join(threads[i].thread, NULL);
    }
    for (int i = 0; i < k; ++i) {
        printf("%.10g\n", array[i]);
    }
}
