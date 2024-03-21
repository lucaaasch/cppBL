#ifndef _TTOKENS_T_
#define _TTOKENS_T_

#include <iostream>
#include <stdio.h>
#include "strings.hpp"
using namespace std;

// Esta funcion cuenta la cantidad de tokens en una cadena tokenizada (Ejercicio: 1.2.1.1)

int tokenCount(string s,char sep)
{
   int i;
   if(isEmpty(s))
   {
      i = 0;
   }
   else
   {
      i=charCount(s,sep)+1;
   }
   return i;
}

// Esta funcion aÃ±ade un token a una cadena tokenizada (Ejercicio:1.2.1.2)

void addToken(string& s,char sep,string t)
{
   if(isEmpty(s))
   {
      s += t;
   }
   else
   {
      s += sep + t;
   }
}

// Esta funcion devuelve un token de una cadena tokenizada (Ejercicio:1.2.1.3)

string getTokenAt(string s,char sep, int i)
{
   int d,h;
   d = indexOfN(s,sep,i);
   h = indexOfN(s,sep,i+1);
   string p; 
   p = substring(s,d+1,h);
   return p;
}

// Esta funcion remueve un token en una cadena tokenizada (Ejercicio:1.2.1.4)

void removeTokenAt(string &s,char sep, int i)
{
   s = cpad(s,length(s)+2,sep);
   int d=indexOfN(s,sep,i+1);
   s = removeAt(s,d);
   while(s[d]!=sep)
   {
      s = removeAt(s,d);
   }
   s = removeAt(s,0);
   s = removeAt(s,length(s)-1);
}

// Esta funcion reemplaza un token en una cadena tokenizada (Ejercicio:1.2.1.5)

void setTokenAt(string& s,char sep, string t,int i)
{
   string ini=substring(s,0,indexOfN(s,sep,i));
   string fin=substring(s,indexOfN(s,sep,i+1));
   if(i==0)
   {
      s = ini+t+fin;
   }
   else
   {
      s = ini+sep+t+fin;
   }
}

// Esta funcion indica el numero de token en una cadena tokenizada (Ejercicio:1.2.1.6)

int findToken(string s,char sep, string t)
{
   s = cpad(s,length(s)+2,sep);
   int i = indexOf(s,sep+t+sep);
   if(i==-1)
   {
      return -1;
   }
   string u = substring(s,0,i+1);
   return charCount(u,sep)-1;
}

string emptyTString(int x, char sep)
{
   string s;
   for(int i=0; i<x; i++)
   {
      addToken(s, sep, " ");
   }
   return s;
}

#endif