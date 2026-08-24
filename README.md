# ProcessFlow

Orquestrador de processos em C. Recebe tarefas (programas do sistema), cadastra-as por nome e as executa como processos filhos via `fork()`/`exec()`/`wait()`/`dup2()`/`pipe()`, sem delegar a outro shell (`system()`/`popen()` não usados). Suporta execução sequencial, paralela e em pipe entre tarefas, redirecionamento de entrada/saída/append, diretório de trabalho configurável, e execução em background com controle de jobs.

## Arquivos

- `main.c` — loop interativo/workflow e despacho dos comandos.
- `parser.c` / `parser.h` — tokenização de cada linha em argumentos.
- `task.c` / `task.h` — cadastro e busca de tarefas, redirecionamento de input/output/append.
- `exec.c` / `exec.h` — execução (simples, sequencial, paralela, pipe, background).
- `job.c` / `job.h` — controle de jobs em background (`start`/`jobs`/`wait`).
- `common.h` — constantes compartilhadas (`MAXARG`, `MAXFILE`, `MAXTASKS`, `MAXJOBS`).
- `Makefile` — compilação e limpeza.

## Como compilar

Rode `make`. Gera o executável `processflow`.

## Como executar

Modo interativo (mostra o prompt `processflow> `): `./processflow`

Modo workflow (lê comandos de um arquivo `.pf`, ecoando cada linha antes de processar, sem prompt): `./processflow arquivo.pf`

Modo "entrada redirecionada" (sem prompt, sem eco — só a saída dos comandos, útil pra comparar contra um arquivo de saída esperado): `./processflow < arquivo.txt`

Em qualquer modo, o comando `exit` encerra o programa.

## Como limpar

Rode `make clean`.

## Sistema operacional usado

Ubuntu 26.04 LTS (WSL2).

## Comandos suportados

- `task <nome> <programa> [argumentos...]` — cadastra uma tarefa.
- `run <nome>` — executa uma tarefa isolada.
- `run sequential <t1> <t2> ...` — executa em sequência.
- `run parallel <t1> <t2> ...` — executa em paralelo.
- `run pipe <t1> <t2> ...` — executa encadeadas por pipe.
- `input <tarefa> <arquivo>` — redireciona entrada da tarefa.
- `output <tarefa> <arquivo>` — redireciona saída da tarefa (trunca).
- `append <tarefa> <arquivo>` — redireciona saída da tarefa (não trunca).
- `workdir <diretório>` — muda o diretório de trabalho do ProcessFlow (herdado pelos filhos).
- `start <tarefa>` — executa em background, imprime `[jobId] PID`.
- `jobs` — lista jobs em background.
- `wait <jobId>` — aguarda o término de um job específico.
- `exit` — encerra o ProcessFlow.