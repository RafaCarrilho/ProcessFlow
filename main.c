#include <stdio.h>
#include <string.h>
#include "task.h"
#include "parser.h"
#include "exec.h"

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

        if (strcmp(argv[0], "run")==0){
            if (strcmp(argv[1], "sequential")==0){
                
                executar_sequencial(&argv[2]);

            } else if  (strcmp(argv[1], "parallel")==0){
                
                executar_paralelo(&argv[2]);
                
            }else if (strcmp(argv[1], "pipe")==0){
                
                executar_pipe(&argv[2]);

            } else {
                task *task_alvo =encontrar_task (argv[1]);
            
                if (task_alvo != NULL) {
                    executar(task_alvo);
                }
            }
        
        }
        
    }

    return 0;
}