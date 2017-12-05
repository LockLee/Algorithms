#ifndef _CLOSEST_H
#define _CLOSEST_H

#define min(x, y) ((x) < (y)) ? (x) : (y)

typedef struct point Point;

struct point
{
	double x;
	double y;
};

void mergeX(Point *A,int p ,int q ,int r );
void mergeY(Point *A,int p ,int q ,int r );

void merge_sortX(Point *A,int p,int r);
void merge_sortY(Point *A,int p,int r);	

double dist(Point p, Point q);

double bruteForce(Point P[], int n);

double stripClosest(Point strip[], int size, double d);

double closestUtil(Point Px[], Point Py[], int n);

double closest(Point P[], int n);

#endif
