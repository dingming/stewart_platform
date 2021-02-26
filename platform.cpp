#include "platform.h"

double A[6][3]={{100.0, 0.0, 0.0},
				{50.0, 80.6603, 0.0},
				{-50.0, 80.6603, 0.0},
				{-100.0, 0.0, 0.0},
				{-50.0, -80.6603, 0.0},
				{50.0, -80.6603, 0.0}};

double B[6][3]={{100.0*(0.75), 0.0*(0.75), 100.0},
				{50.0*(0.75), 80.6603*(0.75), 100.0},
				{-50.0*(0.75), 80.6603*(0.75), 100.0},
				{-100.0*(0.75), 0.0*(0.75), 100.0},
				{-50.0*(0.75), -80.6603*(0.75), 100.0},
				{50.0*(0.75), -80.6603*(0.75), 100.0}};

double C[2][3]={{0.0, 0.0, 0.0},
				{0.0, 0.0, 100.0}};


cStewartPlatform::cStewartPlatform()
{
	for(int i=0;i<6;i++){
		vLower[i].set(A[i]);
		vUpper[i].set(B[i]);
		vUpper0[i].set(B[i]);
	}
	CenterL.set(C[0]);
	CenterU.set(C[1]);
	aroll=0.0; apitch=0.0; ayaw=0.0;
	mx = 0.0; my = 0.0; mz = 0.0;
}

cStewartPlatform::~cStewartPlatform()
{

}

void cStewartPlatform::roll(double angle)
{
	aroll += angle;
	setShdData();
}

void cStewartPlatform::pitch(double angle)
{
	apitch += angle;
	setShdData();
}

void cStewartPlatform::yaw(double angle)
{
	ayaw += angle;
	setShdData();
}

void cStewartPlatform::move(double dx, double dy, double dz)
{
	mx += dx;
	my += dy;
	mz += dz;
	setShdData();
}

void cStewartPlatform::translate()
{
	HTMatrix M1, M2, M3, M4;
	M1.roll(aroll);
	M2.pitch(apitch);
	M3.yaw(ayaw);
	M4.move(mx, my, mz);

	TM = M4*M1*M2*M3;

	for(int i=0;i<6;i++){
		vUpper[i]=TM*(vUpper0[i]-CenterU) + CenterU;
	}
}

void cStewartPlatform::status()
{
	printf("rotation: \t%.2f, \t%.2f, \t%.2f\n", aroll, apitch, ayaw);
	printf("translate: \t%.2f, \t%.2f, \t%.2f\n", mx, my, mz);
}

void cStewartPlatform::reset()
{
	aroll=0.0; apitch=0.0; ayaw=0.0;
	mx=0.0; my=0.0; mz=0.0;
	setShdData();
}

void cStewartPlatform::getShdData()
{
	aroll = sm.data->angle[0];
	apitch = sm.data->angle[1];
	ayaw = sm.data->angle[2];

	mx=sm.data->move[0];
	my=sm.data->move[1];
	mz=sm.data->move[2];
}

void cStewartPlatform::setShdData()
{
	sm.data->angle[0]=aroll;
	sm.data->angle[1]=apitch;
	sm.data->angle[2]=ayaw;

	sm.data->move[0]=mx;
	sm.data->move[1]=my;
	sm.data->move[2]=mz;
}
