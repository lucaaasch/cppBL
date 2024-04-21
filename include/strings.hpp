#ifndef _TSTRINGS_T_
#define _TSTRINGS_T_

#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

// Esta funcion determina la cantidad de letras de una cadena. (Ejercicio: 1.1.1.1)

int length(string s)
{
    int a=0;
    while (s[a]!='\0')
    {
        a++;
    }
    return a;
}

// Esta funcion determina cuantas veces aparece el caracter c en una cadena. (Ejercicio: 1.1.1.2)

int charCount(string s,char c)
{
    int cont=0;
    for(int i=0 ;i<length(s); i++)
    {
        if(s[i]==c)
        {
            cont++;
        }
    }
    return cont;
}

// Esta funcion crea una subcadena desde D hasta H (sin incluir) (Ejercicio: 1.1.1.3)

string substring(string s,int d,int h)
{
    string r;
    for( ;d<h;d++)
    {
        r += s[d];
    }
    return r;
}

// Esta funcion crea una subcadena desde D hasta el final de la cadena principal. (Ejercicio: 1.1.1.4)

string substring(string s,int d) // ok
{
    string r;
    for( ;d<length(s);d++)
    {
        r += s[d];
    }
    return r;
}

// Esta funcion indica la primera posicion del caracter c, sino = -1. (Ejercicio: 1.1.1.5)

int indexOf(string s,char c) // ok
{   
    for(int i=0;i<length(s);i++)
    {
        if(s[i]==c)
        {
            return i;
        }
    }
    return -1;
}

// Esta funcion dice a partir de una posicion offset, la primera vez que aparece un caracter c en una cadena. (Ejercicio: 1.1.1.6)

int indexOf(string s,char c,int offSet) 
{   
    for(;offSet<length(s); offSet++)
    {
        if(s[offSet]==c)
        {
            return offSet;       
        }
    }
    return -1;
}

//Esta funcion devuelve la posicion de una cadena dentro de otra. (Ejercicio: 1.1.1.7)

int indexOf(string s,string toSearch) // ok
{   
    int d = 0;
    for(int h = length(toSearch);h<=length(s);h++)
    {
        if(substring(s,d,h)==toSearch)
        {
            return d;
        }
        d++;
    }
    return -1;
}

// Esta funcion busca una cadena dentro de otra desde una posicion especifica. (Ejercicio: 1.1.1.8)

int indexOf(string s,string toSearch, int offset) // ok
{   
    for(int h = length(toSearch) + offset;h<=length(s);h++)
    {
        if(substring(s,offset,h)==toSearch)
        {
            return offset;
        }
        offset++;
    }
    return -1;
}

// Esta funcion devuelve la ultima posicion de un caracter en una cadena (Ejercicio: 1.1.1.9)

int lastIndexOf(string s,char c)
{
    for(int i=length(s)-1;i>=0;i--)
    {
        if(s[i]==c)
        {
            return i;
        }
    }
    return -1;
}

// Devuelve la posicion de la n-esima ocurrencia de c dentro de una cadena. (Ejercicio: 1.1.1.10)

int indexOfN(string s,char c,int n)
{
    int cont = 0;
    int pos = -1;
    for(int i=0;i<length(s);i++)
    {
        if(s[i]==c)
        {
            cont++;
            pos = cont==n?i:pos;
        }
    }
    return cont==0?pos:n>cont?length(s):pos;
}

// Devuelve el valor ASCII de una letra (Ejercicio: 1.1.1.11)

int charToInt(char c)
{
    return c<='9' && c>='0'? c-'0' : c>='A' && c<='Z'? c-'7' : c>='a' && c<='z'? c-'W' : c;
}

// Devuelve la letra correspondida a un ASCII (Ejercicio: 1.1.1.12)

char intToChar(int i)
{
   return i>=0 && i<=9? i+'0' : i>=10 && i<=35? i+'7' : i;
}

// Retorna el i-ésimo dígito del valor de n (Ejercicio: 1.1.1.13)

int getDigit (int n, int i)
{
    n=abs(n);
    int pot = 10;
    int aux = n;
    while(i>0)
    {
        pot*=10;
        i--;
    }
    aux/=pot;
    n-=(aux*pot);
    return n/(pot/10);
}

