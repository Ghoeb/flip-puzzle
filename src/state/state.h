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
/** Gets a next state by applying an operation to the given state */
State state_next        (State state, Operation op);
/** Indicates whether or not two states are identical */
bool  state_equals      (State a, State b);
/** Indicates whether or not a state is solution */
bool  state_is_solution (State state);
/** Frees the resources used by a state */
void  state_destroy     (State state);

/** Lee el estado inicial e inicializa las variables globales y el watcher */
/** Obtiene el estado producto de aplicar una operación */
/** Libera los recursos asociados a este estado */
/** Entrega true si y solo si el estado es solución */
/** Entrega true si y solo si ambos estados son iguales */
/** Obtiene el clon de un estado */



// State state_clone       (State dolly);

// void state_flip_col(State parent, State son, uint8_t flip_col);

// void state_flip_row(State parent, State son, uint8_t flip_row);
