/*
 *Name：Binomial Queue
 *Author：LS
 *Time：2017.9.24
 */
#include <stdio.h>
#include <stdlib.h>
#include "binomialheap.h"

int main()
{
    BinQueue H, H1, H2;    
    Elemtype data1[6] = {65, 24, 12, 51, 16, 18};    
    Elemtype data2[7] = {24, 65, 51, 23, 14, 26, 13};
    int i;
    Elemtype minvalue;

    H1 = Initialize();        
    for(i=0; i<6; i++)
    {
        Insert(data1[i], H1);
    }
    printf("\n=== after the binominal queue H1 is created ===\n");    
    PrintBinomialQueue(H1);    

  
    H2 = Initialize();        
    for(i=0; i<7; i++)
    {
        Insert(data2[i], H2);
    }
    printf("\n=== after the binominal queue H2 is created ===\n");    
    PrintBinomialQueue(H2);    
   
   
    Merge(H1, H2);
    printf("\n=== after H2 is merged into the H1 ===\n");    
    PrintBinomialQueue(H1);    
    
    
    
    printf("\n=== after executing deleteMin opeartion towards binominal queue bq1 ===\n");    
    minvalue = DeleteMin(H1);
    printf("\n===The H1 min value is %d\n",minvalue);
    PrintBinomialQueue(H1);    
    
    DestroyQueue(H2);
    DestroyQueue(H1);
    
    return  0;
}
