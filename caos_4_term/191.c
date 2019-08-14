//Программе в качестве единственного аргумента передается имя файла разделяемой библиотеки.
//Программа должна создать именованный разделяемый сегмент памяти, и поместить в него структуру:
//typedef struct {
    //sem_t request_ready;  // начальное значение 0
    //sem_t response_ready; // начальное значение 0
    //char func_name[20];
    //double value;
    //double result;
//} shared_data_t;
//После инициализации структуры и готовности к взаимодействию - вывести на стандартный поток вывода имя разделяемого сегмента памяти POSIX для начала взаимодействия. При использовании высокоуровневых функций необходимо использовать fflush.
//Взаимодействие заключается в выполнении некоторой функции с заданным именем func_name с единственным аргументом value и сохранением результата в result.
//Когда противоположная сторона сформировала запрос, то разблокируется семафор request_ready. При готовности результата вычисления реализованной программой необходимо разблокировать семафор response_ready.
//Признаком завершения взаимодействия считается пустое имя функции.
//Используйте уникальные имена разделяемых сегментов памяти, например, используя в качестве части имени свой логин в ejudge.
//Не забывайте удалять за собой используемые ресурсы.

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
#include <dlfcn.h>
#include <time.h>

typedef struct {
    sem_t request_ready;  // начальное значение 0
    sem_t response_ready; // начальное значение 0
    char func_name[20];
    double value;
    double result;
} shared_data_t;

int main(int argc, char* argv[]) {
	char shared_memory[] = "/winsold84620346i";
	int shm_id = shm_open(shared_memory, O_RDWR|O_CREAT, 0777);
	
	ftruncate(shm_id, sizeof(shared_data_t));
	shared_data_t* semaphoric_coop = mmap (NULL, sizeof(shared_data_t), 
										   PROT_READ|PROT_WRITE,
										   MAP_SHARED,
										   shm_id, 0);
	close(shm_id);
	
	sem_init(&semaphoric_coop->response_ready, 1, 0);
	sem_init(&semaphoric_coop->request_ready, 1, 0);
		
	void *exec_func;
	exec_func = dlopen(argv[1], RTLD_LAZY);
	if (!exec_func) {
		sem_destroy(&semaphoric_coop->response_ready);
		sem_destroy(&semaphoric_coop->request_ready);
		munmap(semaphoric_coop, sizeof(shared_data_t));
		shm_unlink(shared_memory);
		dlclose(exec_func);
		return 0;
	}
	
	printf("%s\n", shared_memory);
	fflush(stdout);
		
	while (1) {
		sem_wait(&semaphoric_coop->request_ready);
		if (strlen(semaphoric_coop->func_name) == 0) {
			break;
		}
		double (*ret_func) (double) = dlsym(exec_func, semaphoric_coop->func_name);
		semaphoric_coop->result = ret_func(semaphoric_coop->value);
		sem_post(&semaphoric_coop->response_ready);
	}
	sem_destroy(&semaphoric_coop->response_ready);
	sem_destroy(&semaphoric_coop->request_ready);
	munmap(semaphoric_coop, sizeof(shared_data_t));
	shm_unlink(shared_memory);
	dlclose(exec_func);
	return 0;
}
