#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "parser.h"
#include "exec.h"
#include "job.h"

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
        if (argv[0] == NULL) {
            continue;
        }
        
        if (strcmp(argv[0], "task")==0){
            if (argv[1] == NULL) {
                printf("Uso: task <nome> <programa> [args...]\n");
                continue;
            }
            cadastrar_task (argv[1], &argv[2]);
            printf("Task %s cadastrada com sucesso\n", argv[1]);
        }

        if (strcmp(argv[0], "start")==0){
            if (argv[1] == NULL) {
                printf("Uso: start <tarefa>\n");
                continue;
            }
            task *task_alvo =encontrar_task (argv[1]);
            
            if (task_alvo != NULL) {
                executar_background(task_alvo);
            }
        }

        if (strcmp(argv[0], "jobs")==0){
            listar_jobs();
        }    
        
        if (strcmp(argv[0], "wait")==0){
            if (argv[1] == NULL) {
                printf("Uso: wait <jobID>\n");
                continue;
            }
            int jobID = atoi(argv[1]);
            wait_job(jobID);
        }  
        
        
        if (strcmp(argv[0], "input")==0){
            if (argv[1] == NULL || argv[2] == NULL) {
                printf("Uso: input <tarefa> <arquivo>\n");
                continue;
            }
            criar_input (argv[1], argv[2]);
            printf("Input de %s alterado com sucesso\n", argv[1]);
        }

        if (strcmp(argv[0], "output")==0){
            if (argv[1] == NULL || argv[2] == NULL) {
                printf("Uso: output <tarefa> <arquivo>\n");
                continue;
            }
            criar_output (argv[1], argv[2]);
            printf("Output de %s alterado com sucesso\n", argv[1]);
        }

        if (strcmp(argv[0], "append")==0){
            if (argv[1] == NULL || argv[2] == NULL) {
                printf("Uso: append <tarefa> <arquivo>\n");
                continue;
            }
            criar_append (argv[1], argv[2]);
            printf("Append de %s alterado com sucesso\n", argv[1]);
        }

        if (strcmp(argv[0], "run")==0){
            if (argv[1] == NULL) {
                printf("Uso: run <sequential|parallel|pipe|nome> ...\n");
                continue;
            }
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