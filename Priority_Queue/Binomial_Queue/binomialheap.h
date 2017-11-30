#ifndef _BINOMIAL_QUEUE_H
#define _BINOMIAL_QUEUE_H

//定义二项队列最大包含二项树个数
#define MaxSize 30

//定义二项队列最大容量
#define Capacity 1073741823

//自定义节点元素类型
typedef int Elemtype;

//元素节点
struct BinNode;
typedef struct BinNode node;
typedef node *BinTree;
typedef node *Position;

//二项队列
struct Collection;
typedef struct Collection *BinQueue;

//初始化二项队列
BinQueue Initialize();

//判断二项队列是否为空
int IsEmpty(BinQueue H);

//判断二项队列是否满
int IsFull(BinQueue H);

//将元素X插入二项队列中
void Insert(Elemtype X, BinQueue H);

//找到二项队列最小元素并返回
Elemtype  FindMinValue(BinQueue H);

//找到二项队列最小元素所在下标并返回
int FindMinIndex(BinQueue H);

//销毁二项队列
void DestroyQueue(BinQueue H);

//合并二项队列
BinQueue Merge(BinQueue H1, BinQueue H2);

//删除二项队列最小元素并返回
Elemtype DeleteMin(BinQueue H);

//打印二项队列信息
void PrintBinomialQueue(BinQueue H);


#endif
