#ifndef _TQUEUE_TAD_
#define _TQUEUE_TAD_

#include <iostream>
#include "../funciones/lists.hpp"

using namespace std;

template<typename T>
struct Queue
{
   Node<T>* p;
   Node<T>* q;
   int cant;
};

template<typename T>
Queue<T> queue()
{
   Queue<T> q;
   q.p = NULL;
   q.q = q.p;
   q.cant = 0;
   return q;
}

template<typename T>
T* queueEnqueue(Queue<T>& q,T e)
{
   Node<T>* aux = enqueue(q.p,q.q,e);
   q.cant++;
   return NULL;
}

template<typename T>
T queueDequeue(Queue<T>& q)
{
   T t = dequeue<T>(q.p,q.q);
   q.cant--;
   return t;
}

template<typename T>
bool queueIsEmpty(Queue<T> q)
{
   return isEmpty<T>(q.p);
}

template<typename T>
int queueSize(Queue<T> q)
{
   return q.cant;
}

#endif
