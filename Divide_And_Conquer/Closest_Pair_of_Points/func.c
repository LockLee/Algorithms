#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "closest.h"

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


double dist(Point p, Point q)
{
	double d;
	d = sqrt((p.x - q.x)*(p.x - q.x) + (p.y - q.y)*(p.y - q.y));
	return d;
}

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

double stripClosest(Point strip[], int size, double d)
{
	int i, j;
	double min = d;
	double dtmp;
	
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

double closestUtil(Point Px[], Point Py[], int n)
{
	int i, j, k;
	int li, ri;
	int mid = n/2;
	double d, dl, dr;
	Point midPoint = Px[mid];
	Point Pyl[mid + 1];
	Point Pyr[n - mid - 1];
	Point strip[n];	

	if(n <= 3)
		return bruteForce(Px, n);
	
	for(k = 0, i = 0; i < n; i++)
	{
		if(i <= mid)
			Pyl[i] = Px[i];
		else
			Pyr[k++] = Px[i];	
	}
	
	merge_sortY(Pyl, 0, mid);
	merge_sortY(Pyr, mid+1, n-1);

	dl = closestUtil(Px, Pyl, mid);
	dr = closestUtil(Px + mid, Pyr, n-mid);
	
	d = min(dl, dr);
	
	for (i = 0, j = 0; i < n; i++)
	{
		if(fabs(Py[i].x - midPoint.x) < d)
			strip[j++] = Py[i];
	}
	
	return min(d, stripClosest(strip, j, d));
}

double closest(Point P[], int n)
{
	int i, j;
	Point Px[n];
	Point Py[n];

	for(i = 0; i < n; i++)
	{
		Px[i] = P[i];
		Py[i] = P[i];
	}
	
	merge_sortX(Px, 0, n-1);
	merge_sortY(Py, 0, n-1);

	return closestUtil(Px, Py, n);
}
