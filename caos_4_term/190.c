//Программе на стандартный поток ввода три лексемы, разделенные пробельными символами: имя семафора готовности данных, имя разделяемого блока памяти и целое неотрицательное значение N.
//Используются разделяемая память и семафоры POSIX.
//В разделяемой памяти содержится массив чисел типа int, который нужно будет вывести на стандартный поток вывода, когда данные будут готовы.
//Данные считаются готовыми в тот момент, когда можно разблокировать семафор.

#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
 
int main(int argc, char* argv[]) {
    char semaphore[NAME_MAX];
    char shared_memory[NAME_MAX];
    int N = 0;
    if (argc > 1)
        strncpy(semaphore, argv[1], sizeof(semaphore));
    else
        scanf("%s", semaphore);
    if (argc > 2)
        strncpy(shared_memory, argv[2], sizeof(shared_memory));
    else
        scanf("%s", shared_memory);
    if (argc > 3)
        N = strtol(argv[3], NULL, 10);
    else
        scanf("%d", &N);
 
    sem_t* sem = sem_open(semaphore, 0);
    sem_wait(sem);
    sem_close(sem);
 
    int shm_id = shm_open(shared_memory, O_RDONLY, 0);
 
    size_t map_size = N * sizeof(int);
 
    int *array = mmap(NULL, map_size,
              PROT_READ,
              MAP_SHARED,
              shm_id, 0);
    close(shm_id);
 
    for(size_t i = 0; i < N ;++i)
        printf("%d ", array[i]);
    fflush(stdout);
    munmap(array, map_size);
}
