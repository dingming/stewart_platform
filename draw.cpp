#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "myconfig.h"
#include "mathutils.h"
#include "draw.h"
#include "color.h"
#include "mygl.h"

#include "platform.h"
extern cStewartPlatform sp;

void myglCylinder(double r0, double r1, double l, int st)
{
    int i;
	double normal[3];
	glPushMatrix();
	for(i = 1; i <= st; i++) {
		double lng0 = 2 * M_PI * (double) (i-1) / st;
		double x0 = cos(lng0);
		double y0 = sin(lng0);

		double lng1 = 2 * M_PI * (double) i / st;
		double x1 = cos(lng1);
		double y1 = sin(lng1);
		
		double p[3][3];
		
		// bottom
		p[0][0] = 0;p[0][1] = 0; p[0][2]= 0;
		p[1][0] = x0 * r1;p[1][1] =  y0 * r1; p[1][2]= 0;
		p[2][0] = x1 * r1;p[2][1] =  y1 * r1; p[2][2]= 0;
		SetNormal(p[0],p[1],p[2],normal);
		glNormal3dv(normal);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(x0 * r0, y0 * r0, 0);
		glVertex3f(x1 * r0, y1 * r0, 0);
		glEnd();

		// Cylinder
		p[0][0] = x0 * r0;p[0][1] =  y0 * r0; p[0][2]= 0;
		p[1][0] = x0 * r1;p[1][1] =  y0 * r1; p[1][2]= l;
		p[2][0] = x1 * r1;p[2][1] =  y1 * r1; p[2][2]= l;

		SetNormal(p[2],p[1],p[0],normal);
		glNormal3dv(normal);
		glBegin(GL_POLYGON);
		glVertex3f(x0 * r0, y0 * r0, 0);
		glVertex3f(x0 * r1, y0 * r1, l);
		glVertex3f(x1 * r1, y1 * r1, l);
		glVertex3f(x1 * r0, y1 * r0, 0);
		glEnd();

		// top
		p[0][0] = 0;p[0][1] = 0; p[0][2]= l;
		p[1][0] = x0 * r1;p[1][1] =  y0 * r1; p[1][2]= l;
		p[2][0] = x1 * r1;p[2][1] =  y1 * r1; p[2][2]= l;
		SetNormal(p[2],p[1],p[0],normal);
		glNormal3dv(normal);
		glBegin(GL_POLYGON);
		glVertex3f(0, 0, l);
		glVertex3f(x0 * r1, y0 * r1, l);
		glVertex3f(x1 * r1, y1 * r1, l);
		glEnd();
	}	
	glPopMatrix();
}

void draw_platform(Point v[])
{
	double normal[3];
	glPushMatrix();
	{
		SetNormal(v[0].data, v[1].data , v[2].data, normal);
		glNormal3dv(normal);
		glBegin(GL_POLYGON);
		for(int i=0; i<6; i++){
			glVertex3f(v[i].x(), v[i].y(), v[i].z());
		}
		glEnd();

		for(int i=0; i<6; i++){
			glPushMatrix();
			{
				glTranslated(v[i].x(), v[i].y(), v[i].z());
				glutSolidSphere(5,16,16);
			}
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void draw_Cylinder(Point v1, Point v2, double nl,
				   double r1, double r2, int st)
{
	double dist;
	double angle[2];

	// Draw in Line
	glPushMatrix();
	{
		glBegin(GL_LINES);
		glVertex3f(v1.x(), v1.y(), v1.z());
		glVertex3f(v2.x(), v2.y(), v2.z());
		glEnd();
	}
	glPopMatrix();

	// Draw in Cylinder
	dist = pointsDist(v1, v2);
	point2angle(v1,v2,angle);
	glPushMatrix();
	{
		glTranslatef(v1.data[0],v1.data[1],v1.data[2]);
		glRotatef(90-RAD2DEG(angle[0]), 0.0, 0.0, 1.0);
		glRotatef(RAD2DEG(angle[1]), 0.0, 1.0, 0.0);
		glPushMatrix();
		{
			glTranslatef(0,0, 10);
			myglCylinder(r1, r1, nl, st);
		}
		glPopMatrix();

		myglCylinder(r2, r2, dist, st);
	}
	glPopMatrix();
}

void draw()
{
	sp.getShdData();
	sp.translate();
	//sp.status();
	//sp.roll(DEG2RAD(10));
	//sp.pitch(DEG2RAD(10));
	//sp.yaw(DEG2RAD(30));
	//sp.move( 10, 0 , 0 );
	//sp.move( 0, 10 , 0 );
	//sp.move( 10, 0 , 0 );

// 	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
// 	glutSolidCube(100);
	// Draw lower Platform
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
	draw_platform(sp.vLower);

	// Draw upper Platform
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
	draw_platform(sp.vUpper);

	// Draw Cylinder
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey8);
	for(int i=0; i<6; i++){
		draw_Cylinder(sp.vLower[i], sp.vUpper[i], 30, 4, 2, 32);
	}
}
