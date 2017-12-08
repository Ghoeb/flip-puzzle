#include "../state/state.h"
#include <stdlib.h>
#include <stdio.h>
#include "random/pcg_basic.h"
#include "../watcher/watcher.h"

/* Máscara para obtener el primer bit del byte de operaciones */
#define ROW_MASK 0b10000000
/* Máscara para obtener los últimos 7 bits del byte de operaciones */
#define IDX_MASK 0b01111111
/** La operacion de hacer flip de la fila i */
#define ROWOP(i) (ROW_MASK | (i))
/** La operacion de hacer flip de la columna i */
#define COLOP(i) (0 | (i))
/* El indice de una operacion son sus ultimos 7 bytes */
#define INDEX(op) ((op) & IDX_MASK)
/* Si tiene un 1 en el primer bit, entonces la operacion es de fila */
#define ISROW(op) (((op) & ROW_MASK) == ROW_MASK)


int main(int argc, char **argv)
{
	if(argc != 7)
	{
		printf("Uso: %s <img> <out> <h> <w> <d> <s>\nDonde\n", argv[0]);
		printf("\timg es la imagen a desarmar\n");
		printf("\tout es la imagen que será la del problema\n");
		printf("\th es la altura de la matriz\n");
		printf("\tw es el ancho de la matriz\n");
		printf("\td es la profundidad de los cambios\n");
		printf("\ts es la semilla aleatoria\n");

		return 1;
	}

	char* img_file = argv[1];
	char* out_file = argv[2];

	printf("%s\n", out_file);

	height = atoi(argv[3]);
	width = atoi(argv[4]);

	printf("%d %d\n", height, width);

	watcher_open(img_file, height, width);

	int depth = atoi(argv[5]);
	int seed = atoi(argv[6]);

	pcg32_srandom(0x853c49e6748fea9bULL ^ seed, 0xda3e39cb94b95bdbULL);

	/* Inicializa la lista de operaciones */
	operations = calloc(height + width, sizeof(Operation));

	op_count = 0;
	for(uint8_t row = 0; row < height; row++)
	{
		operations[op_count++] = ROWOP(row);
	}
	for(uint8_t col = 0; col < width; col++)
	{
		operations[op_count++] = COLOP(col);
	}

	State actual = calloc(height, sizeof(uint8_t*));

	for(uint8_t row = 0; row < height; row++)
	{
		actual[row] = calloc(width, sizeof(uint8_t));
		for(uint8_t col = 0; col < width; col++)
		{
			actual[row][col] = row * width + col;
		}
	}

	for(int i = 0; i < depth; i++)
	{
		Operation op = operations[pcg32_boundedrand(op_count)];

		State next = state_next(actual, op);
		state_destroy(actual);
		actual = next;

		operation_watch(op);
	}
	for(uint8_t row = 0; row < height; row++)
	{
		for(uint8_t col = 0; col < width; col++)
		{
			printf("%d%c", actual[row][col], col == width - 1 ? '\n' : ' ');
		}
	}

	state_destroy(actual);

	watcher_snapshot(out_file);

	free(operations);

	watcher_close();

	return 0;
}