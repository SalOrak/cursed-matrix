#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <ncurses.h>

#include "matrix.h"
#include "constants.h"
#include "utils.h"

void usage();
struct program * process_args(int argc, char ** argv);

int main(int argc, char ** argv){

    // Process CLI arguments
    struct program *prog = process_args(argc, argv);
    if (prog->res) return prog->res;

    if (start_matrix(prog) != EXIT_SUCCESS){
        LOG("Failed to start matrix\n");
        endwin();
        return EXIT_FAILURE;
    }

    do{
        update_matrix();
        napms(100 - prog->speed);
        if (getch() == 'x') {
            break;
        }
        
    }while(1);

    endwin();
    free(prog);
    return 0;
}

/**
 * Print the usage for the CLI command in the terminal
 */
void usage(){
    printf("Usage: mcursed [-fs --falling-speed] [ -c --color ] [ -tm --trailing-memory] [-h --help]\n" \
           "\t -fs / --failing-speed NUMBER:\n" \
           "\t\tChanges the speed of the letters falling. Range 1 - 100\n" \
           "\t -tm / --trailing-memory NUMBER:\n" \
           "\t\tChanges the amount of characters alive in the trailing while alive. Range 0 - 50\n" \
           "\t -c / --cells NUMBER:\n" \
           "\t\tChanges the maximum amount of leading characters on screen. Range 1 - 100" \
           "\t -co / --color COLOR:\n" \
           "\t\tChanges the color of the leading character falling. One of WHITE | GREEN | BLUE | RED | PURPLE | YELLOW\n" \
           "\t -h / --help:" \
           "\t\tDisplays this usage help messsage\n"); 
}

/**
 * Process CLI arguments passed to the application
 */
struct program *process_args(int argc, char ** argv){

    struct program *prog = malloc(sizeof(struct program));
    prog->max_cells= 30;
    prog->speed = 75;
    prog->trailing_memory= 10;
    prog->res = 0;

    if (argc < 2){
        return prog;
    }

    int curr = 1;
    char *arg;
    do{
        printf("argv[%d] = %s\n", curr, argv[curr]);
        arg = argv[curr];

        if (strcmp(arg, "-h") == 0 || 
            strcmp(arg, "--help") == 0 ||
            (curr + 1) == argc){
            usage();
            prog->res = 1;
            return prog;
        }
        else if (strcmp(arg, "-fs") == 0 || 
                 strcmp(arg, "--falling-speed") == 0){
            int tmp = atoi(argv[++curr]);
            if (tmp> 100) tmp= 100;
            else if (tmp< 1) tmp= 1;
            prog->speed = tmp;
        }

        else if (strcmp(arg, "-tm") == 0 || 
                 strcmp(arg, "--trailing-memory") == 0){
            int tmp = atoi(argv[++curr]);
            if (tmp > 50) tmp = 50;
            else if (tmp < 1) tmp = 1;
            prog->trailing_memory = tmp;
        }

        else if (strcmp(arg, "-c") == 0 || 
                 strcmp(arg, "--cells") == 0){
            int tmp = atoi(argv[++curr]);
            if (tmp > 100) tmp = 100;
            else if (tmp < 1) tmp = 1;
            prog->trailing_memory = tmp;
        }

        else if (strcmp(arg, "-co") == 0 || 
                 strcmp(arg, "--color") == 0){
            printf("Color argument");
        }
        else{
            printf("ERROR:Argument not found");
            prog->res = 1;
            return prog;
        }
            
    } while(argc > ++curr);

    return prog;
}

