#ifndef LISTA_LEITORES_H
#define LISTA_LEITORES_H

#include "leitor.h"

typedef struct listaLeitores tListaLeitores;

tListaLeitores *criaListaLeitores();

void insereListaLeitores(tListaLeitores *l, tLeitor *leitor);

void retiraListaLeitores(tListaLeitores *l, int id); // Alterado para void para liberar o leitor dentro da funcao

tLeitor *retornaLeitorListaLeitores(tListaLeitores *l, int id);

int recomendaLivroListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino, FILE* saidas_f);

int aceitaRecomendacaoListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino, FILE* saidas_f);

int recusaRecomendacaoListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino, FILE* saidas_f);

// Funcoes Novas (2)
int descobreLivrosComumListaLeitores(tListaLeitores *l, int id_origem, int id_destino, FILE* saidas_f);

void imprimeNomesListaLeitores(tListaLeitores* l, FILE* saidas_f);

// void liberaLeitoresDaListaLeitores(tListaLeitores *l); Funcao a ser obervada por alteracao na libera principal

void criaAfinidadesEntreLeitores(tListaLeitores* l);
//Fim das Funcoes (2)

//F(3)
int existeElementoEmComum(tListaLeitores* l1, tListaLeitores* l2);
//Fim(3)

void imprimeListaLeitores(tListaLeitores *l, FILE* saidas_f);

void liberaListaLeitores(tListaLeitores *l);

#endif