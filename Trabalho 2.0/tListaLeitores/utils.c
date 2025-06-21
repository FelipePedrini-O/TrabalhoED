#include "utils.h"
#include "leitor.h"
#include "lista.h"
#include "listaLivros.h"
#include "listaLeitores.h"
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

//Novas Funcoes (2)
void static leAfinidadesLeitor(FILE* f_leitores, tLista* gostos){
    char leitor_gosto[100];
    fscanf(f_leitores, "%[^;];", leitor_gosto);
    char* gosto = strdup(leitor_gosto);
    insereListaFinal(gostos, gosto, free, (void*) printf);
}

void leLeitores(tListaLeitores* lista){
    FILE* f_leitores = fopen("leitores.txt", "r");
    if(!f_leitores){
        fprintf(stderr, "ERRO! Arquivo nao encontrado leitores.txt\n");
        exit(1);
    }

    char header[256];
    fgets(header, sizeof(header), f_leitores);

    char nome[100]; int id, n_afinidades;
    while(fscanf(f_leitores, "%d;%[^;];%d;", &id, nome, &n_afinidades) == 3){
        tLista* gostos = criaLista(); //Cria uma lista para guarda os gostos de um leitor: Terror, Drama e etc.
        for(int i=0; i<n_afinidades-1; i++){
            leAfinidadesLeitor(f_leitores, gostos);
        }

        //Le a "afinidade/gosto" final do leitor
        char leitor_gosto[100];
        fscanf(f_leitores, "%[^\n]%*c", leitor_gosto);
        char* gosto = strdup(leitor_gosto);
        insereListaFinal(gostos, gosto, free, (void*) printf);
        printf("%s: ", nome);
        imprimeLista(gostos);
        printf("\n");
        insereListaLeitores(lista, criaLeitor(id, nome, gostos));
    }


    fclose(f_leitores);
}
//Fim das Funcoes (2)

void checkMemory(void *p)
{
    if(!p)
    {
        fprintf(stderr, "ERRO! Falta de memoria\n");
        exit(1);
    }
}

tLivro* retornaLivroBiblioteca(tListaLivro* lista, char* titulo){
    return retornaLivroLista(lista, titulo);
}