#include "parser.h"
#include <string.h>

void parse(char *linha, char *argv[]){
    
    char *token = strtok (linha, " ");
    
    int i=0;
    while (token != NULL && i < MAXARG - 1){
        argv[i] = token;
        token = strtok (NULL, " ");
        i++;
    }
    argv[i] = NULL;
}
