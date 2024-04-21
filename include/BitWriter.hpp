#ifndef _TARR_BITWRITER_
#define _TARR_BITWRITER_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "strings.hpp"
#include "files.hpp"

using namespace std;

struct BitWriter
{
   FILE* f;
   string s;
   int pos;
};

BitWriter bitWriter(FILE* f)
{
   return {f,"",0};
}

void bitWriterWrite(BitWriter& bw,int bit)
{
   bw.s += intToString(bit);
   bw.pos++;
}

void bitWriterWrite(BitWriter& bw,string sbit)
{
   bw.s += sbit;
   bw.pos += length(sbit);
}

void bitWriterFlush(BitWriter& bw)
{
   seek<char>(bw.f,fileSize<char>(bw.f));
   while( bw.pos%8 != 0 )
   {
      bitWriterWrite(bw,0);
   }
   while(bw.s != "")
   {
      char a = stringToInt(substring(bw.s,0,8),2);
      bw.s = substring(bw.s,8,length(bw.s));
      write<char>(bw.f,a);
   }
   bw.pos = 0;
}

#endif
