#include "shm.h"

SharedMemory::SharedMemory()
{
	
}

SharedMemory::~SharedMemory()
{
	shmdt((void *)data);

	if(isserver == SHM_SERVER){
		if (shmctl(id, IPC_RMID, 0) == -1){
			fprintf(stderr, "shmctl(IPC_RMID) failed\n");
		}
	}
}

void SharedMemory::init(int flag)
{
	isserver = flag;
	fprintf(stderr, "pass\n");
	id = shmget((key_t)SHM_KEY, sizeof(SHARED_DATA), 0666 | IPC_CREAT);
	if(id == -1){
		fprintf(stderr, "shmget failed\n");
	}
	data = (SHARED_DATA *)shmat(id, (void *)0, 0);

	if(isserver == SHM_SERVER){
		printf("MFESHM: start as shm server.\n");
		bzero((void *)data, sizeof(SHARED_DATA));
	}else{
		printf("MFESHM: start as shm client.\n");
	}

	if((void *)data == (void *)-1) {
		fprintf(stderr, "shmat failed\n");
	}
	printf("Memory attached at %p\n", data);

}

