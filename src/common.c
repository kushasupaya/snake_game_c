#include "common.h"

#include <stddef.h>
#include <stdlib.h>

// TODO: define global variables needed for your snake! (part 1A)
// Definition of global variables for game status.
int g_game_over = 0;
int g_score= 0;
int g_snake_position_x =0;
int g_snake_position_y = 0;
enum input_key g_snake_direction = INPUT_NONE;
size_t g_board_height, g_board_width = 0;
/** Sets the seed for random number generation.
 * Arguments:
 *  - `seed`: the seed.
 */
void set_seed(unsigned seed) {
    /* DO NOT MODIFY THIS FUNCTION */
    srand(seed);
    /* DO NOT MODIFY THIS FUNCTION */
}

/** Returns a random index in [0, size)
 * Arguments:
 *  - `size`: the upper bound for the generated value (exclusive).
 */
unsigned generate_index(unsigned size) {
    /* DO NOT MODIFY THIS FUNCTION */
    return rand() % size;
    /* DO NOT MODIFY THIS FUNCTION */
}
