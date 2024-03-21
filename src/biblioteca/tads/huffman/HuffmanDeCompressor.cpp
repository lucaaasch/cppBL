#include <iostream>
#include <string>
#include <string.h>

#include "C:\Users\Lucas\Desktop\api\src\biblioteca\funciones\arrays.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\funciones\strings.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\funciones\files.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\funciones\arrays.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\funciones\lists.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\funciones\tokens.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\tads\Array.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\tads\BitReader.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\tads\BitWriter.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\tads\Coll.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\tads\List.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\tads\Map.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\tads\Mtx.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\tads\Queue.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\tads\Stack.hpp"
#include "C:\Users\Lucas\Desktop\api\src\biblioteca\tads\huffman\HuffmanSetup.hpp"

// Retorna la cantidad de bytes de un archivo

int fileBytes(FILE* f)
{
   return fileSize<unsigned char>(f);
}

// init function

HuffmanTable huffmanTable(unsigned int n, string cod)
{
   HuffmanTable hT;
   hT.n=n;
   hT.cod=cod;
   return hT;
}

int cmpHuffmanTreeInfoOrder(HuffmanTreeInfo* a,HuffmanTreeInfo* b)
{
    int frst = a->n-b->n;
    int scnd = a->c-b->c;
    if(frst==0)
    {
        return scnd;
    }
    return frst;
}

int cmpHuffmanTreeInfoFind(HuffmanTreeInfo* a, unsigned int b)
{
    return a->c-b;
}

int cmpHuffmanTableFind(HuffmanTable a, unsigned char b)
{
    return a.n-b;
}

int cmpHuffmanTableFind2(HuffmanTable a, string cod)
{
    return cmpString(a.cod,cod);
}

int cmpHuffmanTableOrder(HuffmanTable a, HuffmanTable b)
{
    return length(a.cod)-length(b.cod);
}

void byteDiscover(unsigned int c,List<HuffmanTreeInfo*>& lByte)
{
    HuffmanTreeInfo** hti = listFind<HuffmanTreeInfo*,unsigned int>(lByte,c,cmpHuffmanTreeInfoFind);
    if(hti==NULL)
    {
        HuffmanTreeInfo* x = huffmanTreeInfo(c,0,NULL,NULL);
        hti = listAdd<HuffmanTreeInfo*>(lByte,x);
    }
    (*hti)->n++;
}

List<HuffmanTreeInfo*> createByteList(FILE* f)
{
    List<HuffmanTreeInfo*> lByte = list<HuffmanTreeInfo*>();
    unsigned int c = (unsigned int)read<unsigned char>(f);

    while(!feof(f))
    {   
        byteDiscover(c,lByte);
        c = (unsigned int)read<unsigned char>(f);
    }

    return lByte;
}

HuffmanTreeInfo* byteListToHuffmanTree(List<HuffmanTreeInfo*> lByte)
{
    listSort<HuffmanTreeInfo*>(lByte,cmpHuffmanTreeInfoOrder);
    while(listSize(lByte)>1)
    {
        HuffmanTreeInfo* lft = listRemoveFirst<HuffmanTreeInfo*>(lByte);
        HuffmanTreeInfo* rgt = listRemoveFirst<HuffmanTreeInfo*>(lByte);

        HuffmanTreeInfo* ast = huffmanTreeInfo(256,rgt->n+lft->n,lft,rgt);
        listOrderedInsert<HuffmanTreeInfo*>(lByte,ast,cmpHuffmanTreeInfoOrder);
    }
    HuffmanTreeInfo* root = lByte.p->info;
    listFree<HuffmanTreeInfo*>(lByte);
    return root;
}

List<HuffmanTable> rootToHuffmanTable(HuffmanTreeInfo* root)
{
    HuffmanTree hTree = huffmanTree(root);
    List<HuffmanTable> lHTable = list<HuffmanTable>();
    string cod;

    while(huffmanTreeHasNext(hTree))
    {
        HuffmanTreeInfo* hTINext = huffmanTreeNext(hTree,cod);
        HuffmanTable hTable = huffmanTable(hTINext->c,cod);
        listAdd<HuffmanTable>(lHTable,hTable);
    }

    listSort<HuffmanTable>(lHTable,cmpHuffmanTableOrder);
    return lHTable;
}

unsigned char codSize(HuffmanTable* x)
{
    int a = length(x->cod);
    return (unsigned char)a;
}

void generateMetadata(FILE* f,FILE* fHuf, List<HuffmanTable> lHTable)
{
    unsigned short leafCount = listSize<HuffmanTable>(lHTable);
    write<unsigned short>(fHuf,leafCount);
    listReset<HuffmanTable>(lHTable);
    while(listHasNext<HuffmanTable>(lHTable))
    {
        HuffmanTable* x = listNext<HuffmanTable>(lHTable);
        unsigned short cS = codSize(x);
        unsigned int codNum = stringToInt(x->cod,2);
        write<unsigned char>(fHuf,x->n);
        write<unsigned short>(fHuf,cS);
        write<unsigned int>(fHuf,codNum);
    }
    unsigned int fSize = fileBytes(f);
    write<unsigned int>(fHuf,fSize);
}

string compressByte(unsigned char c, List<HuffmanTable> lHTable)
{
    HuffmanTable* hTable = listFind<HuffmanTable,unsigned char>(lHTable,c,cmpHuffmanTableFind);
    return hTable->cod;
}

void loadCompressedData(FILE* f,FILE* fHuf, List<HuffmanTable> lHTable)
{
    seek<int>(f,0);
    BitWriter bW = bitWriter(fHuf);
    unsigned char c = read<unsigned char>(f);
    while(!feof(f))
    {
        string cod = compressByte(c,lHTable);
        bitWriterWrite(bW,cod);
        if(length(bW.s)%8==0)
        {
            bitWriterFlush(bW);
        }
        c = read<unsigned char>(f);
    }
    bitWriterFlush(bW);
}

