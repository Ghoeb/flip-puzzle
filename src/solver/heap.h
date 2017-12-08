#pragma once

#include "../hash/hash_table.h"

/** Representa un elemento del heap */
struct heap_node;

/** Representa un elemento del heap */
typedef struct heap_node HeapNode;

/** Representa un elemento del heap */
struct heap_node
{
	/** El nodo de la tabla que guarda el estado */
	HashNode* node;
	/** La heuristica de A* */
	double heuristic;
};

/** Representa un min-heap de estados */
struct heap
{
	/** Arreglo que implícitamente contiene el arbol del heap */
	HeapNode* array;
	/** Cantidad de elementos actualmente en el heap */
	int count;
	/** Tamaño del arreglo del heap */
	int size;
};

/** Representa un min-heap de estados */
typedef struct heap Heap;

/** Inicializa el heap */
Heap*     heap_init(int size);
/** Obtiene el siguiente elemento del heap */
HashNode* heap_extract (Heap* heap);
/** Agrega un elemento al heap */
void      heap_insert  (Heap* heap, HashNode* node, double heuristic);
/** Libera todos los recursos asociados al heap */
void      heap_destroy (Heap* heap);
