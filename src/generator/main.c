#include "../state/state.h"
#include <stdlib.h>
#include <stdio.h>
#include "random/pcg_basic.h"
#include "../watcher/watcher.h"

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
		operations[op_count++] = (Operation){.type = flip_row, .index = row};
	}
	for(uint8_t col = 0; col < width; col++)
	{
		operations[op_count++] = (Operation){.type = flip_col, .index = col};
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

		State next = state_consolidate(state_next_temp(actual, op));
		state_destroy(actual);
		actual = next;

		watcher_operate(op);
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
