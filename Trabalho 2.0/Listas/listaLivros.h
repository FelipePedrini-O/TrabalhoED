#ifndef LISTA_LIVROS_H
#define LISTA_LIVROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "livro.h"

typedef struct listaLivro tListaLivro;

tListaLivro* criaListaLivro();

void insereLivro(tListaLivro* l, tLivro* livro);

void retiraLivro(tListaLivro* l, char* nome);

tLivro* retornaLivroLista(tListaLivro* l, char* key);

void imprimeListaLivro(tListaLivro* l);

void liberaListaLivro(tListaLivro* l);

void liberaBiblioteca(tListaLivro* l);

#endif