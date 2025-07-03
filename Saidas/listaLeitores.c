#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitor.h"
#include "listaLivros.h"
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

void imprimeNode(tNode *n, FILE* saidas_f)
{
    if(n->leitor)
        imprimeLeitor(n->leitor, saidas_f);
}

void liberaNode(tNode *n)
{
    if(n)
    {
        liberaLeitor(n->leitor); // Alteracao feita para liberar o leitor dentro da lista
        free(n);
    }
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
    if(l)
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
}

void retiraListaLeitores(tListaLeitores *l, int id)
{
    if(l)
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
    
                liberaNode(temp);
                return;
            }
            temp = temp->prox;
        }
    }
}

tLeitor *retornaLeitorListaLeitores(tListaLeitores *l, int id)
{
    if(l)
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
}

 /*
    A obrigacao de encontrar e verificar o livro eh do cliente
    Retorna 0 em caso de erro na verificacao e 1 em caso de exito
 */
int recomendaLivroListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino, FILE* saidas_f)
{
    tLeitor *origem = retornaLeitorListaLeitores(l, id_origem);
    tLeitor *destino = retornaLeitorListaLeitores(l, id_destino);

    if (!leitoresValidos(origem, destino))
    {
        if(origem == destino)
            fprintf(saidas_f, "%s não pode recomendar livros para si mesmo\n", retornaNomeLeitor(origem));
        if(!origem)
            fprintf(saidas_f, "Erro: Leitor recomendador com ID %d não encontrado\n", id_origem);
        if(!destino)
            fprintf(saidas_f, "Erro: Leitor destinatário com ID %d não encontrado\n", id_destino);
        return 0;
    }

    // Verifica se o livro já foi recomendado antes
    tLivro *jaRecomendado = retornaLivroLista(retornaListarecomendados(destino), retornaIdLivro(livro));
    tLivro *jaDesejado = retornaLivroLista(retornaListaDesejados(destino), retornaIdLivro(livro));
    tLivro *jaLido = retornaLivroLista(retornaListaLidos(destino), retornaIdLivro(livro));
    if (jaRecomendado)
    {
        //printf("Recomendacao ignorada! Livro '%s' ja foi recomendado ao leitor com id %d\n", 
        //        retornaNomeLivro(livro), id_destino);
        return 0;
    }
    else if(jaDesejado)
    {
        fprintf(saidas_f,"%s já deseja ler \"%s\", recomendação desnecessária\n", retornaNomeLeitor(destino), retornaNomeLivro(livro));
        return 0;
    }
    else if (jaLido)
    {
        fprintf(saidas_f, "%s não precisa da recomendação de \"%s\" pois já leu este livro\n", retornaNomeLeitor(destino), retornaNomeLivro(livro));
        return 0;
    }
    fprintf(saidas_f, "%s recomenda \"%s\" para %s\n", retornaNomeLeitor(origem), retornaNomeLivro(livro), retornaNomeLeitor(destino));
    adicionaLivroLista(livro, retornaListarecomendados(destino));
    return 1;
}

 /*
    A obrigacao de encontrar e verificar o livro eh do cliente
    Retorna 0 em caso de erro na verificacao e 1 em caso de exito
 */
int aceitaRecomendacaoListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino, FILE* saidas_f)
{
    tLeitor *origem = retornaLeitorListaLeitores(l, id_origem);
    tLeitor *destino = retornaLeitorListaLeitores(l, id_destino);

    if (!leitoresValidos(origem, destino))
    {
        if(!retornaLivroLista(retornaListarecomendados(destino), retornaIdLivro(livro)) && origem == destino)
        {
            fprintf(saidas_f, "%s não possui recomendação do livro ID %d feita por %s\n", retornaNomeLeitor(destino), retornaIdLivro(livro), retornaNomeLeitor(origem));
            return 0;
        }
        if(origem == destino)
            fprintf(saidas_f, "%s não pode recomendar livros para si mesmo\n", retornaNomeLeitor(origem));
        if(!origem)
            fprintf(saidas_f, "Erro: Leitor recomendador com ID %d não encontrado\n", id_origem);
        if(!destino)
            fprintf(saidas_f, "Erro: Leitor com ID %d não encontrado\n", id_destino);
        return 0;
    }
    else if(!retornaLivroLista(retornaListarecomendados(destino), retornaIdLivro(livro)))
    {
        fprintf(saidas_f, "%s não possui recomendação do livro ID %d feita por %s\n", retornaNomeLeitor(destino), retornaIdLivro(livro), retornaNomeLeitor(origem));
        return 0;
    }

    retiraLivro(retornaListarecomendados(destino), retornaIdLivro(livro));

    // Verificacao da unicidade do livro na lista
    tListaLivro *desejados = retornaListaDesejados(destino);
    tLivro *livroNaLista = retornaLivroLista(desejados, retornaIdLivro(livro));
    if(!livroNaLista)
    {
        adicionaLivroLista(livro, desejados);
        fprintf(saidas_f, "%s aceita recomendação \"%s\" de %s\n", retornaNomeLeitor(destino), retornaNomeLivro(livro), retornaNomeLeitor(origem));
    }
    else
    {
        return 0;
    }
    return 1;
}

 /*
    A obrigacao de encontrar e verificar o livro eh do cliente
    Retorna 0 em caso de erro na verificacao e 1 em caso de exito
 */
int recusaRecomendacaoListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino, FILE* saidas_f)
{
    tLeitor *origem = retornaLeitorListaLeitores(l, id_origem);
    tLeitor *destino = retornaLeitorListaLeitores(l, id_destino);

    if (!leitoresValidos(origem, destino))
    {
        if(origem == destino)
            fprintf(saidas_f, "%s não pode recomendar livros para si mesmo\n", retornaNomeLeitor(origem));
        if(!origem)
            fprintf(saidas_f, "Erro: Leitor recomendador com ID %d não encontrado\n", id_origem);
        if(!destino)
            fprintf(saidas_f, "Erro: Leitor com ID %d não encontrado\n", id_destino);
        return 0;
    }
    else if(!retornaLivroLista(retornaListarecomendados(destino), retornaIdLivro(livro)))
    {
        fprintf(saidas_f, "%s não possui recomendação do livro ID %d feita por %s\n", retornaNomeLeitor(destino), retornaIdLivro(livro), retornaNomeLeitor(origem));
        return 0;
    }

    retiraLivro(retornaListarecomendados(destino), retornaIdLivro(livro));
    fprintf(saidas_f, "%s rejeita recomendação \"%s\" de %s\n", retornaNomeLeitor(destino), retornaNomeLivro(livro), retornaNomeLeitor(origem));
    return 1;
}

// Funcoes Novas (2)

int descobreLivrosComumListaLeitores(tListaLeitores *l, int id_origem, int id_destino, FILE* saidas_f){
    tLeitor *origem = retornaLeitorListaLeitores(l, id_origem);
    tLeitor *destino = retornaLeitorListaLeitores(l, id_destino);

    if (!leitoresValidos(origem, destino)){
        if(!origem)
            fprintf(saidas_f, "Erro: Leitor com ID %d não encontrado\n", id_origem);
        if(!destino)
            fprintf(saidas_f, "Erro: Leitor com ID %d não encontrado\n", id_destino);
        return 0;
    }

    tListaLivro* origemLidos = retornaListaLidos(origem);
    tListaLivro* destinoLidos = retornaListaLidos(destino);

    tListaLivro* livros_em_comum = retornaLivrosEmComumListaLivro(origemLidos, destinoLidos);
    
    fprintf(saidas_f, "Livros em comum entre %s e %s: ", retornaNomeLeitor(origem), retornaNomeLeitor(destino));
    if(!listaVazia(livros_em_comum)){
        imprimeListaLivro(livros_em_comum, saidas_f);
        fprintf(saidas_f, "\n");
    }else{
        fprintf(saidas_f, "Nenhum livro em comum\n");
    }

    liberaListaLivro(livros_em_comum);

    return 1;
}

void imprimeNomesListaLeitores(tListaLeitores* l, FILE* saidas_f){
    if(l)
    {
        tNode *temp = l->prim;
        if(temp == NULL)
            fprintf(saidas_f, "\n");
        while(temp)
        {
            if(temp->prox != NULL){
                fprintf(saidas_f, "%s, ", retornaNomeLeitor(temp->leitor));
            }else{
                fprintf(saidas_f, "%s\n", retornaNomeLeitor(temp->leitor));
            }
            temp = temp->prox;
        }
    }
}

// Funcao de uso uncico e exclusivo para a liberacao das afinidades
void liberaLeitoresDaListaAfinidadesLeitores(tListaLeitores *l)
{
    if(l)
    {
        tNode *temp = l->prim;
        while(temp)
        {
            tNode *aux = temp;
            temp = temp->prox;
            free(aux); // Libera apenas o no e nao o leitor para evitar double free de afinidades
        }
        free(l);
    }
}

// Funcao alterada para evitar duplicatas na lista de afinidades
static void insereAfinidadeEntreLeitores(tListaLeitores* l, tLeitor* target){
    if(l)
    {
        tNode* p  = l->prim;
    
        while(p != NULL){
            if(p->leitor != target && existeGostoEmComum(p->leitor, target)){
                // Só insere se ainda não estiver presente
                if (!retornaLeitorListaLeitores(retornaAfinidades(target), retornaIdLeitor(p->leitor))) {
                    insereListaLeitores(retornaAfinidades(target), p->leitor);
                }
            }
            p = p->prox;
        }
    }
}

void criaAfinidadesEntreLeitores(tListaLeitores* l){
    if(l)
    {
        tNode* aux = l->prim;
    
        while(aux != NULL){
            insereAfinidadeEntreLeitores(l, aux->leitor);
            aux = aux->prox;
        }
    }
}

//Fim das Funcoes (2)

//F(3)
int existeElementoEmComum(tListaLeitores* l1, tListaLeitores* l2){
    if(l1 && l2)
    {
        tNode* aux = l1->prim;
    
        while(aux != NULL){
            tNode* p = l2->prim;
            while(p != NULL){
                if(strcmp(retornaNomeLeitor(aux->leitor), retornaNomeLeitor(p->leitor)) == 0){//Compara os nomes
                    return 1;
                }
                p = p->prox;
            }
            aux = aux->prox;
        }
    }

    return 0;
}
//Fim(3)

void imprimeListaLeitores(tListaLeitores *l, FILE* saidas_f)
{
    if(l)
    {
        tNode *temp = l->prim;
        //printf("======== Lista de leitores =========\n");
        while(temp)
        {
            imprimeLeitor(temp->leitor, saidas_f);
            temp = temp->prox;
        }
        //printf("===== Fim da lista de leitores =====\n");
    }
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
        //printf("Leitor origem nao encontrado!\n");
        return 0;
    }
    if (!destino)
    {
        //printf("Leitor destino nao encontrado!\n");
        return 0;
    }
    if(origem == destino) // Update da leitoresValidos
    {
        //printf("Leior destino nao pode ser o mesmo da origem\n");
        return 0;
    }
    return 1;
}