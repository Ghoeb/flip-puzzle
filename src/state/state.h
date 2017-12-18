#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "operation.h"

/****************************************************************************/
/*                                  State                                   */
/*                                                                          */
/* Represents a configuration of the puzzle. Height and width are constant  */
/****************************************************************************/

/** The puzzle matrix itself */
typedef uint8_t** State;

/****************************************************************************/
/*                             Global Variables                             */
/****************************************************************************/

/** Matrix height */
uint8_t height;
/** Matrix width */
uint8_t width;

/****************************************************************************/
/*                                Functions                                 */
/****************************************************************************/

/** Reads the initial state, initializes global variables and the watcher */
State state_init        (char* filename);
/** Gets a temporal next state by applying an operation to the given state */
State state_next_temp   (State state, Operation op);
/** Gets a permanent copy of the given state */
State state_consolidate (State state);
/** Indicates whether or not two states are identical */
bool  state_equals      (State a, State b);
/** Indicates whether or not a state is solution */
bool  state_is_solution (State state);
/** Frees the resources used by a state */
void  state_destroy     (State state);
