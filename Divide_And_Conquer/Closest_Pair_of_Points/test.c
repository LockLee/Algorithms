#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "closest.h"

int main()
{
	Point P[] = {{1,1}, {2,1}, {2,5}, {2,3}, {2,-1}, {2,-3}, {4,1}, {2,7}, {2,-5}, {2,9}, {2, -7}, {2,11}, {2,-9}};
	int n = sizeof(P) / sizeof(P[0]);
	printf("%f\n",closest(P, n));
	return 0;
}
