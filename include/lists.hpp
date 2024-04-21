#ifndef _TLIST_T_
#define _TLIST_T_

#include <iostream>
#include <stdio.h>

using namespace std;

template <typename T>
struct Node
{
   T info;
   Node<T>* sig;
};

template <typename T>
Node<T>* add(Node<T>*& p,T e)
{
   Node<T>* nuevo = new Node<T>();
   nuevo->info = e;
   nuevo->sig = NULL;

   if(p != NULL)
   {
      Node<T>* aux = p;
      while(aux->sig != NULL)
      {
         aux = aux->sig;
      }
      aux->sig = nuevo;
   }
   else
   {
      p = nuevo;
   }

   return nuevo;
}

template <typename T>
Node<T>* addFirst(Node<T>*& p,T e)
{
   Node<T>* nuevo = new Node<T>();
   nuevo->info = e;
   nuevo->sig = p;
   p = nuevo;
   return p;
}

template <typename T, typename K>
T remove(Node<T>*& p,K k,int cmpTK(T,K))
{
   Node<T>* aux = p;
   Node<T>* ant = NULL;

   T t = aux->info;
   while(cmpTK(t,k)!=0 && aux!=NULL)
   {
      ant = aux;
      aux = aux->sig;
      t = aux->info;
   }
   if(ant == NULL)
   {
      p = aux->sig;
   }
   else
   {
      ant->sig = aux->sig;
   }
   delete aux;
   return t;
}

template <typename T>
T removeFirst(Node<T>*& p)
{
   Node<T>* aux = p;
   T t = aux->info;
   p = aux->sig;
   delete aux;
   return t;
}

template <typename T, typename K>
Node<T>* find(Node<T>* p,K k,int cmpTK(T,K))
{
   while(p!=NULL && cmpTK(p->info,k)!=0)
   {
      p=p->sig;
   }
   return p;
}

template <typename T>
Node<T>* orderedInsert(Node<T>*& p,T e,int cmpTT(T,T))
{
   Node<T>* nuevo = new Node<T>();
   nuevo->info = e;
   Node<T>* aux = p;
   Node<T>* ant = NULL;

   while(aux!=NULL && cmpTT(aux->info,e)<0)
   {
      ant = aux;
      aux = aux->sig;
   }
   if(ant==NULL)
   {
      nuevo->sig = p;
      p = nuevo;
   }
   else
   {
      ant->sig=nuevo;
      if(aux==NULL)
      {
         nuevo->sig = NULL;
      }
      else
      {
         nuevo->sig = aux;
      }
   }
   return nuevo;
}

template <typename T>
Node<T>* searchAndInsert(Node<T>*& p,T e,bool& enc,int cmpTT(T,T))
{
   Node<T>* aux = find<T,T>(p,e,cmpTT);
   enc = true;
   if(aux==NULL)
   {
      aux = orderedInsert<T>(p,e,cmpTT);
      enc = false;
   }
   return aux;
}

template <typename T>
void sort(Node<T>*& p,int cmpTT(T,T))
{
   Node<T>* e = NULL;
   Node<T>* aux = p;
   while(p!=NULL)
   {
      T min = p->info;
      while(aux!=NULL)
      {
         if(cmpTT(aux->info,min)<0)
         {
            min = aux->info;
         }
         aux=aux->sig;
      }
      remove<T>(p,min,cmpTT);
      aux = p;
      add<T>(e,min);
   }
   p = e;
}

template <typename T>
bool isEmpty(Node<T>* p)
{
   return p==NULL?1:0;
}

template <typename T>
void free(Node<T>*& p)
{
   while(p!=NULL)
   {
      removeFirst<T>(p);
   }
}

template <typename T>
Node<T>* push(Node<T>*& p,T e)
{
   return addFirst<T>(p,e);
}

template <typename T> T pop(Node<T>*& p)
{
   return removeFirst<T>(p);
}

template <typename T>
Node<T>* enqueue(Node<T>*& p,Node<T>*& q,T e)
{
   q = add<T>(p,e);
   return q;
}

template <typename T>
Node<T>* enqueue(Node<T>*& q,T e)
{
   Node<T>* n = new Node<T>();
   n->info = e;
   n->sig = q->sig;
   q->sig = n;
   q = n;
   return q;
}

template <typename T>
T dequeue(Node<T>*& p, Node<T>*& q)
{
   return removeFirst<T>(p);
}

template <typename T>
T dequeue(Node<T>*& q)
{
   Node<T>* aux = q->sig;
   q->sig = q->sig->sig;
   return removeFirst<T>(aux);
}

template <typename T>
void display(Node<T>* p)
{
   Node<T>* aux = p;
   while( aux!=NULL )
   {
      if(aux->sig != NULL)
      {
         cout<< aux->info << " -> ";
      }
      else
      {
         cout<< aux->info << endl;
      }
      aux = aux->sig;
   }
}

#endif
