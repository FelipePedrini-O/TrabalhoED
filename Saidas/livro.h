#ifndef LIVRO_H
#define LIVRO_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
    Varios hotfixes foram feitos nas funcoes para evitar erros de segfault
*/

typedef struct livro tLivro;

tLivro* criaLivro(char* titulo, char* autor, char* genero, int ano_publicacao, int id);

char* retornaNomeLivro(void* livro);

int retornaIdLivro(void *livro);

void liberaLivro(void* livro);

#endif