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

void executar_pipe (char *argv[]){
    int n = 0, i=0, status;
    task *tarefas_encontradas[MAXARG];
    int pipes[MAXARG][2];
    pid_t listapid [MAXARG];

    while (argv[i] != NULL) {
        task *tarefa = encontrar_task(argv[i]);
        if (tarefa != NULL) {
            tarefas_encontradas[n] = tarefa;
            n++;
        }
        i++;
    }
    
    for (int i=0; i<n-1; i++){
        pipe(pipes[i]);
    }

    int p = 0;
    for (int k = 0; k < n; k++) {
        task *tarefa = tarefas_encontradas[k];
        pid_t pid = fork();

        if (pid < 0) {
            perror("Erro no fork");
        } else if (pid == 0) {
            if (k == 0) {
                dup2(pipes[k][1], STDOUT_FILENO);
            } else if (k == n-1) {
                dup2(pipes[k-1][0], STDIN_FILENO);
            } else {
                dup2(pipes[k-1][0], STDIN_FILENO);
                dup2(pipes[k][1], STDOUT_FILENO);
            }

            for (int i=0; i<n-1; i++){
                close(pipes[i][0]);
                close(pipes[i][1]);
            }
           
            execvp(tarefa->argv[0], tarefa->argv);
            perror("Erro no exec (duvido que aconteça)");
            exit(1);
        
        } else{ //aqui é o pai
            listapid[p] = pid;
            p++;
        }
    }
    //aqui TAMBÉM continua sendo o pai
    for (int i=0; i<n-1; i++){
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (int j = 0; j < p; j++) {
        waitpid(listapid[j], &status, 0);
        if (WIFEXITED(status)) {
            printf("Terminamos bem galera\n");
        } else {
            printf("Não foi dessa vez...\n");
        }
    }
}