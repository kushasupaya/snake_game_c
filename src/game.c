#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "linked_list.h"
#include "mbstrings.h"

/** Updates the game by a single step, and modifies the game information
 * accordingly. Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: width of the board.
 *  - height: height of the board.
 *  - snake_p: pointer to your snake struct (not used until part 2!)
 *  - input: the next input.
 *  - growing: 0 if the snake does not grow on eating, 1 if it does.
 */


#include "common.h" // Include necessary headers

void move_snake(snake_t* snake_p, int* cells, size_t width, size_t height, int growing) {
    // Calculate the new head position based on the current direction
    int new_head_x = snake_p->position_x;
    int new_head_y = snake_p->position_y;

    switch (snake_p->direction) {
        case INPUT_UP:
            new_head_y--;
            break;
        case INPUT_DOWN:
            new_head_y++;
            break;
        case INPUT_LEFT:
            new_head_x--;
            break;
        case INPUT_RIGHT:
            new_head_x++;
            break;
        default:
            // Invalid direction; do nothing
            break;
    }

    // Update the snake's position
    snake_p->position_x = new_head_x;
    snake_p->position_y = new_head_y;

}

void update_snake_direction(snake_t* snake_p, enum input_key input) {
    switch(input) {
        case INPUT_UP:
            snake_p->position_y--;
            snake_p->direction = INPUT_UP;
            break;
        case INPUT_DOWN:
            snake_p -> position_y++;
            snake_p->direction = INPUT_DOWN;
            break;
        case INPUT_LEFT:
            snake_p -> position_x--;
            snake_p->direction = INPUT_LEFT;
            break;
        case INPUT_RIGHT:
            snake_p -> position_x++;
            snake_p->direction = INPUT_RIGHT;
            
            break;
        case INPUT_NONE:
            // No input received; do nothing
            break;
        default:
            // Invalid input; do nothing
            break;
    }
}



void update(int* cells, size_t width, size_t height, snake_t* snake_p,
            enum input_key input, int growing) {
    // `update` should update the board, your snake's data, and global
    // variables representing game information to reflect new state. If in the
    // updated position, the snake runs into a wall or itself, it will not move
    // and global variable g_game_over will be 1. Otherwise, it will be moved
    // to the new position. If the snake eats food, the game score (`g_score`)
    // increases by 1. This function assumes that the board is surrounded by
    // walls, so it does not handle the case where a snake runs off the board.


    // TODO: implement!
    cells[snake_p -> position_y * width + snake_p -> position_x] = FLAG_PLAIN_CELL;

    if (input == INPUT_NONE)
        input = snake_p -> direction;

    update_snake_direction(snake_p, input);
    if ( cells[snake_p -> position_x + snake_p -> position_y * width] == FLAG_FOOD){
        g_score++;
        cells[snake_p -> position_x + snake_p -> position_y * width] = FLAG_SNAKE;
        place_food(cells, width, height);
    }

    if ( cells[snake_p -> position_x + snake_p -> position_y * width] == FLAG_WALL){
        g_game_over = 1;
        cells[(snake_p -> position_x + snake_p -> position_y * width) - 1] = FLAG_SNAKE;
    }
    else{
        cells[snake_p -> position_x + snake_p -> position_y * width] = FLAG_SNAKE;
    }

}

/** Sets a random space on the given board to food.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: the width of the board
 *  - height: the height of the board
 */
void place_food(int* cells, size_t width, size_t height) {
    /* DO NOT MODIFY THIS FUNCTION */
    unsigned food_index = generate_index(width * height);
    if (*(cells + food_index) == FLAG_PLAIN_CELL) {
        *(cells + food_index) = FLAG_FOOD;
    } else {
        place_food(cells, width, height);
    }
    /* DO NOT MODIFY THIS FUNCTION */
}

/** Prompts the user for their name and saves it in the given buffer.
 * Arguments:
 *  - `write_into`: a pointer to the buffer to be written into.
 */
void read_name(char* write_into) {
    // TODO: implement! (remove the call to strcpy once you begin your
    // implementation)
    strcpy(write_into, "placeholder");
}

/** Cleans up on game over — should free any allocated memory so that the
 * LeakSanitizer doesn't complain.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - snake_p: a pointer to your snake struct. (not needed until part 2)
 */
void teardown(int* cells, snake_t* snake_p) {
    // TODO: implement!
    if(cells!=NULL){
        free(cells);
    }
}
