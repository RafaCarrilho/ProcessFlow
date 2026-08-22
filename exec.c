#include "task.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


void executar (task* task_alvo){
    pid_t pid = fork();

    if (pid < 0){
        perror("Erro no fork");
    }else if (pid ==0 ){
        execvp (task_alvo->argv[0], task_alvo->argv);
        perror ("Erro no exec (duvido que aconteça)");
        exit(1);
    } else{
        
        //agora papi]
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)){
            printf("Terminamos bem galera\n");
        } else {
            printf ("Não foi dessa vez...\n");
        }

    }

    
}

void executar_sequencial (char *argv[]){
    int i = 0;
    while (argv[i] != NULL){
        task *tarefa = encontrar_task (argv[i]);
        
        if (tarefa != NULL) {
            executar(tarefa);
        }
        i++;
    }
}


void executar_paralelo (char *argv[]){
    int i = 0, n=0, status;
    pid_t listapid [MAXARG];
    while (argv[i] != NULL){
        task *tarefa = encontrar_task (argv[i]);
        
        if (tarefa != NULL) {
            pid_t pid = fork();
            if (pid < 0){
                perror("Erro no fork");
            }else if (pid ==0 ){
                execvp (tarefa->argv[0], tarefa->argv);
                perror ("Erro no exec (duvido que aconteça)");
                exit(1);
            }else{
                listapid[n] = pid;
                n++;
            }

        }
        i++;
    }
    for (int j=0; j<n; j++){
        waitpid(listapid[j], &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Terminamos bem galera\n");
        } else {
            printf("Não foi dessa vez...\n");
        }
    }
    
}