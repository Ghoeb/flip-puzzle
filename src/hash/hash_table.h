#pragma once

#include "../state/state.h"
#include <stdlib.h>
#include "hash.h"

/** Representa un nodo de una tabla de hash */
struct hash_node;
/** Representa un nodo de una tabla de hash */
typedef struct hash_node HashNode;

/** Representa un nodo de una tabla de hash */
struct hash_node
{
	/** El estado mismo */
	State state;
	/** Profundidad a la que se encuentra el estado */
	uint8_t depth;
	/** El hash del estado */
	uint64_t hash_value;
		/** El nodo que engendró a este nodo */
	HashNode* parent;
	/** La operación que engendró a este nodo */
	Operation op;
};

struct hash_table
{
	/** La tabla de hash donde se van guardando los nodos de la tabla */
	HashNode** table;
	/** Tamaño de la tabla */
	int table_size;
	/** Cantidad de elementos que tiene la tabla */
	int state_count;
};

typedef struct hash_table HashTable;

/** Inicializa la tabla de hash del tamaño especificado */
HashTable* hash_table_init     (int size);
/** Ingresa un estado a la tabla, pero solo si no ha sido visto antes */
HashNode*  hash_table_insert   (HashTable* ht, State state, uint64_t hash);
/** Libera todos los recursos asociados a la tabla */
void       hash_table_destroy  (HashTable* ht);
