#include "leitor.h"

struct leitor{
    int id;
    char* nome;
    tListaLivro* recomendacoes;
    tListaLivro* desejados;
    tListaLivro* lidos;
    tLista* afinidades;
};

tLeitor* criaLeitor(int id, char* nome){
    tLeitor* leitor = malloc(sizeof(*leitor));

    leitor->nome = strdup(nome);
    leitor->id = id;
    
    leitor->recomendacoes = criaListaLivro();
    leitor->desejados = criaListaLivro();
    leitor->lidos = criaListaLivro();
    leitor->afinidades = criaLista();

    return leitor;
}

void adicionaLivroLido(tLeitor* leitor, tLivro* livro){
    insereLivro(leitor->lidos, livro);
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
