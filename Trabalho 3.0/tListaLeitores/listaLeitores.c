#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "listaLeitores.h"

static int leitoresValidos(tLeitor *origem, tLeitor *destino);

// Node
typedef struct node
{
    tLeitor* leitor;
    struct node* prox;
    struct node* ant;
}
tNode;

tNode *criaNode(tLeitor *leitor)
{
    tNode *n = malloc(sizeof(*n));
    checkMemory(n);

    n->leitor = leitor;
    n->prox = NULL;
    n->ant = NULL;
    return n;
}

void imprimeNode(tNode *n)
{
    if(n->leitor)
        imprimeLeitor(n->leitor);
}

void liberaNode(tNode *n)
{
    if(n)
        free(n);
}

// Lista Leitores
struct listaLeitores
{
    tNode* prim;
    tNode* ult;
};

tListaLeitores *criaListaLeitores()
{
    tListaLeitores *l = malloc(sizeof(*l));
    checkMemory(l);

    l->prim = NULL;
    l->ult = NULL;
    return l;
}

void insereListaLeitores(tListaLeitores *l, tLeitor *leitor)
{
    tNode *n = criaNode(leitor);

    if(l->ult)
        l->ult->prox = n;
    n->ant = l->ult;
    n->prox = NULL;
    l->ult = n;

    if(!l->prim)
        l->prim = n;
}

tLeitor *retiraListaLeitores(tListaLeitores *l, int id)
{
    tNode *temp = l->prim;
    while(temp)
    {
        if(id == retornaIdLeitor(temp->leitor))
        {
            if(temp->ant)
                temp->ant->prox = temp->prox;
            if(temp->prox)
                temp->prox->ant = temp->ant;
            if(temp->ant == NULL)
                l->prim = temp->prox;
            if(temp->prox == NULL)
                l->ult = temp->ant;

            tLeitor *leitor = temp->leitor;
            liberaNode(temp);
            return leitor;
        }
        temp = temp->prox;
    }
    return NULL;
}

tLeitor *retornaLeitorListaLeitores(tListaLeitores *l, int id)
{
    tNode *temp = l->prim;
    while(temp)
    {
        if(id == retornaIdLeitor(temp->leitor))
            return temp->leitor;
        temp = temp->prox;
    }
    return NULL;
}

 /*
    A obrigacao de encontrar e verificar o livro eh do cliente
    Retorna 0 em caso de erro na verificacao e 1 em caso de exito
 */
int recomendaLivroListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino)
{
    tLeitor *origem = retornaLeitorListaLeitores(l, id_origem);
    tLeitor *destino = retornaLeitorListaLeitores(l, id_destino);

    if (!leitoresValidos(origem, destino))
        return 0;

    // Verifica se o livro já foi recomendado antes
    tListaLivro *recomendados = retornaListarecomendados(destino);
    tLivro *jaRecomendado = retornaLivroLista(recomendados, retornaNomeLivro(livro));
    if (jaRecomendado)
    {
        printf("Recomendacao ignorada! Livro '%s' ja foi recomendado ao leitor com id %d\n", 
                retornaNomeLivro(livro), id_destino);
        return 0;
    }

    adicionaLivroLista(livro, retornaListarecomendados(destino));
    return 1;
}

 /*
    A obrigacao de encontrar e verificar o livro eh do cliente
    Retorna 0 em caso de erro na verificacao e 1 em caso de exito
 */
int aceitaRecomendacaoListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino)
{
    tLeitor *origem = retornaLeitorListaLeitores(l, id_origem);
    tLeitor *destino = retornaLeitorListaLeitores(l, id_destino);

    if (!leitoresValidos(origem, destino))
        return 0;

    retiraLivro(retornaListarecomendados(destino), retornaNomeLivro(livro));

    // Verificacao da unicidade do livro na lista
    tListaLivro *desejados = retornaListaDesejados(destino);
    tLivro *livroNaLista = retornaLivroLista(desejados, retornaNomeLivro(livro));
    if(!livroNaLista)
        adicionaLivroLista(livro, desejados);
    return 1;
}

 /*
    A obrigacao de encontrar e verificar o livro eh do cliente
    Retorna 0 em caso de erro na verificacao e 1 em caso de exito
 */
int recusaRecomendacaoListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino)
{
    tLeitor *origem = retornaLeitorListaLeitores(l, id_origem);
    tLeitor *destino = retornaLeitorListaLeitores(l, id_destino);

    if (!leitoresValidos(origem, destino))
        return 0;

    retiraLivro(retornaListarecomendados(destino), retornaNomeLivro(livro));
    return 1;
}

void imprimeListaLeitores(tListaLeitores *l)
{
    tNode *temp = l->prim;
    printf("======== Lista de leitores =========\n");
    while(temp)
    {
        imprimeLeitor(temp->leitor);
        temp = temp->prox;
    }
    printf("===== Fim da lista de leitores =====\n");
}

void liberaListaLeitores(tListaLeitores *l)
{
    if(l)
    {
        tNode *temp = l->prim;
        while(temp)
        {
            tNode *aux = temp;
            temp = temp->prox;
            liberaNode(aux);
        }
        free(l);
    }
}

static int leitoresValidos(tLeitor *origem, tLeitor *destino)
{
    if (!origem)
    {
        printf("Leitor origem nao encontrado!\n");
        return 0;
    }
    if (!destino)
    {
        printf("Leitor destino nao encontrado!\n");
        return 0;
    }
    return 1;
}