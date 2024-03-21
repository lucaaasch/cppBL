#ifndef _TARR_BITREADER_
#define _TARR_BITREADER_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "../funciones/strings.hpp"
#include "../funciones/files.hpp"

using namespace std;

struct BitReader
{
   FILE* f;
   int buf;
   int pos;
};

BitReader bitReader(FILE* f)
{
   return {f,0,0};
}

int bitReaderRead(BitReader& br)
{
   if(br.pos%8 == 0)
   {
      br.buf = (int)read<char>(br.f);
      br.buf = br.buf>=0?br.buf:256+br.buf;
      br.pos = 0;
   }
   int mask = pow(2,7-br.pos);
   int i = br.buf&mask;
   br.pos++;
   return i>0?1:0;
}

template<typename T>
string _binToString(T t)
{
   int fin = sizeof(T)*8-1;
   string bin;
   for (int i = 0; i<=fin; i++)
   {
      int mask = pow(2,fin-i);
      int x = (t&mask)>0?1:0;
      bin+=intToString(x);
   }
   return bin;
}

#endif