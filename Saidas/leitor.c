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

void imprimeLeitor(tLeitor* l, FILE* saidas_f)//Imprime leitor modificado
{
    checkMemory(l);

    //printf("===== Leitor =====\n");

    //printf("ID: %d\n", l->id);
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

    //printf("==================\n");
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

// Alterado key para int para ficar conforme os comandos
void retiraLivroLista(tListaLivro* lista, int key){
    retiraLivro(lista, key);
}

//Funcoes novas (2)
int existeGostoEmComum(tLeitor* l1, tLeitor* l2){
    if(existeElementoNaOutraLista(l1->gostos, l2->gostos, strcmp)){
        return 1;
    }

    return 0;
}
//Fim das funcoes novas (2)

//Funcao (3)

int existeAfinidadeLeitores(tLeitor* orig, tLeitor* dest){//Nova funcao
    
    // Se for NULL retorna 0, se não retorna 1
    if (!retornaLeitorListaLeitores(retornaAfinidades(dest), retornaIdLeitor(orig)) && 
        !existeElementoEmComum(retornaAfinidades(orig), retornaAfinidades(dest))){
        return 0;
    }

    return 1;
}
//Fim (3)

void liberaLeitor(void* leitor){
    tLeitor* l = (tLeitor*) leitor;
    
    if(l != NULL){
        free(l->nome);
        liberaLista(l->gostos);

        liberaListaLivro(l->recomendacoes);
        //liberaListaLeitores(l->afinidades);       // Comentado para evitar double free
        liberaListaLivro(l->desejados);
        liberaListaLivro(l->lidos);
        
        free(l);
        l = NULL;
    }
}
