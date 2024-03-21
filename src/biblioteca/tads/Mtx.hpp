#ifndef _MAINHPP
#define _MAINHPP
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\funciones\strings.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\funciones\files.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\funciones\tokens.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\tads\Coll.hpp"
using namespace std;


template <typename T>
struct Mtx
{
   Coll<T> datos;
   int f;
   int c;
};

template <typename T>
Mtx<T> mtx(int f,int c,T valorDefault,string tToString(T))
{
   Mtx<T> m;
   m.c = c;
   m.f = f;

   m.datos = coll<T>();
   int x = c*f;
   for(int i=0;i<x;i++)
   {
      collAdd<T>(m.datos,valorDefault,tToString);
   }

   return m;
}

template <typename T>
int coordenadasToInt(Mtx<T> m,int f,int c)
{
   return f*m.c+c;
}

template <typename T>
T mtxGetAt(Mtx<T> m,int f,int c,T tFromString(string))
{
   int n = coordenadasToInt<T>(m,f,c);
   return collGetAt<T>(m.datos,n,tFromString);
}

template <typename T>
void mtxSetAt(Mtx<T>& m,T t,int f,int c,string tToString(T))
{
   int n = coordenadasToInt<T>(m,f,c);
   collSetAt<T>(m.datos,t,n,tToString);
}


#endif
