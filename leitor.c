#include "leitor.h"
#include "lista.h"

struct leitor{
    int id;
    char* nome;
    tLista* recomendacoes;
    tLista* desejados;
    tLista* lidos;
    tLista* afinidades;
};

tLeitor* criaLeitor(int id, char* nome){
    tLeitor* leitor = malloc(sizeof(*leitor));

    leitor->nome = strdup(nome);
    leitor->id = id;
    
    leitor->recomendacoes = criaLista();
    leitor->desejados = criaLista();
    leitor->lidos = criaLista();
    leitor->afinidades = criaLista();

    return leitor;
}

void liberaLeitor(void* leitor){
    tLeitor* l = (tLeitor*) leitor;
    
    if(l != NULL){
        free(l->nome);

        liberaLista(l->recomendacoes);
        liberaLista(l->afinidades);
        liberaLista(l->desejados);
        liberaLista(l->lidos);
        
        free(l);
        l = NULL;
    }
}