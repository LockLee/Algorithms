/*
 *NAME:CLOSEST-PAIR-OF-POINTS(O(n(lgn)2))
 *TIME:2017.12.5
 *AUTHOR:LS
 */

/*
 PROBLEM:
 We are given an array of n points in the plane,and the problem is to 
 find out the closest pair of points in the array.
 
 Input: An array of n points P[]
 Output: The smallest distance between two points in the given array.
 
 As a pre-processing step, input array is sorted according to x coordinates.

1) Find the middle point in the sorted array, we can take P[n/2] as middle point.

2) Divide the given array in two halves. The first subarray contains points from P[0] to P[n/2]. 
   The second subarray contains points from P[n/2+1] to P[n-1].

3) Recursively find the smallest distances in both subarrays. Let the distances be dl and dr. 
   Find the minimum of dl and dr. Let the minimum be d.
 
4) From above 3 steps, we have an upper bound d of minimum distance. Now we need to consider the 
   pairs such that one point in pair is from left half and other is from right half. Consider the
   vertical line passing through passing through P[n/2] and find all points whose x coordinate is 
   closer than d to the middle vertical line. Build an array strip[] of all such points.
   
5) Sort the array strip[] according to y coordinates. This step is O(nLogn). It can be optimized to O(n) 
   by recursively sorting and merging.

6) Find the smallest distance in strip[]. This is tricky. From first look, it seems to be a O(n^2) step,
   but it is actually O(n). It can be proved geometrically that for every point in strip, we only need to 
   check at most 7 points after it (note that strip is sorted according to Y coordinate). See this for more analysis.

7) Finally return the minimum of d and distance calculated in above step (step 6)
 
 */
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
