#include "state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../watcher/watcher.h"

/** Lee el estado inicial e inicializa las variables globales y el watcher */
State state_init(char* filename)
{
	/* Abre el archivo en modo lectura */
	FILE* f = fopen(filename, "r");

	if(!f)
	{
		perror("Error abriendo archivo\n");
		abort();
	}

	/* Lee el nombre de la imagen */
	char buffer[32];
	fscanf(f, "%s", buffer) ? : abort();

	/* Lee las dimensiones de la matriz */
	fscanf(f, "%hhu %hhu", &height, &width) ? : abort();

	/* Abre la interfaz gráfica */
	watcher_open(buffer, height, width);

	/* Lee la matriz misma */
	State state = calloc(height, sizeof(uint8_t*));
	for(uint8_t row = 0; row < height; row++)
	{
		state[row] = calloc(width, sizeof(uint8_t));
		for(uint8_t col = 0; col < width; col++)
		{
			fscanf(f, "%hhu", &state[row][col]) ? : abort();
		}
	}

	fclose(f);

	/* Inicializa la lista de operaciones */
	operations = calloc(height + width, sizeof(Operation));

	op_count = 0;
	for(uint8_t row = 0; row < height; row++)
	{
		operations[op_count++] = (Operation){.type = flip_row, .index = row};
	}
	for(uint8_t col = 0; col < width; col++)
	{
		operations[op_count++] = (Operation){.type = flip_col, .index = col};
	}

	return state;
}

/*************************** Espacio de estados *****************************/

/** Guarda el nuevo estado producto de hacer flip row */
void state_flip_row(State parent, State son, uint8_t flip_row)
{
	for(uint8_t row = 0; row < height; row++)
	{
		/* Inicializa nueva memoria para guardar las filas */
		son[row] = calloc(width, sizeof(uint8_t));

		/* La fila afectada */
		if(row == flip_row)
		{
			/* Se invierte */
			for(uint8_t col = 0; col < width; col++)
			{
				son[row][col] = parent[row][width - 1 - col];
			}
		}
		/* Las demás */
		else
		{
			/* Se copian tal cual */
			memcpy(son[row], parent[row], width);
		}
	}
}

/** Guarda el nuevo estado producto de hacer flip col */
void state_flip_col(State parent, State son, uint8_t flip_col)
{
	for(uint8_t row = 0; row < height; row++)
	{
		/* Inicializa nueva memoria para guardar las filas */
		son[row] = calloc(width, sizeof(uint8_t));

		for(uint8_t col = 0; col < width; col++)
		{
			/* La columna afectada se invierte */
			if(col == flip_col)
			{
				son[row][col] = parent[height - 1 - row][col];
			}
			/* Las demás */
			else
			{
				/* Se copian tal cual */
				son[row][col] = parent[row][col];
			}
		}
	}
}

/** Obtiene el estado producto de aplicar una operación */
State state_next (State parent, Operation op)
{
	/** Inicializa el contenedor de las filas */
	State son = calloc(height, sizeof(uint8_t*));

	if(op.type == flip_row)
	{
		state_flip_row(parent, son, op.index);
	}
	else
	{
		state_flip_col(parent, son, op.index);
	}

	return son;
}

/********************************* Útiles ***********************************/

/** Entrega true si y solo si el estado es solución */
bool  state_is_solution(State state)
{
	for(uint8_t row = 0; row < height; row++)
	{
		for(uint8_t col = 0; col < width; col++)
		{
			if(state[row][col] != row * width + col) return false;
		}
	}
	return true;
}

/** Entrega true si y solo si ambos estados son iguales */
bool  state_equals(State a, State b)
{
	for(uint8_t row = 0; row < height; row++)
	{
		for(uint8_t col = 0; col < width; col++)
		{
			if(a[row][col] != b[row][col]) return false;
		}
	}
	return true;
}

/** Obtiene el clon de un estado */
State state_clone (State dolly)
{
	State clone = calloc(height, sizeof(uint8_t*));

	for(uint8_t row = 0; row < height; row++)
	{
		clone[row] = calloc(width, sizeof(uint8_t));
		memcpy(clone[row], dolly[row], width);
	}

	return clone;
}

/** Libera los recursos asociados a este estado */
void  state_destroy(State state)
{
	for(uint8_t row = 0; row < height; row++)
	{
		free(state[row]);
	}
	free(state);
}

/** Libera todos los recursos de la lista de operaciones */
void  operations_destroy()
{
	free(operations);
}
