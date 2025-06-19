#ifndef LISTA_LIVROS_H
#define LISTA_LIVROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "livro.h"

typedef struct listaLivro tListaLivro;

tLista* criaListaLivro();

void insereLivro(tLista* l, tLivro* livro);

void retiraLivro(tLista* l, char* nome);

void imprimeListaLivro(tLista* l);

void liberaListaLivro(tLista* l);

#endif