void generateHuffmanFile(FILE* f, List<HuffmanTable> lHTable,string fName)
{
    fName+=".huf";
    char arr[length(fName)];
    strcpy(arr,fName.c_str());

    FILE* fHuf = fopen(arr,"w+b");

    // Se generan y escriben los datos del arbol

    generateMetadata(f,fHuf,lHTable);

    // Se carga la información recodificada

    loadCompressedData(f,fHuf,lHTable);

    fclose(fHuf);
}

void huffmanCompressor(string fName)
{
    char arr[length(fName)];
    strcpy(arr,fName.c_str());
    FILE* f = fopen(arr,"r+b");

    cout << "Leyendo archivo..." << endl;

    // Se crea la lista de bytes con sus ocurrencias

    List<HuffmanTreeInfo*> lByte = createByteList(f);

    // Se obtiene, a partir de la lista, la raíz del árbol de Huffman

    HuffmanTreeInfo* root = byteListToHuffmanTree(lByte);

    // Se convierte a la raiz en una tabla con los datos de las hojas

    List<HuffmanTable> lHTable = rootToHuffmanTable(root);

    cout << "Generando archivo comprimido..." << endl;

    // Se genera el archivo comprimido

    generateHuffmanFile(f,lHTable,fName);

    cout << "Archivo comprimido." << endl;
}

string regToCod(unsigned short cS,unsigned int codNum)
{
    string cod = _binToString<unsigned int>(codNum);
    return substring(cod,(int)(length(cod)-cS));
}

List<HuffmanTable> readHuffmanTable(FILE* f)
{
    List<HuffmanTable> lHTable = list<HuffmanTable>();
    int leafCount = (int)read<unsigned short>(f);
    for(int i=0;i<leafCount;i++)
    {
        unsigned char byte = read<unsigned char>(f);
        unsigned short cS = read<unsigned short>(f);
        unsigned int codNum = read<unsigned int>(f);
        string cod = regToCod(cS,codNum);
        listAdd<HuffmanTable>(lHTable,huffmanTable(byte,cod));
    }
    listSort<HuffmanTable>(lHTable,cmpHuffmanTableOrder);
    return lHTable;
}

bool isLeaf(HuffmanTreeInfo* aux)
{
    if(aux->left==NULL && aux->right==NULL)
    {
        return true;
    }
    return false;
}

unsigned char decode(HuffmanTreeInfo* root,BitReader& bR)
{
    string provCod;
    HuffmanTreeInfo* aux = root;
    while(!isLeaf(aux))
    {
        provCod+=intToString(bitReaderRead(bR));
        aux = provCod[length(provCod)-1]=='1'?aux->right:aux->left;
    }
    return aux->c;
}

void decompress(FILE* f, HuffmanTreeInfo* root,string fName)
{
    fName = substring(fName,0,length(fName)-4);
    char arr[length(fName)];
    strcpy(arr,fName.c_str());

    FILE* fD = fopen(arr,"w+b");
    unsigned int fSize = read<unsigned int>(f);
    BitReader bR = bitReader(f);

    cout << "Descomprimiendo el archivo..." << endl;

    for(int i=0;i<(int)fSize;i++)
    {
        unsigned char leafByte = decode(root,bR);
        write<unsigned char>(fD,leafByte);
    }

    cout << "Archivo descomprimido." << endl;

    fclose(fD);
}

void leafPut(HuffmanTreeInfo* aux,HuffmanTable* hT,string cod)
{
    if(cod=="1")
    {
        aux->right = huffmanTreeInfo(hT->n,0,NULL,NULL);
    }
    else
    {
        aux->left = huffmanTreeInfo(hT->n,0,NULL,NULL);
    }
}

void leafDiscover(HuffmanTable* hT,HuffmanTreeInfo* root)
{
    string cod = hT->cod;
    HuffmanTreeInfo* aux = root;
    HuffmanTreeInfo* ant = NULL;
    while(length(cod)>1)
    {
        char num = cod[0];
        cod = removeAt(cod,0);

        ant = aux;
        aux = num=='1'?aux->right:aux->left;
        if(aux==NULL)
        {
            aux = huffmanTreeInfo(256,0,NULL,NULL);
        }
        if(num=='1')
        {
            ant->right = aux;
        }
        else
        {
            ant->left = aux;
        }
    }
    leafPut(aux,hT,cod);
}

HuffmanTreeInfo* huffmanTableToRoot(List<HuffmanTable> lHTable)
{
    HuffmanTreeInfo* root = huffmanTreeInfo(256,0,NULL,NULL);
    listReset<HuffmanTable>(lHTable);
    while(listHasNext<HuffmanTable>(lHTable))
    {
        HuffmanTable* hT = listNext<HuffmanTable>(lHTable);
        leafDiscover(hT,root);
    }
    return root;
}

void huffmanDecompressor(string fName)
{
    char arr[length(fName)];
    strcpy(arr,fName.c_str());
    FILE* f = fopen(arr,"r+b");

    // Se interpretan los primeros registros del archivo y se cargan en una tabla

    List<HuffmanTable> lHTable = readHuffmanTable(f);

    // Se convierte a la tabla en raíz del árbol de Huffman

    HuffmanTreeInfo* root = huffmanTableToRoot(lHTable);

    // Se descomprimen y escriben los datos

    decompress(f,root,fName);

    fclose(f);
}

int main(int argc,char** argv)
{
    string fName = argv[1];
    
    if(!endsWith(fName,".huf"))
    {
        huffmanCompressor(fName);
    }
    else
    {
        huffmanDecompressor(fName);
    }
    
    return 0;
}