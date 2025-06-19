#ifndef LEITOR_H
#define LEITOR_H

#include "lista.h"
#include "livro.h"

typedef struct leitor tLeitor;

tLeitor* criaLeitor(int id, char* nome);

void adicionaLivroLido(tLeitor* leitor, tLivro* livro);

void liberaLeitor(void* leitor);

#endif