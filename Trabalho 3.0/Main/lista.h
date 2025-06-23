#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista tLista;

typedef void (*libera)(void*);
typedef void (*imprime)(void*);//Adicionado
typedef int (*compara_fptr)(const char*, const char*);//Adicionado

tLista* criaLista();

void insereListaInicio(tLista* l, void* item, libera libera_item);

void insereListaFinal(tLista* l, void* item, libera libera_item, imprime imprime_item);//Modificado

void retiraLista(tLista* l, int key);

int existeElementoNaOutraLista(tLista* l1, tLista* l2, compara_fptr compara);

void imprimeLista(tLista* l);

void liberaLista(tLista* l);

#endif