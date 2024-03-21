#include <iostream>
#include <stdio.h>
#include <math.h>
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\funciones\strings.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\funciones\tokens.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\tads\Coll.hpp"

using namespace std;

struct BigInt
{
    string s;
};

BigInt bigInt(string s)
{
    BigInt b;
    b.s = s;
    return b;
}

string minuendoComplemento(string a)
{
    char sep = '|';
    string c = emptyTString(length(a)-2, sep);
    int i = length(a)-1;
    while(a[i] == '0')
    {
        setTokenAt(c, sep, "0",i-1);
        i--;
    }
    setTokenAt(c,sep,"10", i-1);
    i--;
    while(i>0)
    {
        setTokenAt(c,sep,"9", i-1);
        i--;
    }
    return c;
}

BigInt complementoBigInt(BigInt a)
{
    BigInt l;
    string m = minuendoComplemento(a.s), c;
    int i = 0,p;
    while(i<length(a.s)-1)
    {
        p = stringToInt(getTokenAt(m,'|',i))-charToInt(a.s[i+1]);
        c+=intToString(p);
        i++;
    }
    l = bigInt(c);
    return l;
}

int signosOperacion(BigInt a, BigInt b)
{
    if(a.s[0]=='-')
    {
        if(b.s[0]=='-')
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
    if(b.s[0]=='-')
    {
        return 3;
    }
    return 4;
}

void prepararBigInt(BigInt& a, BigInt& b)
{
    if(length(a.s)>length(b.s))
    {
        b.s = lpad(b.s,length(a.s),'0');
    }
    if(length(a.s)<length(b.s))
    {
        a.s = lpad(a.s,length(b.s),'0');
    }
}

BigInt sumaGenerica(BigInt a, BigInt b)
{
    prepararBigInt(a,b);
    BigInt sum;
    sum.s = cpad(sum.s,length(a.s)+1,'0');
    int c=0, x = length(a.s)-1, s;
    while(x>=0)
    {
        s = charToInt(a.s[x])+charToInt(b.s[x])+c;
        c = getDigit(s,1);
        s = getDigit(s,0);
        sum.s[x+1] = intToChar(s);
        x--;
    }
    if(c>0)
    {
        sum.s[x+1] = intToChar(c);
    }
    if(startsWith(sum.s,"0"))
    {
        sum.s = removeAt(sum.s,0);
    }
    return sum;
}

BigInt restarComplemento (BigInt sum, int p)
{
    int i = length(sum.s)-1;
    BigInt empty = bigInt("");
    empty.s = cpad(empty.s, length(sum.s), '0');
    BigInt aRestar = bigInt("1");
    aRestar.s = rpad(aRestar.s,p,'0');
    prepararBigInt(empty,aRestar);
    while(aRestar.s[i]=='0')
    {
        empty.s[i]=sum.s[i];
        i--;
    }
    if(sum.s[i]!='0')
    {
        empty.s[i] = intToChar(charToInt(sum.s[i]) - 1);
        i--;
        while(i>=0)
        {
            empty.s[i]=sum.s[i];
            i--;
        }
    }
    if(sum.s[i]=='0')
    {
        empty.s[i] = intToChar(charToInt(sum.s[i])+10 - charToInt(aRestar.s[i]));
        i--;
        while(i>=0)
        {
            if(sum.s[i+1]=='0')
            {
                if(sum.s[i]!='0')
                {
                    empty.s[i] = intToChar(charToInt(sum.s[i])-1);
                }
                else
                {
                    empty.s[i] = intToChar(9);
                }
            }
            else
            {
                empty.s[i] = intToChar(charToInt(sum.s[i]));
            }
            i--;
        }
    }
    return empty;
}

void invertirSignos(BigInt& a,BigInt& b)
{
    a = bigInt(removeAt(a.s,0));
    b = bigInt(lpad(b.s,length(b.s)+1,'-'));
}

void permutarBigInt(BigInt& a,BigInt& b)
{
    BigInt aux = a;
    a = b;
    b = aux;
}

int cmpBigInt(BigInt a,BigInt b)
{
    if(startsWith(a.s,"-"))
    {
        a.s = removeAt(a.s,0);
    }
    if(startsWith(b.s,"-"))
    {
        b.s = removeAt(b.s,0);
    }
    prepararBigInt(a,b);
    return cmpString(a.s,b.s);
}

void prepararDatosIn(BigInt& a,BigInt& b, int sig, int& sob, bool& inverso)
{
    BigInt auxA = a;
    BigInt auxB = b;

    if(sig==1)
    {
        a.s = removeAt(a.s,0);
        b.s = removeAt(b.s,0);
    }
    if(sig==2)
    {
        if(cmpBigInt(auxA,auxB)<=0)
        {
            permutarBigInt(a,b);
            b = complementoBigInt(b);
            sob = length(b.s)+1;
            inverso = false;
        }
        if(cmpBigInt(auxA,auxB)>0)
        {
            invertirSignos(a,b);
            b = complementoBigInt(b);
            sob = length(b.s)+1;
            inverso = true;
        }
    }
    if(sig==3)
    {
        if(cmpBigInt(auxA,auxB)<0)
        {
            permutarBigInt(a,b);
            invertirSignos(a,b);
            b = complementoBigInt(b);
            sob = length(b.s)+1;
            inverso = true;
        }
        if(cmpBigInt(auxA,auxB)>=0)
        {           
            b = complementoBigInt(b);
            sob = length(b.s)+1;
            inverso = false;
        }
    } 
}

void limpiarBigInt(BigInt& a)
{
    while(a.s[0]=='0')
    {
        a.s = removeAt(a.s,0);
    }
    if(isEmpty(a.s))
    {
        a.s="0";
    }
}

void prepararDatosOut(BigInt& suma, int sig, int sob, bool inverso)
{
    if(sig==1)
    {
        limpiarBigInt(suma);
        suma.s = lpad(suma.s,length(suma.s)+1,'-');
    }
    if(sig==2 || sig==3)
    {
        if(inverso)
        {
            suma = restarComplemento(suma,sob);
            limpiarBigInt(suma);
            suma.s = lpad(suma.s,length(suma.s)+1,'-');
        }
        else
        {
            suma = restarComplemento(suma,sob);
            limpiarBigInt(suma);
        }
    }
    if(sig==4)
    {
        limpiarBigInt(suma);
    }
}

int siAlgunoEsCero(BigInt a, BigInt b)
{
    if(a.s=="0")
    {
        return 0;
    }
    if(b.s=="0")
    {
        return 1;
    }
    return -1;
}

BigInt bigIntSumar(BigInt a, BigInt b)
{
    BigInt suma;
    int sig = signosOperacion(a,b), sob;
    bool inverso;

    if(siAlgunoEsCero(a,b)==0 || siAlgunoEsCero(a,b)==1)
    {
        if(siAlgunoEsCero(a,b)==0)
        {
            return b;
        }
        else
        {
            return a;
        }
    }

    prepararDatosIn(a,b,sig,sob,inverso);
    suma = sumaGenerica(a,b);
    prepararDatosOut(suma,sig,sob,inverso);
    
    return suma;
}

string bigIntToString(BigInt a)
{
    return a.s;
}

BigInt bigIntRestar(BigInt a, BigInt b)
{
    if(startsWith(b.s, "-"))
    {
        b.s = removeAt(b.s,0);
    }
    else
    {
        if(siAlgunoEsCero(a,b)!=1)
        {
            b.s = lpad(b.s,length(b.s)+1,'-');
        }
    }
    BigInt resta = bigIntSumar(a,b);
    if(bigIntToString(resta)=="-0")
    {
        resta = bigInt("0");
    }
    return resta;
}

BigInt bigIntFromString(string s)
{
    BigInt a = bigInt(s);
    return a;
}

int main()
{
    BigInt sum = bigIntSumar(bigInt("-46969979696"),bigInt("9999999"));
    cout<<sum.s;
    return 0;
}