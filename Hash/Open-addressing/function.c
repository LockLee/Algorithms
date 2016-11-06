/*
 *NAME:HASH FUNCTION(OPEN ADDRESSING)
 *TIME:2016.11.06
 *AUTHOR:LS
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"

/*
typedef int Type;

typedef unsigned int Index;
typedef Index Position;

struct HashEntry;
typedef struct hashEntry Node;

struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitTable(int size);
void DestoryTable(HashTable H);
Position Find(Type key,HashTable H);
void Insert(Type key,HashTable H);
Type Retrieve(Position P,HashTable H);
HashTable Rehash(HashTable H);

//Routines such as Delete and MakeEmpty are omitted 

enum KindOfEntry
{
        Legitimate,
        Empty,
        Deleted
};

struct HashEntry
{
        Type Value;
        enum KindOfEntry Info;
};

struct HashTbl
{
        int TableSize;
        Node *TheNodes;
}; 
*/


static int Hash(Type key, int TableSize)
{
	double S,A;
	S = 2654435769.0;
	A = S/pow(2,32);
	//The multiplication method(Details for P263 of Intriduction to Algorithms)
	return (int)(TableSize * (key*A-(int)(key*A))); 
}

HashTable InitTable(int size)
{
	HashTable H;
	int i;
	
	H = (HashTable)malloc(sizeof(struct HashTbl));
	if(H == NULL)
	{
		printf("ERROE!");
		exit(1);
	}	
	
	H->TableSize = 3*size;

	H->TheNodes = (Node*)malloc(sizeof(struct HashTbl) * H->TableSize);
	if(H->TheNodes == NULL)
	{
		printf("ERROR!");
		exit(1);
	}
	
	for(i = 0; i < H->TableSize; i++)
	{
		H->TheNodes[i].Info = Empty;
	}
	
	return H;
}

Position Find(Type key, HashTable H)
{
	Position CurrentPos;
	int CollisionNum;
	
	CollisionNum = 0;
	CurrentPos = Hash(key, H->TableSize);
	while(H->TheNodes[CurrentPos].Info != Empty && H->TheNodes[CurrentPos].Value != key)
	{
		//Quadratic probing
		CurrentPos += 2* ++CollisionNum - 1;						
		if(CurrentPos >= H->TableSize)
			CurrentPos -= H->TableSize;
	}
	
	return CurrentPos;
}

void Insert(Type key, HashTable H)
{
	Position pos;
	
	pos = Find(key, H);
	if(H->TheNodes[pos].Info != Legitimate)
	{
		H->TheNodes[pos].Info = Legitimate;
		H->TheNodes[pos].Value = key;
	}
}

void Delete(Type key, HashTable H)
{
	Position pos;
	
	pos = Find(key, H);
	if(H->TheNodes[pos].Info == Legitimate)
	{
		H->TheNodes[pos].Info = Deleted;
	}
}
