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

//Funcoes novas (2)
int listaVazia(tListaLivro* l);

tListaLivro* retornaLivrosEmComumListaLivro(tListaLivro* orig, tListaLivro* dest);
//Fim das funcoes (2)

void imprimeListaLivro(tListaLivro* l);

void liberaListaLivro(tListaLivro* l);

void liberaBiblioteca(tListaLivro* l);

#endif