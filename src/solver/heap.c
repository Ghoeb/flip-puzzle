#include "heap.h"
#include <stdlib.h>

/* Macros para obtener las relaciones entre indices de padres e hijos */
#define PARENT(x) ((((x) + 1) / 2) - 1)
#define LEFTSON(x) ((2 * ((x) + 1)) - 1)
#define RIGHTSON(x) (LEFTSON(x) + 1)

/** Intercambia dos elementos en el arreglo */
static void swap(HeapNode* array, int n1, int n2)
{
	HeapNode aux = array[n1];
	array[n1] = array[n2];
	array[n2] = aux;
}

/** Hace subir un elemento tanto como puede */
static void sift_up(HeapNode* array, int index)
{
	/* Mientras exista un padre para ese elemento */
	while(index > 0)
	{
		/* Posición del padre en el arreglo */
		int parent_index = PARENT(index);
		/* Compara las llaves de los distintos nodos, hace subir el más chico */
		if(array[index].heuristic < array[parent_index].heuristic)
		{
			swap(array, index, parent_index);
			index = parent_index;
		}
		/* Si no es más chico que su padre, terminó de subir */
		else
		{
			break;
		}
	}
}

/** Hace bajar un elemento tanto como puede */
static void sift_down(Heap* heap, int index)
{
	HeapNode* array = heap -> array;

	while(true)
	{
		/* Posiciones de los hijos en el arreglo */
		int left_son_index = LEFTSON(index);
		int right_son_index = RIGHTSON(index);

		/* Si el elemento tiene hijos */
		if(left_son_index < heap -> count)
		{
			/* El mejor hijo es el izquierdo */
			int son_index = left_son_index;

			/* Pero si existe derecho */
			if(right_son_index < heap -> count)
			{
				/* Y es mejor */
				if(array[right_son_index].heuristic < array[left_son_index].heuristic)
				{
					/* Entonces el mejor es el derecho */
					son_index = right_son_index;
				}
			}

			/* Si el hijo es mejor que el padre */
			if(array[son_index].heuristic < array[index].heuristic)
			{
				swap(array, index, son_index);
				index = son_index;
			}
			/* Terminó de bajar */
			else
			{
				break;
			}
		}
		/* No quedan hijos por revisar */
		else
		{
			break;
		}
	}
}

/** Hace crecer el arreglo en caso de ser necesario */
static void heap_grow_if_needed(Heap* heap)
{
	if(heap -> count == heap -> size)
	{
		heap -> size *= 2;
		HeapNode* new_array = calloc(heap -> size, sizeof(HeapNode));

		for(int i = 0; i < heap -> count; i++)
		{
			new_array[i] = heap -> array[i];
		}
		free(heap -> array);
		heap -> array = new_array;
	}
}

/** Inicializa el heap */
Heap*     heap_init(int size)
{
	Heap* heap = malloc(sizeof(Heap));
	heap -> count = 0;
	heap -> size = size;
	heap -> array =  calloc(heap -> size, sizeof(HeapNode));
	return heap;
}

/** Obtiene el siguiente elemento del heap */
HashNode* heap_extract(Heap* heap)
{
	HashNode* ret = heap -> array[0].node;
	swap(heap -> array, 0, --heap -> count);
	sift_down(heap, 0);
	return ret;
}

/** Agrega un elemento al heap */
void heap_insert(Heap* heap, HashNode* node, double heuristic)
{
	/* El nodo del heap */
	HeapNode hn =
	{
		.node = node,
		.heuristic = heuristic
	};
	/* Se inserta al final del heap */
	heap -> array[heap -> count] = hn;

	/* Se lo hace subir hasta su posición */
	sift_up(heap -> array, heap -> count++);

	/* Hace crecer al heap de ser necesario */
	heap_grow_if_needed(heap);
}

/** Libera todos los recursos asociados al heap */
void heap_destroy(Heap* heap)
{
	free(heap -> array);
	free(heap);
}
