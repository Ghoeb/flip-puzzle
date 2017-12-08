#include "hash_table.h"
#include <stdio.h>

/** Entrega true si los nodos corresponden al mismo estado */
static bool hash_node_equals(HashNode* a, HashNode* b)
{
	if(a -> hash_value != b -> hash_value) return false;
	return state_equals(a -> state, b -> state);
}

/** Inicializa la tabla de hash del tamaño especificado */
HashTable* hash_table_init     (int size)
{
	HashTable* ht = malloc(sizeof(HashTable));
	ht -> table = calloc(size, sizeof(HashNode*));

	ht -> state_count = 0;
	ht -> table_size = size;

	return ht;
}

static void hash_table_grow_if_needed(HashTable* ht)
{
	if(((double)(ht -> state_count)) / ((double)(ht -> table_size)) < 0.75)
	{
		return;
	}

	int old_size = ht -> table_size;

	HashNode** old_table = ht -> table;

	ht -> table_size = 2 * (ht -> table_size + 1) - 1;

	ht -> table = calloc(ht -> table_size, sizeof(HashNode*));

	/* Recorremos toda la tabla antigua */
	for(int i = 0; i < old_size; i++)
	{
		HashNode* protonode = old_table[i];

		/* Solo nos interesa si tiene algo guardado */
		if(protonode)
		{
			/* Indice en el que cae el nodo en la tabla */
			uint64_t index = protonode -> hash_value % ht -> table_size;

			/* Si la celda en la nueva tabla está ocupada, avanza */
			while(ht -> table[index])
			{
				index = (index + 1) % ht -> table_size;
			}

			ht -> table[index] = protonode;
		}
	}

	free(old_table);
}

/** Ingresa un estado a la tabla, pero solo si no ha sido visto antes */
HashNode*  hash_table_insert   (HashTable* ht, State state, uint64_t hash)
{
	/* Obtiene el hash del estado. Crea un par hash / estado para comparar */
	HashNode protonode = (HashNode)
	{
		.hash_value = hash,
		.state = state,
		.parent = NULL,
		.depth = 0
	};

	/* Indice en el que cae el nodo en la tabla */
	uint64_t index = protonode.hash_value % ht -> table_size;

	/* Si la celda está ocupada, avanza */
	while(ht -> table[index])
	{
		/* Pero si el estado ya está, entonces detenemos la inserción */
		if(hash_node_equals(&protonode, ht -> table[index]))
		{
			return NULL;
		}
		index = (index + 1) % ht -> table_size;
	}

	/* Inserta el elemento */
	HashNode* new_node = malloc(sizeof(HashNode));
	*new_node = protonode;
	ht -> table[index] = new_node;

	ht -> state_count++;

	/** Hacemos crecer la tabla de ser necesario */
	hash_table_grow_if_needed(ht);

	/* Retorna un puntero a la celda */
	return new_node;
}

/** Libera todos los recursos asociados a la tabla */
void hash_table_destroy  (HashTable* ht)
{
	printf("Registrados %d estados\n", ht -> state_count);
	for(int i = 0; i < ht -> table_size; i++)
	{
		HashNode* hn = ht -> table[i];
		if(hn)
		{
			state_destroy(hn -> state);
			free(hn);
		}
	}
	free(ht -> table);
	free(ht);
}
