#include "shmlib.h"
#include <stdio.h>

int main() {
	int shm_id, ret;
	SHM_t *shm;

	shm_id = CreateSHM(5000);
	shm = GetPtrSHM(shm_id);
	getchar();
	printf("age: %d, name: %s\n", shm->age, shm->name );
	return 0;
}

