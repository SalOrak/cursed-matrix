#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#include "constants.h"
#include "matrix.h"
#include "utils.h"

struct cell *matrix;
struct program *prog;

int start_matrix(struct program *p){

    prog = p;

    srand(time(NULL));

    initscr();
    curs_set(0); // Inivisible cursor
    cbreak(); // Disable line buffering and erase/kill character-processing, making vchars typed by the ser immediately available to the program
    noecho(); // Dont display character pressed
    nodelay(stdscr, TRUE); // Disable delay
    keypad(stdscr, TRUE); // Capture special keystrokes nodelay(stdscr, TRUE); // Disable block during read
                          
    // Colors
    if (set_colors() == EXIT_FAILURE){
        LOG("set_colors failed!. Not possible to run this");
        return EXIT_FAILURE;
    }

    // Initialize cells on the matrix.
    matrix = malloc(0);
    LOG("start_matrix[0]: init *matrix");
    for (int i = 0; i < prog->max_cells; i++){
        matrix = realloc(matrix, sizeof(struct cell) * (i + 1)); 
        matrix[i].ttl = prog->trailing_memory;
        matrix[i].c = ' ';
        matrix[i].alive = false; 
        matrix[i].pos_x = 0;
        matrix[i].pos_y = 0;
    }
    LOG("start_matrix[1]: ended filling *matrix");

    return EXIT_SUCCESS;
}

int set_colors(){

    if (!has_colors()){
        LOG("Terminal does not have colors!");
        return EXIT_FAILURE;
    }

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    if (can_change_color()){
        // Create 6 different green colors
        for (int i = 1; i < 6; i++){
            init_color(i, 0, (i * 100) % 1000, 0); // Change the definition of a color.
        }
    }else {
        LOG("Can't change colors!!");
    }

    return EXIT_SUCCESS;
}

void update_matrix(){

    //LOG("update_matrix[1]: init ");
    // Update the cells on the screen
    int cells_alive = 0;
    int h,w;
    getmaxyx(stdscr, h,w);
    color_set(1, NULL);
    for (int i = 0; i < prog->max_cells; i ++){
        if (matrix[i].alive == true){
            cells_alive++;
            if (can_change_color()){
                int intensity= prog->trailing_memory - matrix[i].ttl; 
                color_set(intensity, NULL);
            }
            if (matrix[i].ttl == prog->trailing_memory - 1){
                attron(A_DIM);
                mvaddch(matrix[i].pos_y - 1, matrix[i].pos_x, random_char());
                attroff(A_DIM);
            }

            if (matrix[i].ttl == prog->trailing_memory - 2){
                attron(A_STANDOUT);
                mvaddch(matrix[i].pos_y - 1, matrix[i].pos_x, random_char());
                attroff(A_STANDOUT);
            }
            attron(A_BOLD);
            mvaddch(matrix[i].pos_y, matrix[i].pos_x, random_char());
            attroff(A_BOLD);

            matrix[i].pos_y++;
            matrix[i].ttl--;
            if (matrix[i].ttl <= 0){
                attron(A_INVIS);
                mvaddch(matrix[i].pos_y - prog->trailing_memory, matrix[i].pos_x, 'X');
                attroff(A_INVIS);
            }
            if (matrix[i].pos_y - prog->trailing_memory > h){
                for (int j = prog->trailing_memory; j >= 0; j--){
                    attron(A_INVIS);
                    mvaddch(matrix[i].pos_y - j, matrix[i].pos_x, 'X');
                    attroff(A_INVIS);
                }
                matrix[i].alive = false;
                matrix[i].pos_x = 0;
                matrix[i].pos_y = 0;
            }
        }
    }

    // Create new cell
    double rolled = dice_rolls();
    do{
        for (int i = 0; i < prog->max_cells; i++){
            if ( !matrix[i].alive ){ 
                int *p = random_pos();
                matrix[i].alive = true;
                matrix[i].ttl= prog->trailing_memory;
                matrix[i].pos_y = p[1];
                matrix[i].pos_x = p[0];
                free(p);
                break;
            }
        }
        rolled = dice_rolls();
    }while(rolled < PROB_NEW_CELL);

    refresh();
}


int* random_pos(){
    int max_cols, max_rows;
    getmaxyx(stdscr, max_rows, max_cols);
    int *p = malloc(sizeof(int) * 2);
    p[0] = rand() % max_cols;
    p[1] = rand() % max_rows;
    return p;
}

double dice_rolls(){
    return (double)rand() / (double)RAND_MAX;
}


char random_char(){
    int r = (rand() % 23) + 97;
    return (char) r;
}
