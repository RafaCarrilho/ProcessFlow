#ifndef JOB_H
#define JOB_H
#include "common.h"
#include <sys/types.h>

typedef struct {
    int jobID;
    pid_t pid;
    int status;

}job;
int iniciar_job (pid_t pid);
void listar_jobs();
void wait_job (int jobID);
#endif