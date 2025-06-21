#include "listaLivros.h"
#include "livro.h"

typedef struct node{
    tLivro* livro;
    struct node* prox;
    struct node* ant;
}tNode;

struct listaLivro{
    tNode* prim;
    tNode* ult;
};

tListaLivro* criaListaLivro(){
    tListaLivro* l = malloc(sizeof(*l));

    l->prim = NULL;
    l->ult = NULL;

    return l;
}

tLivro* retornaLivroLista(tListaLivro* l, char* key){
    tNode* p = l->prim;

    while(p != NULL){
        if(strcmp(retornaNomeLivro(p->livro), key) == 0){
            return p->livro;
        }

        p = p->prox;
    }

    return NULL;
}

static tNode* buscaLivroLista(tListaLivro* l, char* key){
    tNode* p = l->prim;

    while(p != NULL){
        if(strcmp(retornaNomeLivro(p->livro), key) == 0){
            return p;
        }

        p = p->prox;
    }

    return NULL;
}

void insereLivro(tListaLivro* l, tLivro* livro){
    if(buscaLivroLista(l, retornaNomeLivro(livro)) != NULL){
        printf("Livro já pertence a essa lista! Portanto, não foi adicionado!\n");
        return;
    }

    tNode* nova = malloc(sizeof(*nova));
    nova->prox = NULL;
    nova->ant = l->ult; 
    nova->livro = livro;

    if(l->prim == NULL){
        l->prim = nova;
    }else{
        l->ult->prox = nova;
    }

    l->ult = nova;
}

void retiraLivro(tListaLivro* l, char* nome){
    tNode* p = buscaLivroLista(l, nome);

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

    //tAluno* al = p->a;
    free(p);

    return;
}

void imprimeListaLivro(tListaLivro* l){
    tNode* p = l->prim;

    while(p != NULL){
        if(p->prox != NULL){
            printf("%s, ", retornaNomeLivro(p->livro));
        }else{
            printf("%s", retornaNomeLivro(p->livro));
        }

        p = p->prox;
    }
}

void liberaListaLivro(tListaLivro* l){
    tNode* p = l->prim;

    if(l != NULL){
        while(p != NULL){
            tNode* aux = p->prox;
            free(p);
            p = aux;
        }

        free(l);
        l = NULL;
    }
}

void liberaBiblioteca(tListaLivro* l){
    tNode* p = l->prim;

    if(l != NULL){
        while(p != NULL){
            tNode* aux = p->prox;
            liberaLivro(p->livro);
            free(p);
            p = aux;
        }

        free(l);
        l = NULL;
    }
}