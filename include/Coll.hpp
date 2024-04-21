#ifndef _TCOLL_T_
#define _TCOLL_T_

#include <iostream>
#include "strings.hpp"

using namespace std;

template<typename T>
struct Coll
{
   string s;
   char sep;
   int pos;
};

template<typename T>
Coll<T> coll(char sep)
{
   Coll<T> c;
   c.s = "";
   c.sep = sep;
   c.pos = 0;
   return c;
}

template<typename T>
Coll<T> coll()
{
   Coll<T> c;
   c.s = "";
   c.sep = '|';
   c.pos = 0;
   return c;
}

template<typename T>
int collSize(Coll<T> c)
{
   int i = tokenCount(c.s, c.sep);
   return i;
}

template<typename T>
void collRemoveAll(Coll<T>& c)
{
   c.s = "";
}

template<typename T>
void collRemoveAt(Coll<T>& c, int p)
{
   removeTokenAt(c.s, c.sep, p);
}

template<typename T>
int collAdd(Coll<T>& c,T t,string tToString(T))
{
   addToken(c.s, c.sep, tToString(t));
   return tokenCount(c.s, c.sep) - 1;
}

template <typename T>
void collSetAt(Coll<T>& c,T t,int p,string tToString(T))
{
   setTokenAt(c.s, c.sep, tToString(t), p);
}

template <typename T>
T collGetAt(Coll<T> c,int p,T tFromString(string))
{
   T t;
   t = tFromString(getTokenAt(c.s, c.sep, p));
   return t;
}

template <typename T, typename K>
int collFind(Coll<T> c,K k,int cmpTK(T,K),T tFromString(string))
{
   int i = 0;
   while(cmpTK(tFromString(getTokenAt(c.s, c.sep, i)), k)!=0 && i<tokenCount(c.s, c.sep))
   {
      i++;
   }
   if(cmpTK(tFromString(getTokenAt(c.s, c.sep, i)), k)==0)
   {
      return i;
   }
   else 
   {
      return -1;
   }
}

template <typename T>
void collSort(Coll<T>& c,int cmpTT(T,T),T tFromString(string),string tToString(T))
{
   T q;
   Coll<T> p = coll<T>(c.sep);
   int i = 0, menor;
   while(tokenCount(c.s,c.sep)>0)
   {
      while(i<tokenCount(c.s,c.sep))
      {
         if(i==0)
         {
            q = tFromString(getTokenAt(c.s,c.sep,i));
            menor = i;
         }
         if(cmpTT(q,tFromString(getTokenAt(c.s,c.sep,i)))>0)
         {
            q = tFromString(getTokenAt(c.s,c.sep,i));
            menor = i;
         }
         i++;
      }
      collAdd<T>(p,q,tToString);
      i = 0;
      removeTokenAt(c.s,c.sep,menor);
   }
   c.s = p.s;
}

template<typename T>
bool collHasNext(Coll<T> c)
{
   if(c.pos < collSize<T>(c))
   {
      return true;
   }
   return false;
}

template<typename T>
T collNext(Coll<T>& c,T tFromString(string))
{
   T t;
   t = collGetAt<T>(c,c.pos,tFromString);
   c.pos+=1;
   return t;
}

template<typename T>
T collNext(Coll<T>& c,bool& endOfColl,T tFromString(string))
{
   T t;
   t = collNext(c,tFromString);
   endOfColl = collHasNext(c);
   return t;
}

template<typename T>
void collReset(Coll<T>& c)
{
   c.pos=0;
}

template<typename T>
string collToString(Coll<T> c)
{
   return c.s;
}

#endif