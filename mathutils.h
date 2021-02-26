// -*- mode: c++ -*-
#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PI M_PI
#define RAD2DEG(x)		(x*(180.0/M_PI))
#define DEG2RAD(x)		(x*(M_PI/180.0))

class Point
{
public:
	double data[4];

public:
	Point();
	Point(double v[]);
	Point(double x, double y, double z);
	~Point();

	double x();
	double y();
	double z();
	double getat(int n);
	void setat(int n, double v);
	void set(double v[]);
	void print();
};

// Homogenious Transformation Matrix
class HTMatrix
{
public:
	double data[4][4];

public:
	HTMatrix();
	~HTMatrix();

	void setat(int r, int l, double v);
	void operator=(HTMatrix m);

	void roll(double angle);
	void pitch(double angle);
	void yaw(double angle);
	void move(double x, double y, double z);	

	void print();
};

Point operator+(Point m1, Point m2);
Point operator-(Point m1, Point m2);

HTMatrix operator+(HTMatrix m1, HTMatrix m2);
HTMatrix operator-(HTMatrix m1, HTMatrix m2);
HTMatrix operator*(HTMatrix m1, HTMatrix m2);
Point operator*(HTMatrix m, Point p);


int point2angle(Point v1, Point p2, double *angle);
double pointsDist(Point v1, Point v2);
void vnormalize(double *v, int n);

#endif
