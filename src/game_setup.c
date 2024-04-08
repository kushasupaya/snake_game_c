#include "game_setup.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
            int my_ptr = 0;
            char* my_str = strdup(board_rep);
            while (my_str[my_ptr] != '\0')
            {
                if (my_str[my_ptr] == 'Z')
                {
                    free(my_str);
                    return INIT_ERR_BAD_CHAR;
                }
                my_ptr++;
            }
            free(my_str);
            enum board_init_status status = decompress_board_str(cells_p,width_p, height_p, snake_p, board_rep);
            return status;
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


// Decompress function

enum board_init_status decompress_board_str(int** cells_p, size_t* width_p,
                                            size_t* height_p, snake_t* snake_p,
                                            char* compressed) 
{
    printf("Compressed: %s\n", compressed);
    char* temp = strdup(compressed);
   
    char* cursor = compressed;
    while (*cursor != '\0') {
        if (*cursor == 'S') {
            cursor++;
            if (*cursor != '1') {
                free(temp);
                return INIT_ERR_WRONG_SNAKE_NUM;
            }
        }
        cursor++;
    }
    
    char* token = strtok(compressed, "|");
    printf("This is the beginning: %s ", token);
    
    size_t height, width;
    if (sscanf(token, "B%zux%zu", &height, &width) != 2) {
        free(temp);
        free(*cells_p);
        return INIT_ERR_INCORRECT_DIMENSIONS; 
    }
    int sum = 0;
    
    
    token = strtok(NULL, "|WES");

    while (token != NULL) {
        sum += atoi(token); 
        token = strtok(NULL, "|WES"); 
    }

    // printf("Sum: %d\n", sum);
    // printf("Height: %zu\n", height);
    // printf("Width: %zu\n", width);
    // printf("Product of height and width: %zu\n", height * width);
    if ((size_t)sum != height * width)
    {
        printf("\nIncorrect dimensions\n");
        free(temp);
        return INIT_ERR_INCORRECT_DIMENSIONS;
    }

    *height_p = height;
    *width_p = width;
    *cells_p = (int*)malloc(height * width * sizeof(int));
    if (*cells_p == NULL) {
        free(temp);
        return INIT_ERR_BAD_CHAR; // Memory allocation failed
    }
    *cells_p = parse_compressed_board(temp, *cells_p, width);
    int snake_check = checking_for_snakes(*cells_p, height * width);
    printf("Snake check: %d\n", snake_check);
    if (snake_check != 1) {
        free(temp);
        return INIT_ERR_WRONG_SNAKE_NUM;
    }
    if (*cells_p == NULL) {
        free(temp);
        return INIT_ERR_BAD_CHAR; // Parsing failed
    }
    place_food(*cells_p, *width_p, *height_p);
    free(temp);
    return INIT_SUCCESS;

}

// Helper function to parse a substring and update cells_p accordingly
void parse_substring(char* substring, int* cells_p, int* index) {
    char board_type;
    int number;
    sscanf(substring, "%c%d", &board_type, &number);

    switch (board_type) {
        case 'W':
            for (int k = 0; k < number; k++) {
                cells_p[(*index)++] = FLAG_WALL; 
            }
            break;
        case 'E':
            for (int k = 0; k < number; k++) {
                cells_p[(*index)++] = FLAG_PLAIN_CELL; 
            }
            break;
        case 'S':
            for (int k = 0; k < number; ++k) {
                cells_p[(*index)++] = FLAG_SNAKE;
            }
            break;
    }
}

int checking_for_snakes(int* cells_p, size_t array_size) {
    int num_snakes = 0;
    for (size_t i = 0; i < array_size; i++) {
        if (cells_p[i] == FLAG_SNAKE) {
            num_snakes++;
        }
    }

    return num_snakes;
}

int* parse_compressed_board(char* compressed, int* cells_p, size_t width) {
    char* token = strtok(compressed, "|"); 
    token = strtok(NULL, "|");
    int index = 0;
    while (token != NULL) {
        char* ptr_string = strdup(token);

        int* indexes = malloc(strlen(ptr_string) * sizeof(int)); 

        int array_size = 0;

       
        int i = 0;
        while (ptr_string[i] != '\0') {
            if (ptr_string[i] == 'E' || ptr_string[i] == 'S' || ptr_string[i] == 'W') {
                indexes[array_size++] = i;
            }
            i++;
        }

        if (array_size == 1) {
            char board_type = ptr_string[0];
            switch (board_type) {
                case 'W':
                case 'E':
                case 'S':
                    parse_substring(ptr_string, cells_p, &index);
                    break;
            }
        } else {
            for (int q = 0; q < array_size; q++) {
                int starting_index = indexes[q];

                
                int final_index = (q + 1 < array_size) ? indexes[q + 1] : (int)strlen(ptr_string);

                char* ptr_substring = malloc((final_index - starting_index + 1) * sizeof(char));

                for (int j = starting_index; j < final_index; j++) {
                    ptr_substring[j - starting_index] = ptr_string[j];
                }
                ptr_substring[final_index - starting_index] = '\0'; 

                parse_substring(ptr_substring, cells_p, &index);

                free(ptr_substring);
            }
        }

        free(ptr_string); 
        free(indexes); 
        token = strtok(NULL, "|"); 
    }
    return cells_p;
}
