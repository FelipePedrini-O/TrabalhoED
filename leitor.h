#ifndef LEITOR_H
#define LEITOR_H

#include "lista.h"

typedef struct leitor tLeitor;

tLeitor* criaLeitor(int id, char* nome);

void liberaLeitor(void* leitor);

#endif