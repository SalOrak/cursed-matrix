#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <ncurses.h>

#include "matrix.h"
#include "constants.h"
#include "utils.h"

int main(int argc, char ** argv){

    if (start_matrix() != EXIT_SUCCESS){
        LOG("Failed to start matrix\n");
        endwin();
        return EXIT_FAILURE;
    }

    do{
        update_matrix();
        napms(25);
        if (getch() == 'x') {
            break;
        }
        
    }while(1);

    endwin();
    return 0;
}

