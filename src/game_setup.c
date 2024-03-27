#include "game_setup.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Some handy dandy macros for decompression
#define E_CAP_HEX 0x45
#define E_LOW_HEX 0x65
#define S_CAP_HEX 0x53
#define S_LOW_HEX 0x73
#define W_CAP_HEX 0x57
#define W_LOW_HEX 0x77
#define DIGIT_START 0x30
#define DIGIT_END 0x39

/** Initializes the board with walls around the edge of the board.
 *
 * Modifies values pointed to by cells_p, width_p, and height_p and initializes
 * cells array to reflect this default board.
 *
 * Returns INIT_SUCCESS to indicate that it was successful.
 *
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 */
enum board_init_status initialize_default_board(int** cells_p, size_t* width_p,
                                                size_t* height_p) {
    *width_p = 20;
    *height_p = 10;
    int* cells = malloc(20 * 10 * sizeof(int));
    *cells_p = cells;
    for (int i = 0; i < 20 * 10; i++) {
        cells[i] = FLAG_PLAIN_CELL;
    }

    // Set edge cells!
    // Top and bottom edges:
    for (int i = 0; i < 20; ++i) {
        cells[i] = FLAG_WALL;
        cells[i + (20 * (10 - 1))] = FLAG_WALL;
    }
    // Left and right edges:
    for (int i = 0; i < 10; ++i) {
        cells[i * 20] = FLAG_WALL;
        cells[i * 20 + 20 - 1] = FLAG_WALL;
    }

    // Add snake
    cells[20 * 2 + 2] = FLAG_SNAKE;

    return INIT_SUCCESS;
}

/** Initialize variables relevant to the game board.
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 *  - snake_p: a pointer to your snake struct (not used until part 2!)
 *  - board_rep: a string representing the initial board. May be NULL for
 * default board.
 */
enum board_init_status initialize_game(int** cells_p, size_t* width_p,
                                       size_t* height_p, snake_t* snake_p,
                                       char* board_rep) {
    // TODO: implement!
    
    
        if(board_rep==NULL){
            enum board_init_status status = initialize_default_board(cells_p, width_p, height_p);
            snake_p -> position_x = 2;
            snake_p -> position_y = 2;
            snake_p -> direction = INPUT_RIGHT;
            place_food(*cells_p, *width_p, *height_p);
            return status;
        }else{
            decompress_board_str(cells_p,width_p, height_p, snake_p, board_rep);
        }
    
    

    return INIT_SUCCESS;
}

/** Takes in a string `compressed` and initializes values pointed to by
 * cells_p, width_p, and height_p accordingly. Arguments:
 *      - cells_p: a pointer to the pointer representing the cells array
 *                 that we would like to initialize.
 *      - width_p: a pointer to the width variable we'd like to initialize.
 *      - height_p: a pointer to the height variable we'd like to initialize.
 *      - snake_p: a pointer to your snake struct (not used until part 2!)
 *      - compressed: a string that contains the representation of the board.
 * Note: We assume that the string will be of the following form:
 * B24x80|E5W2E73|E5W2S1E72... To read it, we scan the string row-by-row
 * (delineated by the `|` character), and read out a letter (E, S or W) a number
 * of times dictated by the number that follows the letter.
 */

// Helper function to convert a string to an integer
int str_to_int(const char *str) {
    return atoi(str);
}

// Helper function to get the index of a cell in the board's cell array
size_t get_cell_index(int row, int col, size_t width) {
    return row * width + col;
}

enum board_init_status decompress_board_str(int** cells_p, size_t* width_p,
                                            size_t* height_p, snake_t* snake_p,
                                            char* compressed) {
    // TODO: implement!
    if (cells_p == NULL || width_p == NULL || height_p == NULL || compressed == NULL)
        return INIT_ERR_BAD_CHAR;

    const char *delimiter = "|";
    char *token;
    char *saveptr;

    // Extract dimensions from the compressed string
    token = strtok_r((char *)compressed, "Bx|", &saveptr);
    if (token == NULL)
        return INIT_ERR_BAD_CHAR;

    *height_p = str_to_int(token);
    token = strtok_r(NULL, "x|", &saveptr);
    if (token == NULL)
        return INIT_ERR_BAD_CHAR;
    *width_p = str_to_int(token);

    // Allocate memory for cells
    *cells_p = (int *)malloc((*width_p) * (*height_p) * sizeof(int));
    if (*cells_p == NULL)
        return INIT_ERR_BAD_CHAR;

    // Initialize all cells to 0
    memset(*cells_p, 0, (*width_p) * (*height_p) * sizeof(int));

    // Move to the next token to read the board contents
    token = strtok_r(NULL, delimiter, &saveptr);
    if (token == NULL)
        return INIT_ERR_BAD_CHAR;

    // Initialize row and column indices
    size_t row = 0, col = 0;

    // Parse the board contents
    while (*token != '\0') {
        char direction = *token++;
        size_t count = 0;
        while (*token >= '0' && *token <= '9') {
            count = count * 10 + (*token - '0');
            token++;
        }

        // Fill the cells based on the direction and count
        switch (direction) {
            case 'E':
                for (size_t i = 0; i < count; i++) {
                    (*cells_p)[get_cell_index(row, col++, *width_p)] = 1;
                }
                break;
            case 'W':
                for (size_t i = 0; i < count; i++) {
                    (*cells_p)[get_cell_index(row, col++, *width_p)] = -1;
                }
                break;
            case 'S':
                for (size_t i = 0; i < count; i++) {
                    (*cells_p)[get_cell_index(row++, col, *width_p)] = 1;
                }
                break;
            default:
                return INIT_ERR_BAD_CHAR;
        }
    }

    // Check if decoded dimensions match the specified dimensions
    if (*height_p != row || *width_p != col) {
        free(*cells_p);
        *cells_p = NULL;
        return INIT_ERR_INCORRECT_DIMENSIONS;
    }

    return INIT_SUCCESS;
}