// Retorna la cantidad de dígitos que contiene el valor de n (Ejercicio: 1.1.1.14)

int digitCount(int n) 
{
    n = abs(n);
    int i = 1;
    int pot = 9;
    while(n > pot)
    {
        pot = pot*10+9;
        i++;
    }
    return i;
}

// Retorna una cadena de caracteres representando el valor i (Ejercicio: 1.1.1.15)

string intToString(int i)
{
    string s;
    s = i<0?"-":"";
    i=abs(i);
    for(int y = digitCount(i)-1; y>=0; y--)
    {
        s+=intToChar(getDigit(i,y));
    }
    return s;
}

// Esta funcion devuelve un int de una cadena (Ejercicio: 1.1.1.16)

int stringToInt(string s,int b) 
{
    int num=0;
    int pot=1;
    int total = length(s);
    for(int i=total-1;i>=0;i--)
    {
        if(i==0 && s[i]=='-')
        {
            num*=-1;
        }
        else
        {
            int dig = charToInt(s[i]);
            num += dig * pot;
            pot *= b;
        }
    }
    return num;
}

// Esta funcion devuelve un int de una cadena SOLO PARA BASE DECIMAL (Ejercicio: 1.1.1.17)

int stringToInt(string s) 
{
    int num=0;
    int pot=1;
    int total = length(s);
    for(int i=total-1;i>=0;i--)
    {
        if(i==0 && s[i]=='-')
        {
            num*=-1;
        }
        else
        {
            int dig = charToInt(s[i]);
            num += dig * pot;
            pot *= 10;
        }
    }
    return num;
}

// Esta funcion transforma un char en un string (Ejercicio: 1.1.1.18)

string charToString(char c)
{
    string s; 
    return s=c;
}

// Esta funcion pasa de un string a un char (Ejercicio: 1.1.1.19)

char stringToChar(string s)
{
    return s[0];
}

// Esta funcion devuelve un string de un string (Ejercicio: 1.1.1.20)

string stringToString(string s)
{
    return s;
}

// Esta funcion hace de un double a un string (Ejercicio: 1.1.1.21)

string doubleToString(double d)
{
    string s;
    char buffer[100];
    sprintf(buffer,"%.6f",d);
    s=buffer;
    while(s[length(s)-1]=='0')
    {
        s = substring(s,0,length(s)-1);
    }
    return s;
}

// Esta funcion hace de un string a un double (Ejercicio: 1.1.1.22)

double stringToDouble(string s)
{
    int pot1 = 1;
    double num=0;
    double pot2=10;
    for(int i = indexOf(s,'.')-1;i>=0;i--)
    {
        int dig = charToInt(s[i]);
        num += dig * pot1;
        pot1 *= 10;
    }
    for(int i2 = indexOf(s, '.')+1;i2<=length(s);i2++)
    {
        int dig = charToInt(s[i2]);
        num += dig / pot2;
        pot2 *= 10;
    }
    return num;
}

// Valida si una cadena esta vacia (Ejercicio: 1.1.1.23)

bool isEmpty(string s)
{
    return s[0]=='\0'?1:0;
}

// Esta funcion corrobora si x es prefijo de s (Ejercicio: 1.1.1.24)

bool startsWith(string s,string x)
{
   return substring(s,0,length(x))==x?1:0;
}

// Esta funcion corrobora si X es sufijo de S (Ejercicio: 1.1.1.25)

bool endsWith(string s,string x)
{
   return substring(s,length(s)-length(x))==x?1:0;
}

// Esta funcion corrobora si el caracter c esta contenido en la cadena s (Ejercicio: 1.1.1.26)

bool contains(string s,char c)
{
   return charCount(s,c)>=1?1:0;
}

// Esta funcion reemplaza todas las ocurrencias de oldChar por newChar en la cadena S. (Ejercicio: 1.1.1.27)

string replace(string s,char oldChar,char newChar)
{
    for(int i=0; i<length(s); i++)
    {
        s[i] = s[i]==oldChar?newChar:s[i];
    }
    return s;
}

// Esta funcion inserta el caracter C en la posicion indicada en la cadena S.(Ejercicio: 1.1.1.28)

string insertAt(string s,int pos,char c)
{
    return substring(s,0,pos) + c + substring(s,pos+1);
}

