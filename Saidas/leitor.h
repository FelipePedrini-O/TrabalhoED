#ifndef LEITOR_H
#define LEITOR_H

#include "lista.h"
#include "livro.h"
#include "listaLivros.h"


typedef struct leitor tLeitor;

// Funcoes novas

int retornaIdLeitor(tLeitor *l);
char *retornaNomeLeitor(tLeitor* l);
void imprimeLeitor(tLeitor* l, FILE* saidas_f);

// Fim das funcoes novas

tLeitor* criaLeitor(int id, char* nome, tLista* gostos);

void adicionaLivroLista(tLivro* livro, tListaLivro* lista);

void retiraLivroLista(tListaLivro* lista, int key); // Alterado key para int para ficar conforme os comandos

//Funcoes novas (2)

int existeGostoEmComum(tLeitor* l1, tLeitor* l2);

//Fim das funcoes novas (2)

//Nova funcao (3)
int existeAfinidadeLeitores(tLeitor* orig, tLeitor* dest);
//Fim da funcao (3)

tListaLivro* retornaListaLidos(tLeitor* l);

tListaLivro* retornaListarecomendados(tLeitor* l);

tListaLivro* retornaListaDesejados(tLeitor* l);

void* retornaAfinidades(tLeitor* l);//Modificado

void liberaLeitor(void* leitor);

#endif