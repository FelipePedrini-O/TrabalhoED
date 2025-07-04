/*
 TAD Lista_de_Livros.c
 BookEd

 Created by Artur Vitor Cintra Bernardes && Felipe Pedrini Oliveira in 2025/1 at UFES.
*/

#include "listaLivros.h"
#include "utils.h"

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
    checkMemory(l);

    l->prim = NULL;
    l->ult = NULL;

    return l;
}

tLivro* retornaLivroLista(tListaLivro* l, int key){
    if(l)
    {
        tNode* p = l->prim;
    
        while(p != NULL){
            if(retornaIdLivro(p->livro) == key){
                return p->livro;
            }
    
            p = p->prox;
        }
    }
    return NULL;
}

static tNode* buscaLivroLista(tListaLivro* l, int key){
    if(l)
    {
        tNode* p = l->prim;
    
        while(p != NULL){
            if(retornaIdLivro(p->livro) == key){
                return p;
            }
    
            p = p->prox;
        }
    }
    return NULL;
}

void insereLivro(tListaLivro* l, tLivro* livro){
    if(l)
    {
        if(buscaLivroLista(l, retornaIdLivro(livro)) != NULL){
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
}

void retiraLivro(tListaLivro* l, int key){
    if(l)
    {
        tNode* p = buscaLivroLista(l, key);
    
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
}

int listaVazia(tListaLivro* l){
    if(l)
    {
        if(l->prim == NULL){
            return 1;
        }
    }
    return 0;
}

tListaLivro* retornaLivrosEmComumListaLivro(tListaLivro* orig, tListaLivro* dest){
    tListaLivro* comuns = criaListaLivro();

    if(orig && dest)
    {
        tNode* p = orig->prim;
        while(p != NULL){
            if(retornaLivroLista(dest, retornaIdLivro(p->livro)) != NULL){
                insereLivro(comuns, p->livro);
            }
            p = p->prox;
        }
    }

    return comuns;
}

void imprimeListaLivro(tListaLivro* l, FILE* saidas_f){
    if(l)
    {
        tNode* p = l->prim;
    
        while(p != NULL){
            if(p->prox != NULL){
                if(p->livro)
                    fprintf(saidas_f, "%s, ", retornaNomeLivro(p->livro));
            }else{
                if(p->livro)
                    fprintf(saidas_f, "%s", retornaNomeLivro(p->livro));
            }
    
            p = p->prox;
        }
    }
}

void liberaListaLivro(tListaLivro* l){
    if(l)
    {
        tNode* p = l->prim;
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
    if(l)
    {
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
}