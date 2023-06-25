#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#include "utils.h"

void __write_log(char * filename, char * text){
    FILE *fp;
    fp = fopen(filename, "a");
    if (fp){
        time_t t;
        time(&t);
        char *time_str= ctime(&t);
        time_str[strlen(time_str) - 1] = 0;
        fprintf(fp,"%s %s\n", time_str, text);
        fclose(fp);
    }
    else {
        printf("Something bad happened\n");
    }
}

