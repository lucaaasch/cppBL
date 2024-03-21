#ifndef _TARRAYS_T_
#define _TARRAYS_T_

#include <iostream>

template <typename T>
int add(T arr[],int& len,T e)
{
   arr[len++] = e;
   return len;
}

template <typename T>
void insert(T arr[],int& len,T e,int p)
{
   T aux = arr[p];
   arr[p++] = e;
   while(p<len+1)
   {
      e = aux;
      aux = arr[p];
      arr[p++]=e;
   }
   len++;
}

template <typename T>
T remove(T arr[],int& len,int p)
{
   T ret = arr[p];
   while(p<len-1)
   {
      arr[p] = arr[p+1];
      p++;
   }
   len--;
   return ret;
}

template <typename T, typename K>
int find(T arr[],int len,K k,int cmpTK(T,K))
{
   for(int i = 0; i<len; i++)
   {
      if(cmpTK(arr[i],k)==0)
      {
         return i;
      }
   }
   return -1;
}

template <typename T>
int orderedInsert(T arr[],int& len,T e,int cmpTT(T,T))
{
   int p = 0;
   while(cmpTT(arr[p],e)<0)
   {
      p++;
   }
   insert<T>(arr,len,e,p);
   return p;
}

template <typename T>
void sort(T arr[],int len,int cmpTT(T,T))
{
   bool seInvirtio=true;
   while(seInvirtio)
   {
      seInvirtio=false;
      for(int i=1;i<len;i++)
      {
         if(cmpTT(arr[i],arr[i-1])<0)
         {
            T aux = arr[i-1];
            arr[i-1] = arr[i];
            arr[i] = aux;
            seInvirtio=true;
         }
      }
   }
}



#endif
