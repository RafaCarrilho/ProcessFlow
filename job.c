#include "job.h"
#include <stdio.h>
#include <sys/wait.h>


static job jobs[MAXJOBS];
static int num_jobs = 0;

int iniciar_job (pid_t pid){
    if (num_jobs >= MAXJOBS) {
        printf("Limite de jobs atingido\n");
        return -1;
    }

    job trabalho = {0};
    trabalho.jobID = num_jobs + 1;   // 1, 2, 3... bate com o exemplo do enunciado ([1] 1234)
    trabalho.pid = pid;

    jobs[num_jobs] = trabalho;
    num_jobs++;

    return trabalho.jobID;
}

void listar_jobs (){
    for (int i = 0; i < num_jobs; i++){
        if (jobs[i].status == 0){
            int wstatus;
            int resultado = waitpid(jobs[i].pid, &wstatus, WNOHANG);
            if (resultado == jobs[i].pid) {
                jobs[i].status = 1;
            }
        }
        printf("[%d] %d %s\n", jobs[i].jobID, jobs[i].pid, jobs[i].status == 0 ? "Rodando" : "Terminado");
    }
}


void wait_job (int jobID){
    
    if (jobID <= 0 || jobID > num_jobs) {
        printf("Job informado não existe\n");
        return;
    }

    int indice = jobID - 1;

    if (jobs[indice].status == 1){
        printf("Esse job já tinha terminado\n");
        return;
    } else{
        int wstatus;
        int resultado = waitpid(jobs[indice].pid, &wstatus, 0);
        if (resultado == jobs[indice].pid) {
            jobs[indice].status = 1;
        }
    }
}
