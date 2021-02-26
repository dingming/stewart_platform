#include "mathutils.h"

///////////////// Point Class ////////////////////
Point::Point()
{
	for(int i=0; i<3; i++)
		data[i] = 0;
	data[3]=1.0;
}

Point::Point(double v[])
{
	for(int i=0; i<3; i++)
		data[i] = v[i];
	data[3]=1.0;
}

Point::Point(double x, double y, double z)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3]=1.0;
}


Point::~Point()
{
	
}

double Point::x()
{
	return data[0];
}

double Point::y()
{
	return data[1];
}

double Point::z()
{
	return data[2];
}

double Point::getat(int n)
{
	return data[n];
}

void Point::setat(int n, double v)
{
	data[n] = v;
}

void Point::set(double v[])
{
	for(int i=0; i<3; i++)
		data[i] = v[i];
	data[3]=1.0;
}

void Point::print()
{
	for(int i=0; i<4; i++){
		printf("%.4f\t", data[i]);
	}
	printf("\n\n");
}

///////////////// HTMatrix Class ////////////////////
HTMatrix::HTMatrix()
{
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			data[i][j] = (double)(i==j)*1.0;
		}
	}
}

HTMatrix::~HTMatrix()
{

}

void HTMatrix::roll(double angle)
{
	HTMatrix M;
	M.setat( 1, 1, cos(angle) );
	M.setat( 1, 2, -sin(angle) );
	M.setat( 2, 1, sin(angle) );
	M.setat( 2, 2, cos(angle) );
	*this = (*this)*M;
}

void HTMatrix::pitch(double angle)
{
	HTMatrix M;
	M.setat( 0, 0, cos(angle) );
	M.setat( 0, 2, sin(angle) );
	M.setat( 2, 0, -sin(angle) );
	M.setat( 2, 2, cos(angle) );
	*this = (*this)*M;
}

void HTMatrix::yaw(double angle)
{
	HTMatrix M;
	M.setat( 0, 0, cos(angle) );
	M.setat( 0, 1, -sin(angle) );
	M.setat( 1, 0, sin(angle) );
	M.setat( 1, 1, cos(angle) );
	*this = (*this)*M;
}

void HTMatrix::move(double x, double y, double z)
{
	HTMatrix M;
	M.setat( 0, 3, x );
	M.setat( 1, 3, y );
	M.setat( 2, 3, z );
	*this = (*this)*M;
}

void HTMatrix::setat(int r, int l, double v)
{
	data[r][l] = v;
}

void HTMatrix::print()
{
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			printf("%.4f\t", data[i][j]);
		}
		putchar('\n');
	}
}

void HTMatrix::operator=(HTMatrix m)
{
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			data[i][j] = m.data[i][j];
		}
	}
}

Point operator+(Point m1, Point m2)
{
	Point ret;
	for(int i=0; i<3; i++){
		ret.data[i] = m2.data[i] + m1.data[i];
	}
	return ret;
}

Point operator-(Point m1, Point m2)
{
	Point ret;
	for(int i=0; i<3; i++){
		ret.data[i] = m1.data[i] - m2.data[i];
	}
	return ret;
}


HTMatrix operator+(HTMatrix m1, HTMatrix m2)
{
	HTMatrix ret;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			ret.data[i][j] = m2.data[i][j] + m1.data[i][j];
		}
	}
	return ret;
}

HTMatrix operator-(HTMatrix m1, HTMatrix m2)
{
	HTMatrix ret;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			ret.data[i][j] = m1.data[i][j] - m2.data[i][j];
		}
	}
	return ret;
}

HTMatrix operator*(HTMatrix m1, HTMatrix m2)
{
	HTMatrix res;
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			res.data[i][j] = 0.0;
			for(int k=0; k<4; k++){
				res.data[i][j] += m1.data[i][k]*m2.data[k][j];
			}
		}
	}
	return res;
}

Point operator*(HTMatrix m, Point p)
{
	Point res;
	for(int i=0; i<4; i++){
		res.data[i] = 0.0;
		for(int j=0; j<4; j++){
			res.data[i] += m.data[i][j]*p.data[j];
		}
	}
	return res;
}

int point2angle(Point v1, Point v2, double *angle)
{
	double *p1 = v1.data;
	double *p2 = v2.data;
	int i;
	double d[3];
	for(i=0;i<3;i++) d[i] = p2[i]-p1[i];
	vnormalize(d, 3);
	
/* 	printf("++%f,%f,%f\t", d[0], d[1], d[2]); */
	angle[1]=atan2(sqrt(d[0]*d[0]+d[1]*d[1]), d[2]);
	if(sqrt(d[0]*d[0]+d[1]*d[1])<0.0000001) angle[0]=0.0;
	else angle[0]=atan2(d[0],d[1]);
/* 	printf("%f,%f\t%f\n", angle[0], angle[1], sqrt(d[0]*d[0]+d[1]*d[1])); */

	return 1;
}

double pointsDist(Point v1, Point v2)
{
	int i;
	double d[3];
	double dist=0.0;
	for(i=0;i<3;i++){
		d[i] = v2.data[i]-v1.data[i];
		dist += d[i]*d[i];
	}
	dist = sqrt(dist);
	return dist;
}

void vnormalize(double *v, int n)
{
	int i;
	double det=0.0;
	for(i=0;i<n;i++){
		det += v[i]*v[i];
	}
	
	det = sqrt(det);

	for(i=0;i<n;i++){
		v[i] /= det;
	}
}

