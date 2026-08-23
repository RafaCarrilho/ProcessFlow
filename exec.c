#include "task.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

static void redirecionar_input (task *tarefa){
    if (tarefa->input[0] != '\0'){
        int input = open(tarefa->input, O_RDONLY);
        if (input == -1){
            perror ("Erro ao abrir arquivo");
            exit(1);
        }
        dup2 (input, STDIN_FILENO);
        close (input);
    }
}

static void redirecionar_output_append (task *tarefa){
    if (tarefa->output[0] != '\0'){
        if (tarefa->append == 1){
            int output = open(tarefa->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (output == -1){
                perror ("Erro ao abrir arquivo");
                exit(1);
            }
            dup2 (output, STDOUT_FILENO);
            close(output);
        } else {
            int output = open(tarefa->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (output == -1){
                perror ("Erro ao abrir arquivo");
                exit(1);
            }
            dup2 (output, STDOUT_FILENO);
            close(output);
        }
    }
}

void executar (task* task_alvo){
    pid_t pid = fork();

    if (pid < 0){
        perror("Erro no fork");
    }else if (pid ==0 ){
        redirecionar_input(task_alvo);
        redirecionar_output_append(task_alvo);
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
                redirecionar_input(tarefa);
                redirecionar_output_append(tarefa);

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

    while (argv[i] != NULL) { //aqui eu to procurando quantas tasks viaveis existem
        task *tarefa = encontrar_task(argv[i]);
        if (tarefa != NULL) {
            tarefas_encontradas[n] = tarefa;
            n++;
        }
        i++;
    }
    
    for (int i=0; i<n-1; i++){ //agora é hora de criar pipe, então vou criar viaveis -1 pipes
        pipe(pipes[i]);
    }

    int p = 0;

    for (int k = 0; k < n; k++) {
        task *tarefa = tarefas_encontradas[k];
        pid_t pid = fork();

        if (pid < 0) {
            perror("Erro no fork");
        } else if (pid == 0) {
            if (k == 0) { // caso seja a primeira task eu nao mexo no OUTPUT pois é pra ir pro terminal
                redirecionar_input(tarefa);
                dup2(pipes[k][1], STDOUT_FILENO);
            } else if (k == n-1) { // caso seja a ULTIMA task eu nao mexo no put pois ja vem do terminal
                redirecionar_output_append(tarefa);
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
            printf("Terminamos bem galera\n"); //vou remover essas remarks de teste no futuro
        } else {
            printf("Não foi dessa vez...\n"); //vou remover essas remarks de teste no futuro
        }
    }
}