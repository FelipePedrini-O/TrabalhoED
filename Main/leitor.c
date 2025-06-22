#include "leitor.h"
#include "lista.h"
#include "listaLeitores.h"
#include "listaLivros.h"
#include "utils.h"

struct leitor{
    int id;
    char* nome;
    tLista* gostos;//Adicionado, para comportar os "gostos/afinidades" do leitor

    tListaLivro* recomendacoes;
    tListaLivro* desejados;
    tListaLivro* lidos;
    tListaLeitores* afinidades;//Modificado de tLista para tListaLeitores
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

// Funcoes novas

int retornaIdLeitor(tLeitor *l)
{
    return l->id;
}

char *retornaNomeLeitor(tLeitor* l)
{
    return l->nome;
}

void imprimeLeitor(tLeitor* l)
{
    checkMemory(l);

    printf("===== Leitor =====\n");

    printf("ID: %d\n", l->id);
    printf("Nome: %s\n", l->nome);

    printf("Livros lidos: ");
    imprimeListaLivro(l->lidos);
    printf("\n");

    printf("Livros desejados: ");
    imprimeListaLivro(l->desejados);
    printf("\n");

    printf("Livros recomendados: ");
    imprimeListaLivro(l->recomendacoes);
    printf("\n");

    printf("Afinidades: ");
    imprimeNomesListaLeitores(l->afinidades);
    printf("\n");

    printf("==================\n");
}

// Fim das funcoes novas

tListaLivro* retornaListaLidos(tLeitor* l){
    return l->lidos;
}

tListaLivro* retornaListarecomendados(tLeitor* l){
    return l->recomendacoes;
}

tListaLivro* retornaListaDesejados(tLeitor* l){
    return l->desejados;
}

void* retornaAfinidades(tLeitor* l){//Modificado, tem que ser desse jeito pois nao pode implementar listaLeitores no .h (recursivo)
    return (tListaLeitores*) l->afinidades;
}

void adicionaLivroLista(tLivro* livro, tListaLivro* lista){
    insereLivro(lista, livro);
}

void retiraLivroLista(tListaLivro* lista, char* nome){
    retiraLivro(lista, nome);
}

//Funcoes novas (2)
int existeGostoEmComum(tLeitor* l1, tLeitor* l2){
    if(existeElementoNaOutraLista(l1->gostos, l2->gostos, strcmp)){
        return 1;
    }

    return 0;
}
//Fim das funcoes novas (2)

void liberaLeitor(void* leitor){
    tLeitor* l = (tLeitor*) leitor;
    
    if(l != NULL){
        free(l->nome);
        liberaLista(l->gostos);

        liberaListaLivro(l->recomendacoes);
        liberaListaLeitores(l->afinidades);
        liberaListaLivro(l->desejados);
        liberaListaLivro(l->lidos);
        
        free(l);
        l = NULL;
    }
}
