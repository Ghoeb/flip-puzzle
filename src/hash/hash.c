#include "hash.h"
#include <stdlib.h>
#include "../random/pcg_basic.h"

uint32_t** zobrist_matrix;

/** Precomputa lo que sea necesario para poder hashear eficientemente */
void hash_init()
{
	State solution = calloc(height, sizeof(uint8_t*));
	// zobrist_matrix = calloc(height, sizeof(uint64_t*));

	for(uint8_t row = 0; row < height; row++)
	{
		solution[row] = calloc(width, sizeof(uint8_t));
		// zobrist_matrix[row] = calloc(width, sizeof(uint64_t));

		for(uint8_t col = 0; col < width; col++)
		{
			solution[row][col] = row * width + col;
			// zobrist_matrix[row][col] = pcg32_random();
		}
	}

	solution_hash = hash_state(solution);

	state_destroy(solution);
}

/** Obtiene el hash de un estado */
uint64_t hash_state(State state)
{
	uint64_t hash = 5381;
	for(uint8_t row = 0; row < height; row++)
	{
		for(uint8_t col = 0; col < width; col++)
		{
			hash = ((hash << 5) + hash) + state[row][col];
		}
	}
	return hash;
}

/** Obtiene el hash de un estado a partir del hash anterior */
uint64_t hash_incremental(State state, uint64_t prev_hash, Operation op)
{
	if(op.type == flip_row)
	{

	}
	else
	{

	}
	abort();
}
/** Libera las cosas que sean necesarias para calcular el hash */
void hash_destroy()
{
	abort();
}
