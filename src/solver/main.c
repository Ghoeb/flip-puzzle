#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../watcher/watcher.h"
#include "astar.h"
#include <time.h>

void follow_your_dreams(HashNode* hn)
{
	if(hn -> parent)
	{
		follow_your_dreams(hn -> parent);
		watcher_operate(hn -> op);
	}
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Modo de uso: %s <puzzle.txt>\nDonde\n", argv[0]);
		printf("\tpuzzle.txt es el archivo donde se describe el puzzle\n");
		return 1;
	}

	/* Lee el estado inicial e inicializa las variables globales */
	/* y el watcher */
	State state = state_init(argv[1]);

	HashTable* ht = hash_table_init(7);
	// HashQueue* hq = hash_queue_init(104729);

	clock_t start = clock();

	HashNode* hn = solve(state, ht);

	printf("Resuelto en %lf segundos\n", ((double)(clock() - start))/ CLOCKS_PER_SEC);

	follow_your_dreams(hn);

	hash_table_destroy(ht);

	operations_destroy();

	watcher_close();

	return 0;
}
