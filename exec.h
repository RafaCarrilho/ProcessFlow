#ifndef EXEC_H
#define EXEC_H
#include "task.h"

void executar (task* task_alvo);
void executar_paralelo (char *argv[]);
void executar_sequencial (char *argv[]);
void executar_pipe (char *argv[]);


#endif