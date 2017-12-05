#ifndef _CLOSEST_H
#define _CLOSEST_H

//宏定义求两个数的较小值
#define min(x, y) ((x) < (y)) ? (x) : (y)

//定义数据节点
typedef struct point Point;

struct point
{
	double x;
	double y;
};

//归并排序合并例程
void mergeX(Point *A,int p ,int q ,int r );
void mergeY(Point *A,int p ,int q ,int r );

//归并排序例程，分别按照 x 坐标和 y 坐标排序
void merge_sortX(Point *A,int p,int r);
void merge_sortY(Point *A,int p,int r);	

//求两点间距离
double dist(Point p, Point q);

//暴力求解点集中最近两点间距离
double bruteForce(Point P[], int n);

//求条带内的最近两点间距离
double stripClosest(Point strip[], int size, double d);

//找到最近点距离的主要递归函数
double closestUtil(Point P[], Point n);

//找到最近点距离的主函数
//主要调用 closestUtil()
double closest(Point P[], int n);

#endif
