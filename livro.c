#include "livro.h"

struct livro{
    char* titulo;
    char* autor;
    char* genero;
    int ano;
};

tLivro* criaLivro(char* titulo, char* autor, char* genero, int ano_publicacao){
    tLivro* livro = malloc(sizeof(*livro));

    livro->ano = ano_publicacao;
    livro->titulo = strdup(titulo);
    livro->autor = strdup(autor);
    livro->genero = strdup(genero);

    return livro;
}

char* retornaNomeLivro(void* livro){
    tLivro* l = (tLivro*) livro;

    return l->titulo;
}

void liberaLivro(void* livro){
    tLivro* l = (tLivro*) livro;

    if(l != NULL){
        free(l->titulo);
        free(l->autor);
        free(l->genero);
        free(l);
        l = NULL;
    }
}