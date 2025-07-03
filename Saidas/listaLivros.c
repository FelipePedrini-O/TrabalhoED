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

// Alterado key para int para ficar conforme os comandos
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

// Alterado key para int para ficar conforme os comandos
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

// Alterado key para int para ficar conforme os comandos
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

// Alterado key para int para ficar conforme os comandos
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

//Funcoes Novas (2)
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
//Fim Funcoes (2)

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