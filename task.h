#ifndef TASK_H
#define TASK_H
#include "common.h"

typedef struct {
    char nome[64];
    char *argv[MAXARG];
    char input[MAXFILE];
    char output[MAXFILE];
    int append; //Isso aqui diz se a task é pra appendar ou não.

}task;

void cadastrar_task (char *nome, char *argv[]);
task* encontrar_task (char *nome);

#endif