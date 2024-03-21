
#ifndef _TMAP_TAD_
#define _TMAP_TAD_

#include <iostream>
#include "Array.hpp"

using namespace std;

template<typename K,typename V>
struct Map
{
   Array<K> keys;
   Array<V> values;
   int posK;
   int posV;
};

template<typename K,typename V>
Map<K,V> map()
{
   Map<K,V> m;
   m.keys = array<K>();
   m.values = array<V>();
   m.posK = 0;
   m.posV = 0;
   return m;
}

template<typename T>
int cmpTT(T a,T b)
{
   return a<b?-1:b<a?1:0;
}

template<typename K,typename V>
V* mapGet(Map<K,V> m,K k)
{
   int pos = arrayFind<K,K>(m.keys,k,cmpTT<K>);
   if(pos<0)
   {
      return NULL;
   }
   return arrayGet<V>(m.values,pos);
}

template<typename K,typename V>
V* mapPut(Map<K,V>& m,K k,V v)
{
   int pos = arrayFind<K,K>(m.keys,k,cmpTT<K>);
   if(pos<0)
   {
      arrayAdd<V>(m.values,v);
      pos = arrayAdd<K>(m.keys,k);
   }
   else
   {
      arraySet<V>(m.values,pos,v);
   }
   
   return arrayGet<V>(m.values,pos);
}

template<typename K,typename V>
bool mapContains(Map<K,V> m,K k)
{
   return arrayFind<K,K>(m.keys,k,cmpTT<K>)<0?0:1;
}

template<typename K,typename V>
V mapRemove(Map<K,V>& m,K k)
{
   int pos = arrayFind<K,K>(m.keys,k,cmpTT<K>);
   arrayRemove<K>(m.keys,pos);
   return arrayRemove<V>(m.values,pos);
}

template<typename K,typename V>
void mapRemoveAll(Map<K,V>& m)
{
   arrayRemoveAll<V>(m.values);
   arrayRemoveAll<K>(m.keys);
}

template<typename K,typename V>
int mapSize(Map<K,V> m)
{
   return arraySize<K>(m.keys); // mapSize da uno menos, integrar en el codigo fuente.
}

template<typename K,typename V>
bool mapHasNext(Map<K,V> m)
{
   if(m.posV<mapSize<K,V>(m) && m.posK<mapSize<K,V>(m))
   {
      return true;
   }
   return false;
}

template<typename K,typename V>
K mapNextKey(Map<K,V>& m)
{
   K* k = arrayGet<K>(m.keys,m.posK);
   m.posK++;
   return *k;
}

template<typename K,typename V>
V* mapNextValue(Map<K,V>& m)
{
   V* v = arrayGet<V>(m.values,m.posV);
   m.posV++;
   return v;
}

template<typename K,typename V>
void mapReset(Map<K,V>& m)
{
   m.posV = 0;
   m.posK = 0;
}

// Descubre las KEY, si no existe la agrega con el valor que pongas. Si la encuentra, te retorna su puntero.

template<typename K,typename V>
V* mapDiscover(Map<K,V>& m,K k,V v)
{
   if(!mapContains<K,V>(m,k))
   {
      mapPut<K,V>(m,k,v);
   }
   return mapGet<K,V>(m,k);
}

template<typename K,typename V>
void mapSortByKeys(Map<K,V>& m,int cmpKK(K,K))
{
   bool seInvirtio=true;
   while(seInvirtio)
   {
      seInvirtio=false;
      for(int i=1;i<m.keys.len;i++)
      {
         if(cmpKK(m.keys.arr[i],m.keys.arr[i-1])<0)
         {
            K auxK = m.keys.arr[i-1];
            V auxV = m.values.arr[i-1];
            m.keys.arr[i-1] = m.keys.arr[i];
            m.values.arr[i-1] = m.values.arr[i];
            m.keys.arr[i] = auxK;
            m.values.arr[i] = auxV;
            seInvirtio=true;
         }
      }
   }
}

template<typename K,typename V>
void mapSortByValues(Map<K,V>& m,int cmpVV(V,V))
{
   bool seInvirtio=true;
   while(seInvirtio)
   {
      seInvirtio=false;
      for(int i=1;i<m.values.len;i++)
      {
         if(cmpVV(m.values.arr[i],m.values.arr[i-1])<0)
         {
            K auxK = m.keys.arr[i-1];
            V auxV = m.values.arr[i-1];
            m.keys.arr[i-1] = m.keys.arr[i];
            m.values.arr[i-1] = m.values.arr[i];
            m.keys.arr[i] = auxK;
            m.values.arr[i] = auxV;
            seInvirtio=true;
         }
      }
   }
}

template <typename K, typename V>
void mostrarMap(Map<K,V> m)
{
    K k; V* v = NULL;   
    while(mapHasNext<K,V>(m))
    {
        k = mapNextKey<K,V>(m);
        cout << "La key " << k;
        v = mapNextValue<K,V>(m);
        cout << " tiene el value asociado: " << *v << endl;
    }
}

#endif
