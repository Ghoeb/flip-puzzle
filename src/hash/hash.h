#pragma once

#include "../state/state.h"
#include <stdint.h>

/** Variable Global: Hash del estado solucion */
uint64_t solution_hash;

/** Precomputa lo que sea necesario para poder hashear eficientemente */
void     hash_init();
/** Obtiene el hash de un estado */
uint64_t hash_state(State state);
/** Obtiene el hash de un estado a partir del hash anterior */
uint64_t hash_incremental(State state, uint64_t prev_hash, Operation op);
/** Libera las cosas que sean necesarias para calcular el hash */
void     hash_destroy();
