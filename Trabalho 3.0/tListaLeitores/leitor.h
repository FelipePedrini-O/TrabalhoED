#ifndef LEITOR_H
#define LEITOR_H

#include "lista.h"
#include "livro.h"
#include "listaLivros.h"


typedef struct leitor tLeitor;

// Funcoes novas

int retornaIdLeitor(tLeitor *l);
char *retornaNomeLeitor(tLeitor* l);
void imprimeLeitor(tLeitor* l);

// Fim das funcoes novas

tLeitor* criaLeitor(int id, char* nome);

void adicionaLivroLista(tLivro* livro, tListaLivro* lista);

void retiraLivroLista(tListaLivro* lista, char* nome);

tListaLivro* retornaListaLidos(tLeitor* l);

tListaLivro* retornaListarecomendados(tLeitor* l);

tListaLivro* retornaListaDesejados(tLeitor* l);

tLista* retornaAfinidades(tLeitor* l);

void liberaLeitor(void* leitor);

#endif