// Esta funcion remueve el caracter correspondiente a la posicion indicada. (Ejercicio: 1.1.1.29)

string removeAt(string s,int pos)
{
    return substring(s,0,pos) + substring(s,pos+1);
}

// Esta funcion, corta los primeros espacios en blanco de una cadena (hasta el primer caracter distinto de espacio).(Ejercicio: 1.1.1.30)

string ltrim(string s)
{
    while(s[0]==' ')
    {
        s = removeAt(s,0);
    }
    return s;
}

// Esta funcion corta los espacios finales de una cadena. (Ejercicio: 1.1.1.31)

string rtrim(string s)
{
    while(s[length(s)-1]==' ')
    {
        s = removeAt(s,length(s)-1);
    }
    return s;  
}

// Esta funcion corta los espacios de la derecha y la izquierda de una cadena s. (Ejercicio: 1.1.1.32)

string trim(string s)
{
    return s = rtrim(ltrim(s));
}

// Esta funcion replica el caracter C, N veces. (Ejercicio: 1.1.1.33)

string replicate(char c,int n)
{
    string s;
    for(int i=0;i<n;i++)
    {
        s+=c;
    }
    return s;
}

// Esta funcion replica el espacio, N veces. (Ejercicio: 1.1.1.34)

string spaces(int n)
{
    return replicate(' ',n);
}

// Esta funcion agrega caracteres c a la cadena s hasta llegar a su longitud determinada N. (Ejercicio: 1.1.1.35)

string lpad(string s,int n,char c)
{
    return replicate(c,n-length(s)) + s;
}

// Esta funcion agrega caracteres c a la derecha de la cadena hasta llegar a la longitud determinada (Ejercicio: 1.1.1.36)

string rpad(string s,int n,char c)
{
    return s + replicate(c,n-length(s));
}

// Esta funcion agrega caracteres c a la izquierda y derecha de S por igual. (Ejercicio: 1.1.1.37)

string cpad(string s,int n,char c)
{
    return lpad(s,n-(n-length(s))/2,c) + replicate(c,(n-length(s))/2);
}

// Esta funcion verifica si el char c es un digito numerico. (Ejercicio: 1.1.1.38)

bool isDigit(char c)
{
    return c>='0' && c<='9'?1:0;
}

// Esta funcion verifica si el char c es una letra. (Ejercicio: 1.1.1.39)

bool isLetter(char c)
{
   return (c>='a' && c<= 'z')||(c>='A' && c<='Z')?1:0;
}

// Esta funcion verifica si el char c es una letra mayuscula. (Ejercicio: 1.1.1.40)

bool isUpperCase(char c)
{
    return c>='A' && c<='Z'?1:0;
}

// Esta funcion verifica si el char c es una letra minuscula. (Ejercicio: 1.1.1.41)

bool isLowerCase(char c)
{
    return c>='a' && c<='z'?1:0;
}

// Convierte el char c a mayuscula. (Ejercicio: 1.1.1.42)

char toUpperCase(char c)
{
   return c-32;
}

// Convierte el char c a minuscula. (Ejercicio: 1.1.1.43)

char toLowerCase(char c)
{
   return c+32;
}

// Convierte la cadena s a mayuscula. (Ejercicio: 1.1.1.44)

string toUpperCase(string s)
{
    for(int i=0;i<length(s);i++)
    {
        if(isLowerCase(s[i]))
        {
            s[i] = toUpperCase(s[i]);
        }
    }
    return s;
}

// Convierte la cadena s a minuscula. (Ejercicio: 1.1.1.45)

string toLowerCase(string s)
{
    for(int i=0;i<length(s);i++)
    {
        if(isUpperCase(s[i]))
        {
            s[i] = toLowerCase(s[i]);
        }
    }
    return s;
}

// Establece un criterio de precedencia entre dos strings en donde, si el primero es alfabeticamente menor, retorna un negativo, etc. (Ejercicio: 1.1.1.46)

int cmpString(string a, string b)
{
    return a<b?-1:a>b?1:0;
}

// Establece un criterio de precedencia entre dos double (Ejercicio: 1.1.1.47)

int cmpDouble(double a,double b)
{
   return a-b;
}

char getCharAt(string s, int pos)
{
    return s[pos];
}

int cmpInt(int a, int b)
{
    return a-b;
}

#endif