#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#define MAXARG 64

void parse(char *linha, char *argv[]){
        
    char *token = strtok (linha, " ");
    
    int i=0;
    while (token != NULL && i < MAXARG - 1){
        argv[i] = token;
        token = strtok (NULL, " ");
        i++;
    }
    argv[i] = NULL;
}


int main (){
    int fd[2];
    pipe(fd);
    
    pid_t pid1 = fork();

    if (pid1 == 0){
        dup2(fd[1], STDOUT_FILENO);
        char *argv[MAXARG];
        char linha[]= {"ls"};
        parse(linha, argv);
        close (fd[0]);
        close (fd[1]);

        execvp (argv[0], argv);
        perror("Deu erro no exec\n");
        exit(1);
    }
    pid_t pid2 = fork();
    if (pid2==0){
        dup2 (fd[0], STDIN_FILENO);
        char linha[] = {"wc -l"};
        char *argv[MAXARG];
        parse (linha, argv);

        
        close (fd[0]);
        close (fd[1]);
        sleep(3);
        execvp (argv[0], argv);
        perror ("Deu erro no exec\n");
        exit(1);
    }
    close (fd[0]);
    close (fd[1]);

    int status1, status2;

    int result1 = waitpid(pid1, &status1, WNOHANG);
    int result2 = waitpid(pid2, &status2, WNOHANG);

    while (result1 == 0){
        printf("Estamos no aguardo ainda\n");
        sleep(1);
        result1 = waitpid(pid1, &status1, WNOHANG);
    }

    while (result2 == 0){
        printf("Estamos no aguardo ainda\n");
        sleep(1);
        result2 = waitpid(pid2, &status2, WNOHANG);
    }

    if (WIFEXITED(status1)){
        printf("Terminamos bem galera\n");
    } else {
        printf ("Não foi dessa vez...\n");
    }

    if (WIFEXITED(status2)){
        printf("Terminamos bem galera\n");
    } else {
        printf ("Não foi dessa vez...\n");
    }
} 