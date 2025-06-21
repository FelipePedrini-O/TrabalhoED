#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista tLista;

typedef void (*libera)(void*);

tLista* criaLista();

void insereListaInicio(tLista* l, void* item, libera libera_item);

void insereListaFinal(tLista* l, void* item, libera libera_item);

void retiraLista(tLista* l, int key);

void imprimeLista(tLista* l);

void liberaLista(tLista* l);

#endif