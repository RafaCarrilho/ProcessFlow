#include "task.h"
#include "common.h"
#include <stdio.h>
#include <string.h>


static task tarefas[MAXTASKS];
static int num_tarefas = 0;

void cadastrar_task (char *nome, char *argv[]){
    
    if (num_tarefas >= MAXTASKS) {
        printf("Limite de tasks atingido\n");
        return;
    }

    task tarefa = {0};
    
    strcpy (tarefa.nome, nome);
    
    int i = 0;
    while (argv[i] != NULL) {
        tarefa.argv[i] = strdup(argv[i]);
        i++;
    }
    tarefa.argv[i] = NULL;

    tarefas[num_tarefas]= tarefa;
    num_tarefas++;
}


task* encontrar_task (char *nome){
    int i=0;
    int procurando = 1;
    while (procurando){
        if (i<num_tarefas && strcmp(tarefas[i].nome, nome)==0){
            procurando =0;
            printf("Tarefa encontrada\n");
            return &tarefas[i];
        }

        i++;
        if (i>=num_tarefas && procurando){
            printf("Tarefa não encontrada\n");
            procurando =0;
        }
    }

    return NULL;
}

void criar_input (char* nome, char* nome_arquivo){
    task *tarefa = encontrar_task(nome);
    
    if (tarefa == NULL) {
        printf("Erro ao encontrar tarefa\n");
        return;
    }
    strcpy(tarefa->input, nome_arquivo);

}

void criar_output (char* nome, char* nome_arquivo){
    task *tarefa = encontrar_task(nome);
    
    if (tarefa == NULL) {
        printf("Erro ao encontrar tarefa\n");
        return;
    }
    tarefa->append=0;
    strcpy(tarefa->output, nome_arquivo);

}

void criar_append (char* nome, char* nome_arquivo){
    task *tarefa = encontrar_task(nome);
    
    if (tarefa == NULL) {
        printf("Erro ao encontrar tarefa\n");
        return;
    }
    tarefa->append=1;
    strcpy(tarefa->output, nome_arquivo);


}