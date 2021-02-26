#ifndef MYGL_H
#define MYGL_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "myconfig.h"

void myglConfig(int argc, char **argv);

void myglLight(void);
void myglInit(void);
void myglView(void);
void myglShowlight(void);
void myglDisplay (void);
void myglReshape (int w, int h);
void myglKeyboard (unsigned char key, int x, int y);
void myglProcessHits (GLint hits, GLuint buffer[]);
void myglSelection(int x, int y);
void myglMouse(int button, int state, int x, int y);
void myglMotion(int x, int y);
void myglIdle(void);
void myglOrigin(double ox, double oy, double oz, double axisl, double r);

void SetNormal(double *p1,double *p2,double*p3,double *normal);


#endif
