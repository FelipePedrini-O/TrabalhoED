#ifndef UTILS_H
#define UTILS_H

#include "listaLivros.h"
#include "listaLeitores.h"

void leLivros(tListaLivro* lista);
void checkMemory(void *p);

//Novas funcoes (2)
void leLeitores(tListaLeitores* lista);
//Fim das funcoes (2)

// Novas funcoes (3)
FILE *incializaComandos();
int leComando(FILE *comandos, int *funcionalidade, int *id_1, int *id_2, int *id_3);
void liberaComandos(FILE *comandos);
// Fim das funcoes (3)

#endif