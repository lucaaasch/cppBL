#ifndef _TARR_TAD_
#define _TARR_TAD_

#include <iostream>
#include <stdlib.h>
#include "../funciones/arrays.hpp"

template<typename T>
struct Array
{
   T* arr;
   int len;
   int cap;
};

template<typename T>
Array<T> array()
{
   Array<T> a;
   T* p = new T[20];
   a.arr = p;
   a.len=0;
   a.cap=20;
   return a;
}

template<typename T>
void redimensionar(Array<T>& a)
{
   T* nuevoArr = new T[a.cap+1];
   for(int i=0;i<a.len;i++)
   {
      nuevoArr[i]=a.arr[i];
   }
   delete a.arr;
   a.arr = nuevoArr;
   a.cap++;   
}

template<typename T>
int arrayAdd(Array<T>& a,T t)
{
   if(a.len==a.cap)
   {
      redimensionar<T>(a);
   }
   add<T>(a.arr,a.len,t);
   return a.len-1;
}

template<typename T>
T* arrayGet(Array<T> a,int p)
{
   return &a.arr[p];
}

template<typename T>
void arraySet(Array<T>& a,int p,T t)
{
   T* e = arrayGet<T>(a,p);
   *e = t;
}

template<typename T>
void arrayInsert(Array<T>& a,T t,int p)
{
   if(a.len==a.cap)
   {
      redimensionar<T>(a);
   }
   insert<T>(a.arr,a.len,t,p);
}

template<typename T>
int arraySize(Array<T> a)
{
   return a.len;
}

template<typename T>
T arrayRemove(Array<T>& a,int p)
{
   T t = remove<T>(a.arr,a.len,p);
   return t;
}

template<typename T>
void arrayRemoveAll(Array<T>& a)
{
   a.len=0;
}

template<typename T,typename K>
int arrayFind(Array<T> a,K k,int cmpTK(T,K))
{
   return find<T,K>(a.arr,a.len,k,cmpTK);
}

template<typename T>
int arrayOrderedInsert(Array<T>& a,T t,int cmpTT(T,T))
{
   if(a.len==a.cap)
   {
      redimensionar<T>(a);
   }
   return orderedInsert<T>(a.arr,a.len,t,cmpTT);
}

template<typename T>
T* arrayDiscover(Array<T>& a,T t,int cmpTT(T,T))
{
   int pos = arrayFind<T,T>(a,t,cmpTT);
   if(pos<0)
   {
      pos = arrayAdd<T>(a,t);
   }
   return arrayGet<T>(a,pos);
}

template<typename T>
void arraySort(Array<T>& a,int cmpTT(T,T))
{
   sort<T>(a.arr,a.len,cmpTT);
}

template <typename T>
void mostrarArray(Array<T> arr)
{
    T* x = NULL;

    for(int i = 0; i<arraySize<T>(arr);i++)
    {
        x = arrayGet<T>(arr,i);
        cout << *x << endl;
    }
}

#endif