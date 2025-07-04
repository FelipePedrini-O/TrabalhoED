/*
 TAD Livro.c
 BookEd

 Created by Artur Vitor Cintra Bernardes && Felipe Pedrini Oliveira in 2025/1 at UFES.
*/

#include "livro.h"
#include "utils.h"

struct livro{
    char* titulo;
    char* autor;
    char* genero;
    int ano;
    int id;
};

tLivro* criaLivro(char* titulo, char* autor, char* genero, int ano_publicacao, int id){
    tLivro* livro = malloc(sizeof(*livro));
    checkMemory(livro);

    livro->ano = ano_publicacao;
    livro->titulo = strdup(titulo);
    livro->autor = strdup(autor);
    livro->genero = strdup(genero);
    livro->id = id;

    return livro;
}

tLivro* leLivro(){
    FILE* f_livros = fopen("Livros.txt", "r");
    if(!f_livros){
        exit(1);
    }

    char titulo[100], autor[100], genero[100]; int id, ano_publicacao;
    if(fscanf(f_livros, "%d;%[^;];%[^;];%[^;];%d", &id, titulo, autor, genero, &ano_publicacao) == 5){
        printf("Correto! %s", titulo);
    }else{
        printf("erro!");
    }
    fclose(f_livros);

    return criaLivro(titulo, autor, genero, ano_publicacao, id);
}

char* retornaNomeLivro(void* livro){
    tLivro* l = (tLivro*) livro;
    if(l)
        return l->titulo;
    return NULL;
}

int retornaIdLivro(void *livro){
    tLivro* l = (tLivro*) livro;
    if(l)
        return l->id;
    return -1; // -1 para ponteiro do livro invalido
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