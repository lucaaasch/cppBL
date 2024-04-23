# CPP Basic Library

CPP Basic Library (cppBL) es una biblioteca básica que desarrollé a lo largo de 2023 como proyecto en la materia de Algoritmos y Estructuras de Datos. Esta biblioteca proporciona una serie de funciones y estructuras de datos esenciales para la programación estructurada en C++.

## Funcionalidades Principales

La biblioteca incluye las siguientes funcionalidades principales:

### Funciones

- Manejo de arrays con `arrays.hpp`
- Manipulación de cadenas de caracteres con `strings.hpp`
- Operaciones con archivos con `files.hpp`
- Trabajo con listas con `lists.hpp`
- Análisis de tokens con `tokens.hpp`

### Tipos Abstractos de Datos (TADs)

- Array: `Array.hpp`
- Lector de bits: `BitReader.hpp`
- Escritor de bits: `BitWriter.hpp`
- Colección: `Coll.hpp`
- Lista: `List.hpp`
- Mapa: `Map.hpp`
- Matriz: `Mtx.hpp`
- Cola: `Queue.hpp`
- Pila: `Stack.hpp`

## Uso

Para usar el TAD BigInt, simplemente incluye el archivo `cppBL.hpp` en tu proyecto de C++ y utiliza las funciones proporcionadas según sea necesario.

```cpp
#include "cppBL.hpp"

int main() {

    // Aqui puedes utilizar cualquiera de las funciones o TADs, por ejemplo:

    Array<int> arr = array<int>();

    FILE*f = fopen(f,"r+b");

    while(!feof(f)){
        int x = read<int>(f);
        arrayAdd<int>(x);
    }

    return 0;
}
```
> Notese que "cppBL.hpp" incluye todos los headers, en caso de necesitar solo algunos, puedes incluirlos directamente.

## Información Adicional

¡Te invito a probar la biblioteca a través de dos proyectos que desarrollé simultáneamente con esta biblioteca!

- **TAD BigInt**: Este proyecto es una implementación de BigInt, una representación de enteros de tamaño arbitrario en C++. Utiliza las funciones de coll, strings y tokens de la libreria. Puedes encontrar el proyecto [aquí](https://github.com/lucaaasch/TAD-BigInt).

- **Huffman DeCompressor**: El Huffman DeCompressor es una aplicación para la descompresión de archivos utilizando el algoritmo de compresión de Huffman. Este proyecto utiliza cppBL en su totalidad. Puedes explorar el proyecto  [aquí](https://github.com/lucaaasch/Huffman-DeCompressor).

> Ambos proyectos vienen con los includes necesarios, pero sientete en la libertad de usar esta libreria para probarlos.

La librería fue desarrollada en conjunto con [@msantucho1](https://github.com/msantucho1).

¡Espero que encuentres útiles estos proyectos y disfrutes explorando cppBL!



