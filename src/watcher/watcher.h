#pragma once

#include "../state/operation.h"

/****************************************************************************/
/*                                Watcher                                   */
/*                                                                          */
/* The module in charge of problem visualization                            */
/****************************************************************************/

/** Opens a window to show an image over the given matrix */
void watcher_open     (char* img_file, int matrix_height, int matrix_width);
/** Visualizes the operation on the window */
void watcher_operate  (Operation op);
/** Generates a PNG image with the current content of the window */
void watcher_snapshot (char* filename);
/** Closes the window and frees its resources */
void watcher_close    ();
