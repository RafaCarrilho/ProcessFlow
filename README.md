# ProcessFlow

Orquestrador de processos em C — cadastra tarefas e as executa via fork/exec/wait/dup2/pipe,
sem delegar para outro shell. Suporta execução sequencial, paralela, em pipe, redirecionamento
de entrada/saída/append, diretório de trabalho configurável e execução em background com jobs.

## Arquivos

- `main.c` — loop principal (interativo e modo workflow), parsing de comando e despacho
- `parser.c` / `parser.h` — tokenização de linha em `argv[]`
- `task.c` / `task.h` — cadastro/busca de tasks, configuração de input/output/append
- `job.c` / `job.h` — controle de jobs em background (start/jobs/wait)
- `exec.c` / `exec.h` — execução de fato (fork/exec/pipe/dup2/wait)
- `common.h` — constantes do projeto (MAXARG, MAXFILE, MAXTASKS, MAXJOBS)
- `Makefile` — compilação e limpeza
- `teste.pf`, `teste_exit.pf` — arquivos de exemplo para o modo workflow

## Como compilar

    make

## Como executar

Modo interativo:

    ./main

Modo workflow (lê comandos de um arquivo, um por linha):

    ./main <arquivo.pf>

## Como limpar os arquivos compilados

    make clean

## Sistema operacional usado

Ubuntu 26.04 LTS (WSL2)

## Comandos suportados

    task <nome> <programa> [args...]
    run <nome>
    run sequential <nome1> <nome2> ...
    run parallel <nome1> <nome2> ...
    run pipe <nome1> <nome2> ...
    input <nome> <arquivo>
    output <nome> <arquivo>
    append <nome> <arquivo>
    start <nome>
    jobs
    wait <jobID>
    workdir <diretorio>
    exit