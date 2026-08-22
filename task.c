#include "task.h"
#include "common.h"
#include <stdio.h>
#include <string.h>

static task tarefas[MAXTASKS];
static int num_tarefas = 0;

task* encontrar_task (char *nome){
    int i=0;
    int procurando = 1;
    while (procurando){
        if (i<num_tarefas && strcmp(tarefas[i].nome, nome)==0){
            procurando =0;
            return &tarefas[i];
        }

        i++;
        if (i>=num_tarefas && procurando){
            procurando =0;
        }
    }

    return NULL;
}   