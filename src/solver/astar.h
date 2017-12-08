#pragma once

#include "../hash/hash_table.h"

/** Busca la ruta al nodo solución usando A*. Retorna NULL si no existe */
HashNode* solve(State initial, HashTable* ht);
