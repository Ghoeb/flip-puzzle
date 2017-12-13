#pragma once

#include <stdint.h>

/****************************************************************************/
/*                                Operation                                 */
/*                                                                          */
/* Represents an operation, to be able to pass it around as a parameter.    */
/****************************************************************************/

/** States the operation type: flip row or flip column */
enum op_type
{
	flip_row = 'R',
	flip_col = 'C'
};

/** Encapsulates an operation to get from one state to another */
struct operation
{
	/** The operation type */
	enum op_type type;
	/** The index of the row / column affected */
	uint8_t index;
};
/** Encapsulates an operation to get from one state to another */
typedef struct operation Operation;


/****************************************************************************/
/*                             Global Variables                             */
/****************************************************************************/

/** Operation array with every operation */
Operation* operations;
/** Operation count */
uint8_t op_count;

/****************************************************************************/
/*                                Functions                                 */
/****************************************************************************/

/** Frees the operations list */
void  operations_destroy();
