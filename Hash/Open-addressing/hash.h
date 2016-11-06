/*
 *NAME:HASH HEAD FILE
 *TIME:2016.11.06
 *AUTHOR:LS
 */

#ifndef _HashHead_

typedef int Type;

typedef unsigned int Index;
typedef Index Position;

struct HashEntry;
typedef struct HashEntry Node;

struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitTable(int size);
void DestoryTable(HashTable H);
Position Find(Type key,HashTable H);
void Insert(Type key,HashTable H);
void Delete(Type key,HashTable H);
Type Retrieve(Position P,HashTable H);
HashTable Rehash(HashTable H);

/* Routines such as Delete and MakeEmpty are omitted */

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

#endif


