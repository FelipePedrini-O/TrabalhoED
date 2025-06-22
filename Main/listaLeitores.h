#ifndef LISTA_LEITORES_H
#define LISTA_LEITORES_H

#include "leitor.h"

typedef struct listaLeitores tListaLeitores;

tListaLeitores *criaListaLeitores();

void insereListaLeitores(tListaLeitores *l, tLeitor *leitor);

void retiraListaLeitores(tListaLeitores *l, int id); // Alterado para void para liberar o leitor dentro da funcao

tLeitor *retornaLeitorListaLeitores(tListaLeitores *l, int id);

int recomendaLivroListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino);

int aceitaRecomendacaoListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino);

int recusaRecomendacaoListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino);

// Funcoes Novas (2)
int descobreLivrosComumListaLeitores(tListaLeitores *l, int id_origem, int id_destino);

void imprimeNomesListaLeitores(tListaLeitores* l);

// void liberaLeitoresDaListaLeitores(tListaLeitores *l); Funcao a ser obervada por alteracao na libera principal

void criaAfinidadesEntreLeitores(tListaLeitores* l);
//Fim das Funcoes (2)

void imprimeListaLeitores(tListaLeitores *l);

void liberaListaLeitores(tListaLeitores *l);

#endif