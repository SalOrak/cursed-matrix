#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#define LOG_FLAG 1
#define LOG_FILE "cursed.log"

// Inmutable constants
#define PROB_NEW_CELL 0.35

struct cell{
    int ttl; // Distance until death.
    char c; // Character shown in screen
    int alive; //  Either should be displayed or not
    int pos_x; // Randomly fixed during alive
    int pos_y; // Random but ttl changes it indirectly 
};

struct program{
    int max_cells; // Maximum cells on screen 
    int speed; // Speed of the falling chars
    int trailing_memory; // Trailing memory
    int res; // Result
};


#endif 
