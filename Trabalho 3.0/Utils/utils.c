#include "utils.h"
#include "listaLivros.h"
#include "livro.h"
#include <stdio.h>

void leLivros(tListaLivro* lista){
    FILE* f_livros = fopen("Livros.txt", "r");
    if(!f_livros){
        exit(1);
    }

    char header[256];
    fgets(header, sizeof(header), f_livros);


    char titulo[100], autor[100], genero[100]; int id, ano_publicacao;
    while(fscanf(f_livros, "%d;%[^;];%[^;];%[^;];%d", &id, titulo, autor, genero, &ano_publicacao) == 5){
        tLivro* livro = criaLivro(titulo, autor, genero, ano_publicacao, id);

        insereLivro(lista, livro);
    }

    fclose(f_livros);
}


tLivro* retornaLivroBiblioteca(tListaLivro* lista, char* titulo){
    return retornaLivroLista(lista, titulo);
}