/*
 *NAME:AVL TREE OF MAIN FUNCTION
 *TIME:2016.10.16
 *AUTHOR:LS
 */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/*
truct AVLNode;
typedef struct AVLNode Node;
typedef struct AVLNode *Position;
typedef struct AVLNode *AvlTree;

AvlTree MakeEmpty (AvlTree );
Position Find(int ,AvlTree );
Position FindMin(AvlTree );
Position FindMax(AvlTree );
AvlTree Insert(int ,AvlTree );
AvlTree Delete(int ,AvlTree);

struct AVLNode
{
        int Value;
        AvlTree Left;
        Avltree Right;
        int Height;
};
*/

int main()
{
	AvlTree T;  
	T = NULL;
	int i, n;
        n = 0;
        printf("Please input the TreeNode numbers:");
        scanf("%d",&n);                                         //输入数组大小
        int A[n];
        printf("Please input %d TreeNodes:",n);
        for(i = 0;i < n;i++)
        {
                scanf("%d",&A[i]);
        }                                                       //初始化数组
        for(i = 0;i < n;i++)
	{
		T = Insert(A[i] , T);	
	}
	
	printf("%d\n",sizeof(Node));
	
	Inorder(T);
	
	printf("\n");
	return 0;
}
