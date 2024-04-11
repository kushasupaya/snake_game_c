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

void update_snake_direction(int* cells, size_t width, int* current_x_coord, int* current_y_coord, snake_t* snake_p, enum input_key input) {
    switch (input) {
        case INPUT_UP:
            (*current_y_coord)--;
            if (cells[*current_y_coord * (int)width + *current_x_coord] == FLAG_WALL) {
                cells[++(*current_y_coord) * (int)width + *current_x_coord] = FLAG_SNAKE;
                g_game_over = 1;
                break;
            }
            snake_p->direction = INPUT_UP;
            break;
        case INPUT_DOWN:
            (*current_y_coord)++;
            snake_p->direction = INPUT_DOWN;
            if (cells[*current_y_coord * (int)width + *current_x_coord] == FLAG_WALL) {
                cells[--(*current_y_coord) * (int)width + *current_x_coord] = FLAG_SNAKE;
                g_game_over = 1;
                break;
            }
            break;
        case INPUT_RIGHT:
            (*current_x_coord)++;
            snake_p->direction = INPUT_RIGHT;
            if (cells[*current_y_coord * (int)width + *current_x_coord] == FLAG_WALL) {
                cells[*current_y_coord * (int)width + --(*current_x_coord)] = FLAG_SNAKE;
                g_game_over = 1;
                break;
            }
            break;
        case INPUT_LEFT:
            (*current_x_coord)--;
            if (cells[*current_y_coord * (int)width + *current_x_coord] == FLAG_WALL) {
                cells[*current_y_coord * (int)width + ++(*current_x_coord)] = FLAG_SNAKE;
                g_game_over = 1;
                break;
            }
            snake_p->direction = INPUT_LEFT;
            break;
        default:
            break;
    }
}


void update(int* cells, size_t width, size_t height, snake_t* snake_p, enum input_key input, int growing) {   

    if(g_game_over==0){

    direction_t* dt = snake_p -> body -> data;
    int position_y = dt->y;
    int position_x = dt->x;


    cells[position_y * (int)width + position_x] = FLAG_PLAIN_CELL;

    if (cells[position_y * (int)width + position_x] == FLAG_FOOD) {
        cells[position_y * (int)width + position_x] = FLAG_SNAKE;
        g_score++;
        place_food(cells, width, height);
  
    }

    // if no input
    if (input == INPUT_NONE)
        input = snake_p->direction;

    // Update snake's coordinates based on input
    update_snake_direction(cells, width, &position_x, &position_y, snake_p, input);

    if (g_game_over == 1)
    {
        teardown(cells,  snake_p);
        return;
    }

    cells[dt->y * (int)width + dt->x] = FLAG_PLAIN_CELL;

    if (cells[position_y * (int)width + position_x] == FLAG_FOOD) {
        g_score++;
        place_food(cells, width, height);
    }

    dt->x = position_x;
    dt->y = position_y;

    cells[position_y * (int)width + position_x] = FLAG_SNAKE;
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
    // printf("cells: %p\n", cells);
    // if(cells!=NULL){
    //     free(cells);
    // }
}
