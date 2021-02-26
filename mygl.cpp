// -*- c++-mode -*-
#include "mygl.h"
#include "myconfig.h"
#include "draw.h"
#include <time.h>
#include <pthread.h>

#include "platform.h"
extern cStewartPlatform sp;

double porm=0;

#define BUFSIZE	(512)

GLfloat vh = 0.0; //set the angle of rotation
GLfloat vv = 0.0; //set the angle of rotation
int vr = 400;

int clicked=0,nbutton=0;
int bmx=0,bmy=0;//the mouse position before
double tx=0,ty=0,tz=0;

// light position
GLfloat light_position0[] = {2000.0, 1600.0, 2000.0, 1.0 };
GLfloat light_position1[] = {-2000.0, 1600.0, 2000.0, 1.0};
GLfloat light_position2[] = {-2000.0, -2000.0, 2000.0, 1.0};

void myglConfig(int argc, char **argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_RGB); 
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Stewart Platform Simulation");
	myglInit();
	glutDisplayFunc (myglDisplay);
	glutIdleFunc (myglIdle);
	glutKeyboardFunc (myglKeyboard);
	glutMouseFunc   ( myglMouse ); 
	glutMotionFunc( myglMotion );
	glutReshapeFunc (myglReshape);
}

void myglLight(void)
{
/* 	GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; //set the light specular to white */
	GLfloat whiteSpecularLight0[] = {0.5, 0.5, 0.5}; //set the light specular to white
	GLfloat whiteSpecularLight2[] = {0.1, 0.1, 0.1}; //set the light specular to white
	GLfloat blackAmbientLight[] = {0.2, 0.2, 0.2}; //set the light ambient to black
/* 	GLfloat whiteAmbientLight[] = {1.0, 1.0, 1.0}; //set the light ambient to white */
	GLfloat whiteDiffuseLight[] = {0.8, 0.8, 0.8}; //set the diffuse light to white
	GLfloat whiteDiffuseLight2[] = {0.1, 0.1, 0.1}; //set the diffuse light to white
/* 	GLfloat greenDiffuse[]={0.0, 1.0, 0.0, 1.0}; */

	GLfloat lmodel_ambient[]={0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	GLfloat light_position1[] = { -2000.0, 1600.0, 2000.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_SPECULAR, whiteSpecularLight0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, blackAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteDiffuseLight);
	glLightfv (GL_LIGHT1, GL_POSITION, light_position1);

	//GLfloat light_position2[] = { -2000.0, 1600.0, 2000.0, 1.0 };
	GLfloat light_position2[] = { -2000.0, -2000.0, 2000.0, 1.0 };
	glLightfv(GL_LIGHT2, GL_SPECULAR, whiteSpecularLight2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, blackAmbientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, whiteDiffuseLight2);
	glLightfv (GL_LIGHT2, GL_POSITION, light_position2);

	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
/* 	glEnable (GL_LIGHT1); */
	glEnable (GL_LIGHT2);
}

void myglInit(void)
{
	//glClearColor (0.2,0.2,0.3,1.0);
	//glClearColor (0.1,0.1,0.1,1.0); // grey
/* 	glClearColor (1,1,1,1.0); // white */
	glClearColor (0.0,0.0,0.0,1.0); // black

	glColorMaterial(GL_BACK, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glEnable (GL_DEPTH_TEST);
/* 	glEnable (GL_LIGHTING); */
}

void myglView(void)
{
	gluLookAt (0.0, vr, 200.0,
			   0.0, 0.0, 100.0,
			   0.0, 0.0, 1.0);
	glRotatef(vv, 1.0, 0.0, 0.0);
	glRotatef(vh, 0.0, 0.0, 1.0);
}

void myglShowlight(void)
{
	GLfloat white[] = {1.0, 1.0, 1.0};
	GLfloat *lp[3];
	lp[0] = light_position0;
	lp[1] = light_position1;
	lp[2] = light_position2;

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);

	for(int i=0; i<3; i++){
	glPushMatrix();
	{
		glTranslatef( lp[i][0], lp[i][1], lp[i][2]);
		glutSolidSphere(25,16,16);
	}
	glPopMatrix();
	}

	glPopMatrix();
}

void myglDisplay (void)
{
	glClearDepth(1);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	myglView();
	myglLight();

	// Show Light Position
	myglShowlight();

	draw();
	glutSwapBuffers();
}

void myglReshape (int w, int h)
{
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100000.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

void myglKeyboard (unsigned char key, int x, int y)
{
	switch(key){
	case '+':
		porm = 1.0;
		break;
	case '-':
		porm = -1.0;
		break;
	}

	switch(key)	{
	case 'x':
		sp.move(porm, 0, 0);
		break;
	case 'y':
		sp.move(0, porm, 0);
		break;
	case 'z':
		sp.move(0, 0, porm);
		break;
	case '1':
		sp.roll( DEG2RAD(porm) );
		break;
	case '2':
		sp.pitch( DEG2RAD(porm) );
		break;
	case '3':
		sp.yaw( DEG2RAD(porm) );
		break;
	case 'r':
		sp.reset();
		break;
	case 27:
	case 'q':
		exit(0);
	}
}

void myglProcessHits (GLint hits, GLuint buffer[])
{
/* 	int i; */
/* 	printf("hits = %d\n", hits); */
/* 	for(i=0;i<hits;i++){ */
/* 		printf("buffer[%d] = %d\n", i, buffer[i]); */
/* 	} */

/*   int i; */
/*   unsigned int j; */
  GLuint names, *ptr;

/*   printf("hits = %d\n", hits); */
  ptr = (GLuint *) buffer;
/*   for (i = 0; i < hits; i++) {  /\* for each hit  *\/ */
    names = *ptr;
/*     printf(" number of names for hit = %d\n", names); */
    ptr++;
/*     printf("  z1 is %g;", (float) *ptr/0xffffffff); */
    ptr++;
/*     printf(" z2 is %g\n", (float) *ptr/0xffffffff); */
    ptr++;
/*     printf("   the name is "); */
/* 	njoint = *ptr-1; */
/*     for (j = 0; j < names; j++) {  /\* for each name *\/ */
/*       printf("%d ", *ptr); */
/*       ptr++; */
/*     } */
/*     printf("\n"); */
/*   } */
/* 	if(njoint<0) njoint=-1; */
/* 	if(njoint>6) njoint=6; */
}

void myglSelection(int x, int y)
{
   GLuint selectBuf[BUFSIZE];
   GLint hits=-1;
   GLint viewport[4];
   float current_aspect=0.0;
   glGetIntegerv (GL_VIEWPORT, viewport);
   glSelectBuffer (BUFSIZE, selectBuf);
   (void) glRenderMode (GL_SELECT);

   glInitNames();
   glPushName(0);

   glMatrixMode (GL_PROJECTION);

   glPushMatrix ();{
		glLoadIdentity ();
		gluPickMatrix ((GLdouble) ( x),  (GLdouble) (viewport[3] - y),
					   5.0, 5.0, viewport);
		current_aspect = (float)viewport[2]/(float)viewport[3];
		gluPerspective (60, current_aspect, 1.0, 100000.0);
/* 		gluPerspective(60, current_aspect, 1.0, 100.0); */
		glMatrixMode (GL_MODELVIEW);

		draw();
		glMatrixMode (GL_PROJECTION);
   }
   glPopMatrix ();

   hits = glRenderMode (GL_RENDER);
   myglProcessHits (hits, selectBuf);
   glMatrixMode (GL_MODELVIEW);
/*    glutPostRedisplay(); */
}

void myglMouse(int button, int state, int x, int y){
	clicked = state; nbutton=button;
	if(clicked==1){
		switch(button){
		case GLUT_LEFT_BUTTON:
/* 			printf("Select\n"); */
			myglSelection(x, y);
			break;
		case 3:
/* 			printf("up\n"); */
			break;
		case 4:
/* 			printf("down\n"); */
			break;
		}
	}
}

void myglMotion(int x, int y){
	int dx=0,dy=0;
	//double C1,C2,S1,S2;
	if(clicked == 0){
		dx = x - bmx;
		dy = y - bmy;
//		printf("%d,%d\n",dx,dy);
		if( abs(dx) > 50 || abs(dy) > 50 ){
			dx=0;dy=0;
		}
		switch(nbutton) {
		case GLUT_RIGHT_BUTTON:
			vr +=(10*dy);
			if(vr<100) vr=100;
			if(vr>10000) vr=10000;
			glutPostRedisplay();
			break;
		case GLUT_LEFT_BUTTON:
			//case GLUT_MIDDLE_BUTTON:
			vh += dx; 
			vv -= dy;
			glutPostRedisplay();
			break;
		}
		bmx = x; bmy = y;
	}
}

void myglIdle(void)
{
	myglDisplay();
}

void SetNormal(double *p1,double *p2,double*p3,double *normal)
{
	//double normal[3];
	double x1=p1[0]-p2[0],x2=p2[0]-p3[0];
	double y1=p1[1]-p2[1],y2=p2[1]-p3[1];
	double z1=p1[2]-p2[2],z2=p2[2]-p3[2];
	double det=0;
	int i;

	normal[0]=y1*z2-y2*z1;
	normal[1]=z1*x2-z2*x1;
	normal[2]=-x1*y2+x2*y1;
	
	for(i=0;i<3;i++){
		det += normal[i]*normal[i];
	}
	
	det = sqrt(det);

	for(i=0;i<3;i++){
		normal[i] /= det;
	}
	normal[2] = - normal[2];
}


/************************************/
/*ox,oy,oz : origin position        */
/*	axisl: length of every axis     */
/*	r: arrow                        */
/************************************/
void myglOrigin(double ox, double oy, double oz, double axisl, double r)
{
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(ox,oy,oz);
		glBegin(GL_LINES);
		// x-axis
		glColor3f(1,0,0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(axisl, 0.0, 0.0);
		glEnd();
		glPushMatrix();
		glTranslatef(axisl, 0.0, 0.0);
		glRotatef(90, 0,1,0);
		glutSolidCone( r, 4*r, 8, 8);
		glPopMatrix();
		// y-axis
		glBegin(GL_LINES);
		glColor3f(0,1,0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, axisl, 0.0);
		glEnd();
		glPushMatrix();
		glTranslatef(0.0, axisl, 0.0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone( r, 4*r, 8, 8);
		glPopMatrix();
		// z-axis
		glBegin(GL_LINES);
		glColor3f(0,0,1);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, axisl);
		glEnd();
		glPushMatrix();
		glTranslatef(0.0, 0.0, axisl);
		glutSolidCone( r, 4*r, 8, 8);
		glPopMatrix();
		// origin point

		glColor3f(1,0,0);
		glutSolidSphere(r, 8, 8);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}
