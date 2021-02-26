#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdlib.h>
#include "mathutils.h"
#include "shm.h"

class cStewartPlatform
{
public:
	Point vLower[6];
	Point vUpper[6];
	Point CenterL;
	Point CenterU;
	HTMatrix TM;
	
	double aroll, apitch, ayaw;
	double mx, my, mz;
	
	SharedMemory shdm;

public:
	cStewartPlatform();
	~cStewartPlatform();

	void roll(double angle);
	void pitch(double angle);
	void yaw(double angle);
	void move(double x, double y, double z);
	

	void translate();
	void status();
	void reset();

	SharedMemory sm;
	void getShdData();
	void setShdData();

protected:
	bool ismoved;
	Point vUpper0[6];

};

#endif
