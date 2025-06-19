#include "leitor.h"
#include "listaLivros.h"
#include "utils.h"

int main(){
    int id; char nome[50];
    
    printf("Diga o id do leitor e seu nome: ");
    scanf("%d %s", &id, nome);

    tLeitor* leitor = criaLeitor(id, nome);

    tListaLivro* biblioteca = criaListaLivro();
    leLivros(biblioteca);
    imprimeListaLivro(biblioteca);

    tLivro* livro = retornaLivroLista(biblioteca, "O Iluminado");
    adicionaLivroLista(livro, retornaListaLidos(leitor));

    printf("\nLidos: ");
    imprimeListaLivro(retornaListaLidos(leitor));

    retiraLivroLista(retornaListaLidos(leitor), "O Iluminad");
    printf("\nLidos: ");
    imprimeListaLivro(retornaListaLidos(leitor));

    liberaBiblioteca(biblioteca);
    liberaLeitor(leitor);

    return 0;
}