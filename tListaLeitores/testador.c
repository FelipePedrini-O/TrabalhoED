#include "listaLeitores.h"
#include "listaLivros.h"
#include "utils.h"

int main(){
    // Cria lista de leitores
    tListaLeitores *listaLeitores = criaListaLeitores();

    // Cria leitores para teste
    int id; char nome[50];
    scanf("%d %[^\n]", &id, nome);
    tLeitor* leitor1 = criaLeitor(id, nome);
    insereListaLeitores(listaLeitores, leitor1);
    imprimeListaLeitores(listaLeitores);

    scanf("%d %[^\n]", &id, nome);
    tLeitor* leitor2 = criaLeitor(id, nome);
    insereListaLeitores(listaLeitores, leitor2);
    imprimeListaLeitores(listaLeitores);
    
    scanf("%d %[^\n]", &id, nome);
    tLeitor* leitor3 = criaLeitor(id, nome);
    insereListaLeitores(listaLeitores, leitor3);
    imprimeListaLeitores(listaLeitores);

    // Cria a biblioteca
    tListaLivro* biblioteca = criaListaLivro();
    leLivros(biblioteca);
    printf("===== Livros na biblioteca: =====\n\n");
    imprimeListaLivro(biblioteca);
    printf("\n\n======= Fim da biblioteca =======\n");

    // Adiciona vários livros aos leitores
    adicionaLivroLista(retornaLivroLista(biblioteca, "O Iluminado"), retornaListaLidos(leitor1));
    adicionaLivroLista(retornaLivroLista(biblioteca, "1984"), retornaListaDesejados(leitor1));
    adicionaLivroLista(retornaLivroLista(biblioteca, "Duna"), retornaListaLidos(leitor1));

    adicionaLivroLista(retornaLivroLista(biblioteca, "Garota Exemplar"), retornaListaLidos(leitor2));
    adicionaLivroLista(retornaLivroLista(biblioteca, "O Nome da Rosa"), retornaListaDesejados(leitor2));
    adicionaLivroLista(retornaLivroLista(biblioteca, "O Senhor dos Anéis: A Sociedade do Anel"), retornaListaLidos(leitor2));

    adicionaLivroLista(retornaLivroLista(biblioteca, "Orgulho e Preconceito"), retornaListaLidos(leitor3));
    adicionaLivroLista(retornaLivroLista(biblioteca, "Como Eu Era Antes de Você"), retornaListaDesejados(leitor3));
    adicionaLivroLista(retornaLivroLista(biblioteca, "A Culpa é das Estrelas"), retornaListaDesejados(leitor3));
    adicionaLivroLista(retornaLivroLista(biblioteca, "It: A Coisa"), retornaListaLidos(leitor3));

    // Imprime novamente os leitores com seus livros lidos
    imprimeListaLeitores(listaLeitores);

    // Obtem um leitor da lista para teste
    printf("\nLeitor obtido:\n");
    imprimeLeitor(retornaLeitorListaLeitores(listaLeitores, 1));

    /* Testes de recomendacao */

    printf("\nLeitor %s está recomendando 'Duna' para Leitor %s...\n", 
        retornaNomeLeitor(leitor1), retornaNomeLeitor(leitor2));
    recomendaLivroListaLeitores(listaLeitores, retornaLivroLista(biblioteca, "Duna"), 
        retornaIdLeitor(leitor1), retornaIdLeitor(leitor2));

    printf("\nLeitor %s aceita a recomendação de 'Duna'\n", retornaNomeLeitor(leitor2));
    aceitaRecomendacaoListaLeitores(listaLeitores, retornaLivroLista(biblioteca, "Duna"), 
        retornaIdLeitor(leitor2));

    printf("\nLeitor %s está recomendando '1984' para Leitor %s...\n", 
        retornaNomeLeitor(leitor1), retornaNomeLeitor(leitor3));
    recomendaLivroListaLeitores(listaLeitores, retornaLivroLista(biblioteca, "1984"), 
        retornaIdLeitor(leitor1), retornaIdLeitor(leitor3));

    printf("\nLeitor %s recusa a recomendação de '1984'\n", retornaNomeLeitor(leitor3));
    recusaRecomendacaoListaLeitores(listaLeitores, retornaLivroLista(biblioteca, "1984"), 
        retornaIdLeitor(leitor1), retornaIdLeitor(leitor3));

    printf("\nLeitor %s está recomendando 'It: A Coisa' para Leitor %s\n", 
        retornaNomeLeitor(leitor3), retornaNomeLeitor(leitor1));
    recomendaLivroListaLeitores(listaLeitores, retornaLivroLista(biblioteca, "It: A Coisa"), 
        retornaIdLeitor(leitor3), retornaIdLeitor(leitor1));

    printf("\nLeitor %s está recomendando 'It: A Coisa' para Leitor %s\n", 
        retornaNomeLeitor(leitor3), retornaNomeLeitor(leitor2));
    recomendaLivroListaLeitores(listaLeitores, retornaLivroLista(biblioteca, "It: A Coisa"), 
        retornaIdLeitor(leitor3), retornaIdLeitor(leitor2));

    printf("\nLeitor %s está recomendando 'It: A Coisa' para Leitor %s novamente...\n", 
        retornaNomeLeitor(leitor3), retornaNomeLeitor(leitor2));
    recomendaLivroListaLeitores(listaLeitores, retornaLivroLista(biblioteca, "It: A Coisa"), 
        retornaIdLeitor(leitor3), retornaIdLeitor(leitor2));

    // Imprime novamente para verificar os resultados após recomendações
    printf("\n======= Estado final dos leitores =======\n");
    imprimeListaLeitores(listaLeitores);
    printf("\n============ Fim dos testes =============\n");

    // Libera a memoria utilizada
    liberaListaLeitores(listaLeitores);
    liberaLeitor(leitor1);
    liberaLeitor(leitor2);
    liberaLeitor(leitor3);
    liberaBiblioteca(biblioteca);

    return 0;
}