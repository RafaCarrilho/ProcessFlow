#include <stdio.h>
#include <string.h>
#include "task.h"
#include "parser.h"


int main() {
    char linha[256] = "lesgooo";
    int loop;
    char *argv[MAXARG];

    while ((loop=strcmp(linha, "exit\n"))!=0) {
        
        printf("processflow> ");
        
        fgets(linha, sizeof(linha), stdin);

        if (strcmp(linha, "exit\n") == 0) {
            break;   
        }
        parse(linha, argv);
        if (strcmp(argv[0], "task")==0){
            cadastrar_task (argv[1], &argv[2]);
            printf("Task %s cadastrada com sucesso\n", argv[1]);
        }
        

        
    }

    return 0;
}