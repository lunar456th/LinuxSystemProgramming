#include "shmlib.h"
#include <stdio.h>
#include <string.h>

int main() {
	int shm_id, ret;
	SHM_t *shm;

	shm_id = OpenSHM(5000);
	shm = GetPtrSHM(shm_id);
	shm->age = 18;
	strcpy(shm->name, "daniel");
	getchar();
	return 0;
}

