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