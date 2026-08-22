#include <stdio.h>
#include <string.h>

int main() {
    char linha[256] = "lesgooo";
    int loop;
    while ((loop=strcmp(linha, "exit\n"))!=0) {
        
        printf("processflow> ");
        
        fgets(linha, sizeof(linha), stdin);

        if (strcmp(linha, "exit\n") == 0) {
            break;   
        }

        
    }

    return 0;
}