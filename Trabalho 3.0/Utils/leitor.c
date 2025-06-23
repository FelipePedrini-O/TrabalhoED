#include "leitor.h"
#include "listaLivros.h"

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

tListaLivro* retornaListaLidos(tLeitor* l){
    return l->lidos;
}

tListaLivro* retornaListarecomendados(tLeitor* l){
    return l->recomendacoes;
}

tListaLivro* retornaListaDesejados(tLeitor* l){
    return l->desejados;
}

tLista* retornaAfinidades(tLeitor* l){
    return l->afinidades;
}

void adicionaLivroLista(tLivro* livro, tListaLivro* lista){
    insereLivro(lista, livro);
}

void retiraLivroLista(tListaLivro* lista, char* nome){
    retiraLivro(lista, nome);
}

void liberaLeitor(void* leitor){
    tLeitor* l = (tLeitor*) leitor;
    
    if(l != NULL){
        free(l->nome);

        liberaListaLivro(l->recomendacoes);
        liberaLista(l->afinidades);
        liberaListaLivro(l->desejados);
        liberaListaLivro(l->lidos);
        
        free(l);
        l = NULL;
    }
}
