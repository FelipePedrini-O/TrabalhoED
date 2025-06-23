#ifndef LISTA_LEITORES_H
#define LISTA_LEITORES_H

#include "leitor.h"

typedef struct listaLeitores tListaLeitores;

tListaLeitores *criaListaLeitores();

void insereListaLeitores(tListaLeitores *l, tLeitor *leitor);

tLeitor *retiraListaLeitores(tListaLeitores *l, int id);

tLeitor *retornaLeitorListaLeitores(tListaLeitores *l, int id);

int recomendaLivroListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino);

int aceitaRecomendacaoListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino);

int recusaRecomendacaoListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino);

void imprimeListaLeitores(tListaLeitores *l);

void liberaListaLeitores(tListaLeitores *l);

#endif