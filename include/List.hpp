#ifndef _TLIST_TAD_
#define _TLIST_TAD_

#include <iostream>
#include "lists.hpp"

using namespace std;

template<typename T>
struct List
{
   Node<T>* p;
   int cant;
   int cur;
};

template<typename T>
List<T> list()
{
   List<T> lst;
   lst.p = NULL;
   lst.cant = 0;
   lst.cur = 0;
   return lst;
}

template<typename T>
T* listAdd(List<T>& lst,T e)
{
   Node<T>* aux = add<T>(lst.p,e);
   lst.cant++;
   return &(aux->info);
}

template<typename T>
T* listAddFirst(List<T>& lst,T e)
{
   Node<T>* aux = addFirst<T>(lst.p,e);
   lst.cant++;
   return &(aux->info);
}

template<typename T,typename K>
T listRemove(List<T>& lst,K k,int cmpTK(T,K))
{
   T t = remove<T>(lst.p,k,cmpTK);
   lst.cant--;
   return t;
}

template<typename T>
T listRemoveFirst(List<T>& lst)
{
   T t = removeFirst<T>(lst.p);
   lst.cant--;
   return t;
}

template<typename T,typename K>
T* listFind(List<T> lst,K k,int cmpTK(T,K))
{
   Node<T>* aux = find<T>(lst.p,k,cmpTK);
   return &(aux->info);
}

template<typename T>
bool listIsEmpty(List<T> lst)
{
   return isEmpty<T>(lst.p);
}

template<typename T>
int listSize(List<T> lst)
{
   return lst.cant;
}

template<typename T>
void listFree(List<T>& lst)
{
   free<T>(lst.p);
   lst.cant = 0;
}

template<typename T>
T* listDiscover(List<T>& lst,T t,int cmpTT)
{
   bool e;
   Node<T>* aux = searchAndInsert<T>(lst.p,t,e,cmpTT);
   return &(aux->info);
}

template<typename T>
T* listOrderedInsert(List<T>& lst,T t,int cmpTT(T,T))
{
   Node<T>* aux = orderedInsert<T>(lst.p,t,cmpTT);
   lst.cant++;
   return &(aux->info);
}

template<typename T>
void listSort(List<T>& lst,int cmpTT(T,T))
{
   sort<T>(lst.p,cmpTT);
}

template<typename T>
void listReset(List<T>& lst)
{
   lst.cur = 0;
}

template<typename T>
bool listHasNext(List<T> lst)
{
   return lst.cur<lst.cant?1:0;
}

template<typename T>
T* listNext(List<T>& lst)
{
   Node<T>* aux = lst.p;
   for(int i=0;i<lst.cur;i++)
   {
      aux = aux->sig;
   }
   lst.cur++;
   return &(aux->info);
}

template<typename T>
T* listNext(List<T>& lst,bool& endOfList)
{
   T* t = listNext<T>(lst);
   endOfList = lst.cur==lst.cant?1:0;
   return t;
}

template <typename T>
void listDisplay(List<T> lista)
{
   display(lista.p);
}

template <typename T>
void mostrarLista(List<T> list)
{
    T* t;
    while(listHasNext<T>(list))
    {
        t = listNext<T>(list);
        cout << *t << " -> ";   
    }
}

#endif