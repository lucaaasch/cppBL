#ifndef _TFILES_T_
#define _TFILES_T_

#include <iostream>
#include <stdio.h>

// Escribe un registro en un archivo (Ejercicio 1.4.1.1.)

template<typename T>
void write(FILE* f, T t)
{
   fseek(f,0,SEEK_CUR);
   fwrite(&t,sizeof(T),1,f);
}

// Retorna un registro leido del archivo (Ejercicio 1.4.1.2.)

template<typename T>
T read(FILE* f)
{
   fseek(f,0,SEEK_CUR);
   T t;
   fread(&t,sizeof(T),1,f);
   return t;
}

// Establece la posicion del archivo en un determinado registro (Ejercicio 1.4.1.3.)

template<typename T>
void seek(FILE* f, int n)
{
   fseek(f,n*sizeof(T),SEEK_SET);
}

// Retorna la cantidad de registros de un archivo (Ejercicio 1.4.1.4.)

template<typename T>
int fileSize(FILE* f)
{
   int aux = ftell(f);
   fseek(f,0,SEEK_END);
   int i = (int)ftell(f)/sizeof(T);
   fseek(f,aux,SEEK_SET);
   return i;
}

// Retorna el numero de registro en el que se encuentra el indicador de posicion (Ejercicio 1.4.1.5.)

template<typename T>
int filePos(FILE* f)
{
   return (int)ftell(f)/sizeof(T);
}

#endif