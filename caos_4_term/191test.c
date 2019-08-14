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
#include <assert.h>


typedef struct {
    sem_t request_ready;  // начальное значение 0
    sem_t response_ready; // начальное значение 0
    char func_name[20];
    double value;
    double result;
} data;


void send_function(data* shm, const char* name, double send, double expected) {
	strcpy(shm->func_name, name);
	shm->value = send;
	sem_post(&shm->request_ready);
	
	if (name[0] != '\0') {
		sem_wait(&shm->response_ready);
		printf("Assertion : %lf %lf \n", shm->result, expected);
		assert(shm->result == expected);
	}
}

int main(int argc, char* argv[]) {
	setbuf(stdout, NULL);
	const char* shmname = argv[1];
	
	int shm_id = shm_open(shmname, O_RDWR | O_CREAT, 0642);
	size_t map_size = sizeof(data);
	size_t page_size = sysconf(_SC_PAGESIZE);
	if(map_size % page_size > 0) {
		map_size = (map_size/page_size+1)*page_size;
	}
	ftruncate(shm_id, map_size);
	data* shm = mmap (NULL, 
								  map_size, 
								  PROT_READ|PROT_WRITE,
								  MAP_SHARED,
								  shm_id, 0);
	close(shm_id);
				
//	sem_init(&shm->response_ready, 0642, 0);
//	sem_init(&shm->request_ready, 0642, 0);		
	
	send_function(shm, "zero", 0, 0);
	send_function(shm, "zero", 1, 0);
	send_function(shm, "zero", 2, 0);
	
	send_function(shm, "ident", 0, 0);
	send_function(shm, "ident", 1, 1);
	send_function(shm, "ident", 2, 2);

	send_function(shm, "increment", 0, 1);
	send_function(shm, "increment", 1, 2);
	send_function(shm, "increment", 2, 3);
	
	send_function(shm, "", 0, 0);

}
