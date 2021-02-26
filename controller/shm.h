#ifndef SHM_H
#define SHM_H

#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY (1234)
#define SHM_SERVER              (1)
#define SHM_CLIENT              (0)

typedef struct _SHARED_DATA_{
	double angle[3];
	double move[3];
} SHARED_DATA;

typedef struct _SHARED_MEMORY_{
	int isserver;
	int id;
	SHARED_DATA *data;
} SHM;

int shm_init(SHM *sm, int isserver);
int shm_finish(SHM *sm);

#endif
