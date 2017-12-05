#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "closest.h"

/*归并排序
 *
 *详情请见： https://github.com/LockLee/Algorithms/blob/master/Sorting/Merge_Sort/merge_sort.c
 */
void merge_sortX(Point *A,int p,int r)		
{
	if(p < r)
	{
		
		int q = (r + p) / 2;		
		
		merge_sortX(A,p,q);
		merge_sortX(A,q+1,r);		
		
		mergeX(A,p,q,r);			
	}	
}

void mergeX(Point *A,int p ,int q ,int r )		
{
	int n1,n2;
	int i, j, k;				
	n1 = q -p + 1;				
	n2 = r -q ;		
	Point L[n1 + 1];
	Point R[n2 + 1];			
	
	for(i = 0;i < n1;i++)
	{
		L[i] = A[p + i];
	}
	for(j = 0;j < n2;j++)
	{
		R[j] = A[q + j + 1];		
	}
	
	L[n1].x = DBL_MAX;
	R[n2].x = DBL_MAX;			
	i = 0;
	j = 0;
	for(k = p;k < r + 1;k++)
	{
		if(L[i].x <= R [j].x)
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;			
		}
	}				
}


void merge_sortY(Point *A,int p,int r)
{
        if(p < r)
        {

                int q = (r + p) / 2;

                merge_sortY(A,p ,q);
                merge_sortY(A,q+1,r);

                mergeY(A,p,q,r);
        }

}

void mergeY(Point *A,int p ,int q ,int r )
{
        int n1,n2;
        int i, j, k;
        n1 = q -p + 1;
        n2 = r -q ;
        Point L[n1 + 1];
        Point R[n2 + 1];

        for(i = 0;i < n1;i++)
        {
                L[i] = A[p + i];
        }
        for(j = 0;j < n2;j++)
        {
                R[j] = A[q + j + 1];
        }

        L[n1].y = DBL_MAX;
        R[n2].y = DBL_MAX;
        i = 0;
        j = 0;
        for(k = p;k < r + 1;k++)
        {
                if(L[i].y <= R [j].y)
                {
                        A[k] = L[i];
                        i++;
                }
                else
                {
                        A[k] = R[j];
                        j++;
                }
        }
}

/*
 *A utility function to find the distance between two points
 *
 *param @p: A Point
 *      @q: A Point
 */
double dist(Point p, Point q)
{
	double d;
	d = sqrt((p.x - q.x)*(p.x - q.x) + (p.y - q.y)*(p.y - q.y));
	return d;
}


/*
 *A Brute Force method to return the smallest distance between two points
 *in P[] of size n;
 *
 *param @P: a array of Point
 *      @n: the size of the array
 */
double bruteForce(Point P[], int n)
{
	int i, j;
	double min = DBL_MAX;
	double dtmp;
	
	for(i = 0; i < n; i++)
	{
		for(j = i+1; j < n; j++)
		{
			dtmp = dist(P[i], P[j]);	
			if(dtmp < min)
				min = dtmp;
		}
	}
	return min;
}

// A utility function to find the distance beween the closest points of
// strip of given size. 
//All points in strip[] are sorted accordint to y coordinate. 
//They all have an upper bound on minimum distance as d.
// Note that this method seems to be a O(n^2) method, but it's a O(n)
// method as the inner loop runs at most 7 times
double stripClosest(Point strip[], int size, double d)
{
	int i, j;
	// Initialize the minimum distance as d
	double min = d;
	double dtmp;

	merge_sortY(strip, 0, size-1);
	
	// Pick all points one by one and try the next points till the difference
	// between y coordinates is smaller than d.
	// This is a proven fact that this loop runs at most 7 times
	for(i = 0; i < size; i++)
	{
		for(j = i+1; j < size && (strip[j].y - strip[i].y) < min; j++)
		{
			dtmp = dist(strip[i], strip[j]);
			if(dtmp < min)
				min = dtmp;
		}
	}
	
	return min;
}

/* A recursive function to find the smallest distance. The array P contains
 * all points sorted according to x coordinate
 *
 *param @P: a array of Point
 *      @n: the size of the array
 */
double closestUtil(Point P[], int n)
{
	int i, j, k;
	// Find the middle point
	int mid = n/2;
	double d, dl, dr;
	Point midPoint = P[mid];
	Point strip[n];	

	// If there are 2 or 3 points, then use brute force
	if(n <= 3)
		return bruteForce(P, n);
	
	// Consider the vertical line passing through the middle point
	// calculate the smallest distance dl on left of middle point and
	// dr on right side
	dl = closestUtil(P, mid);
	dr = closestUtil(P + mid, n-mid);
	
	// Find the smaller of two distances
	d = min(dl, dr);
	
	//Find the points that in strip
	for (i = 0, j = 0; i < n; i++)
	{
		if(fabs(P[i].x - midPoint.x) < d)
			strip[j++] = P[i];
	}
	
	// Find the closest points in strip.  Return the minimum of d and closest
	// distance is strip[]
	return min(d, stripClosest(strip, j, d));
}

/* The main functin that finds the smallest distance
 * This method mainly uses closestUtil()
 *
 *param @P: a array of Point
 *      @n: the size of the array
 */
double closest(Point P[], int n)
{
	int i, j;

	merge_sortX(P, 0, n-1);

	// Use recursive function closestUtil() to find the smallest distance
	return closestUtil(P, n);
}
