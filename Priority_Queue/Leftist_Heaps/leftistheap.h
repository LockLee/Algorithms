#ifndef _LEFTIST_HEAP_H
#define _LEFTIST_HEAP_H

//元素之类型
typedef int Elemtype;
	
struct LeftistNode;
typedef struct LeftistNode LNode;
typedef LNode *pLNode;
typedef pLNode Leftist;

struct LeftistNode
{
	Elemtype value;
	pLNode left;
	pLNode right;
	//NULL Path Length，零路径长
	int npl;
};

//前序遍历
void PreorderLeftist(Leftist H);

//中序遍历
void InorderLeftist(Leftist H);

//后序遍历
void PostorderLeftist(Leftist H);

//返回左倾树的最小值
Elemtype GetMin(Leftist H);

//合并左倾树H1和H2
Leftist MergeLeftist(Leftist H1, Leftist H2);

//将元素X插入左倾树H中
Leftist InsertLeftist(Elemtype X, Leftist H);

//将左倾树的最小元素删除
Leftist DeleteMin(Leftist H);

//销毁左倾树
void DestroyLeftist(Leftist H);

//打印左倾树
void PrintLeftist(Leftist H);


#endif 
