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

class SharedMemory{
protected:
	int id;

public:
	int isserver;
	SHARED_DATA *data;

public:
	SharedMemory();
	~SharedMemory();

	void init(int flag);
};

#endif
