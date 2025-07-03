/*
 TAD Lista.c
 BookEd

 Created by Artur Vitor Cintra Bernardes && Felipe Pedrini Oliveira in 2025/1 at UFES.
*/

#include "lista.h"
#include "utils.h"

typedef struct celula{
    void* item;
    struct celula* prox;
    struct celula* ant;

    libera libera_item;
    imprime imprime_item;
}tCelula;

struct lista{
    tCelula* prim;
    tCelula* ult;
};

tLista* criaLista(){
    tLista* l = malloc(sizeof(*l));
    checkMemory(l);

    l->prim = NULL;
    l->ult = NULL;

    return l;
}

void insereListaInicio(tLista* l, void* item, libera libera_item){
    tCelula* nova = malloc(sizeof(*nova));
    nova->prox = l->prim; 
    nova->ant = NULL;
    nova->item = item;
    nova->libera_item = libera_item;

    if(l->prim == NULL){ 
        l->ult = nova;
    }else{
        l->prim->ant = nova;
    }

    l->prim = nova;
}

void insereListaFinal(tLista* l, void* item, libera libera_item, imprime imprime_item){
    tCelula* nova = malloc(sizeof(*nova));
    nova->prox = NULL;
    nova->ant = l->ult; 
    nova->item = item;
    nova->libera_item = libera_item;
    nova->imprime_item = imprime_item;

    if(l->prim == NULL){
        l->prim = nova;
    }else{
        l->ult->prox = nova;
    }

    l->ult = nova;
}

static tCelula* buscaLista(tLista* l, int key){
    return l->prim;
}

void retiraLista(tLista* l, int key){
    tCelula* p = buscaLista(l, key);

    if(p == NULL){ 
        return;
    }

    if(p == l->prim){ 
        l->prim = p->prox;
    }else{
        p->ant->prox = p->prox;
    }

    if(p == l->ult){ 
        l->ult = p->ant;
    }else{
        p->prox->ant = p->ant;
    }

    free(p);

    return;
}

/*
    Essa função é útil para verificar se um elemento está em outra lista,
    digamos por exemplo se algum gosto de um leitor pertence aos gostos de outro leitor.

    Onde a compara_ftr seria uma strcmp().
*/
int existeElementoNaOutraLista(tLista* l1, tLista* l2, compara_fptr compara){
    tCelula* aux = l1->prim;

    while(aux != NULL){
        tCelula* p = l2->prim;
        while(p != NULL){
            if(compara(aux->item, p->item) == 0){
                return 1;
            }
            p = p->prox;
        }
        aux = aux->prox;
    }

    return 0;
}

void imprimeLista(tLista* l){
    tCelula* p = l->prim;

    while(p != NULL){
        p->imprime_item(p->item);
        printf(" ");

        p = p->prox;
    }
}

void liberaLista(tLista* l){
    tCelula* p = l->prim;

    if(l != NULL){
        while(p != NULL){
            tCelula* aux = p->prox;
            p->libera_item(p->item);
            free(p);
            p = aux;
        }

        free(l);
        l = NULL;
    }
}