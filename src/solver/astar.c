#include <math.h>
#include "astar.h"
#include "heap.h"

/** Estima la distancia al estado final */
double state_heuristic(State state)
{
	/* Cuenta la cantidad de celdas que son distintas a lo que tienen que ser */
	double diff = 0;
	for(uint8_t row = 0; row < height; row++)
	{
		for(uint8_t col = 0; col < width; col++)
		{
			if(state[row][col] != row * width + col)
			{
				diff ++;
			}
		}
	}
	/* Divide por la cantidad máxima que se puede arreglar en una sola jugada */
	return diff / fmax(width, height);
}

/** Busca la ruta al nodo solución usando A*. Retorna NULL si no existe */
HashNode* solve(State initial, HashTable* ht)
{
	/* Inicializa lo necesario para hashear los estados */
	hash_init();

	/* Inicializa la cola de prioridades */
	Heap* heap = heap_init(7);

	/* La prioridad del estado actual */
	double priority = state_heuristic(initial);

	/* El padre del estado actual */
	heap_insert(heap, hash_table_insert(ht, initial, hash_state(initial)), priority);

	/* Si aún hay nodos sin revisar */
	while(heap -> count)
	{
		/* Obtiene el siguiente nodo a revisar */
		HashNode* parent = heap_extract(heap);

		/* Si es solución, estamos listos */
		if(parent -> hash_value == solution_hash && state_is_solution(parent -> state))
		{
			heap_destroy(heap);
			return parent;
		}

		/* Si no, se engendran sus hijos */
		for(int i = 0; i < op_count; i++)
		{
			/* Comienza la gestación del hijo de este estado */
			State fetus = state_next(parent -> state, operations[i]);

			/* Se intenta incluir en la lista de la existencia  */
			HashNode* son = hash_table_insert(ht, fetus, hash_state(fetus));

			/* Si efectivamente llegó a término */
			if(son)
			{
				/* Se establecen los vínculos */
				son -> parent = parent;
				son -> op = operations[i];
				son -> depth = parent -> depth + 1;

				/* La prioridad de este elemento */
				priority = son -> depth + state_heuristic(fetus);

				/* Se ingresa a la cola de prioridades */
				heap_insert(heap, son, priority);
			}
			/* Sino */
			else
			{
				/* Se limpian sus restos */
				state_destroy(fetus);
			}
		}
	}

	heap_destroy(heap);
	return NULL;
}
