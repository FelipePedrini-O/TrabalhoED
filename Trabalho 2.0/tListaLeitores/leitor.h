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

tLeitor* criaLeitor(int id, char* nome, tLista* gostos);

void adicionaLivroLista(tLivro* livro, tListaLivro* lista);

void retiraLivroLista(tListaLivro* lista, char* nome);

//Funcoes novas (2)

int existeGostoEmComum(tLeitor* l1, tLeitor* l2);

//Fim das funcoes novas (2)

tListaLivro* retornaListaLidos(tLeitor* l);

tListaLivro* retornaListarecomendados(tLeitor* l);

tListaLivro* retornaListaDesejados(tLeitor* l);

void* retornaAfinidades(tLeitor* l);//Modificado

void liberaLeitor(void* leitor);

#endif