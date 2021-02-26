// -*- c++-mode -*-
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "myconfig.h"
#include "mygl.h"
#include "mathutils.h"

#include "draw.h"
#include "platform.h"

cStewartPlatform sp;


void print_help()
{
	printf("-------- HELP --------\n");
	HTMatrix m,m2;
	Point p(1,2,3);
	m = (m+m)*(m+m);
	m.print();
	p = m*p;
	p.print();
	m2.roll(DEG2RAD(30));
	m2.print();

//	printf("MOUSE:\n");
// 	printf("\tLeft_Button: \tSelect joint\n");
// 	printf("\tRight_Button: \tMove View Point\n");
// 	printf("\tMiddle_Button: \tRotate View Point\n");
// 	printf("\tWheel_Up/Down: \tMove Joint\n");
// 	printf("KEY:\n");
// 	printf("\t\"1~7\": \t\tSelet joint\n");
// 	printf("\t\"-/+\": \t\tMove joint\n");
// 	printf("\t\"q/ESC\": \tQuit\n");
}

int main (int argc, char **argv)
{
	sp.sm.init(SHM_SERVER);
	myglConfig(argc, argv);
//	print_help();
	glutMainLoop();
	return 0;
}
