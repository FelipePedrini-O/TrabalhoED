/*
 Leitor.c
 BookEd

 Created by Artur Vitor Cintra Bernardes && Felipe Pedrini Oliveira in 2025/1 at UFES.
*/

#include "listaLeitores.h"
#include "utils.h"

struct leitor{
    int id;
    char* nome;
    tLista* gostos;

    tListaLivro* recomendacoes;
    tListaLivro* desejados;
    tListaLivro* lidos;
    tListaLeitores* afinidades;
};

tLeitor* criaLeitor(int id, char* nome, tLista* gostos){
    tLeitor* leitor = malloc(sizeof(*leitor));

    leitor->nome = strdup(nome);
    leitor->id = id;
    leitor->gostos = gostos;
    
    leitor->recomendacoes = criaListaLivro();
    leitor->desejados = criaListaLivro();
    leitor->lidos = criaListaLivro();
    leitor->afinidades = criaListaLeitores();

    return leitor;
}

int retornaIdLeitor(tLeitor *l)
{
    if(l)
        return l->id;
    return -999;
}

char *retornaNomeLeitor(tLeitor* l)
{
    if(l)
        return l->nome;
    return NULL;
}

void imprimeLeitor(tLeitor* l, FILE* saidas_f)
{
    if(l)
    {
        checkMemory(l);
    
        fprintf(saidas_f, "Leitor: %s\n", l->nome);
    
        fprintf(saidas_f, "Lidos: ");
        imprimeListaLivro(l->lidos, saidas_f);
        fprintf(saidas_f, "\n");
    
        fprintf(saidas_f, "Desejados: ");
        imprimeListaLivro(l->desejados, saidas_f);
        fprintf(saidas_f, "\n");
    
        fprintf(saidas_f, "Recomendacoes: ");
        imprimeListaLivro(l->recomendacoes, saidas_f);
        fprintf(saidas_f, "\n");
    
        fprintf(saidas_f, "Afinidades: ");
        imprimeNomesListaLeitores(l->afinidades, saidas_f);
        fprintf(saidas_f, "\n");
    }
}

tListaLivro* retornaListaLidos(tLeitor* l){
    if(l)
        return l->lidos;
    return NULL;
}

tListaLivro* retornaListarecomendados(tLeitor* l){
    if(l)
        return l->recomendacoes;
    return NULL;
}

tListaLivro* retornaListaDesejados(tLeitor* l){
    if(l)
        return l->desejados;
    return NULL;
}

void* retornaAfinidades(tLeitor* l){
    if(l)
        return (tListaLeitores*) l->afinidades;
    return NULL;
}

tLista* retornaGostos(tLeitor* l){
    return l->gostos;
}

int adicionaLivroLista(tLivro* livro, tListaLivro* lista){ // Alterado retorno para int para adicionar a flag
    if(!retornaLivroLista(lista, retornaIdLivro(livro)))
    {
        insereLivro(lista, livro);
        return 1;
    }
    return 0;
}

void retiraLivroLista(tListaLivro* lista, int key){
    retiraLivro(lista, key);
}

int existeGostoEmComum(tLeitor* l1, tLeitor* l2){
    if(l1 && l2)
    {
        if(existeElementoNaOutraLista(l1->gostos, l2->gostos, strcmp)){
            return 1;
        }
    }

    return 0;
}

void liberaLeitor(void* leitor){
    tLeitor* l = (tLeitor*) leitor;
    
    if(l != NULL){
        free(l->nome);
        liberaLista(l->gostos);

        liberaLeitoresDaListaAfinidadesLeitores(l->afinidades);
        liberaListaLivro(l->recomendacoes);
        liberaListaLivro(l->desejados);
        liberaListaLivro(l->lidos);
        
        free(l);
        l = NULL;
    }
}
