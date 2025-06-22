#include "listaLeitores.h"
#include "listaLivros.h"
#include "utils.h"

int main(void)
{
    // Incializacao dos arquivos
    FILE *comandos_f = incializaComandos();

    tListaLeitores *leitores = criaListaLeitores();
    leLeitores(leitores);

    tListaLivro *biblioteca = criaListaLivro();
    leLivros(biblioteca);

    // Loop principal do programa
    while (1)
    {
        int funcionalidade, id_origem, id_livro, id_destino;
        int fim_comandos = leComando(comandos_f, &funcionalidade, &id_origem, &id_livro, &id_destino);
        if(fim_comandos)
            break;

        switch (funcionalidade)
        {
            case 1: // Adicionar Livro Lido
            {
                tLeitor *leitor = retornaLeitorListaLeitores(leitores, id_origem);
                tLivro *livro = retornaLivroLista(biblioteca, id_livro);
                adicionaLivroLista(livro, retornaListaLidos(leitor));
                break;
            }
            case 2: // Adicionar Livros Desejados
            {
                tLeitor *leitor = retornaLeitorListaLeitores(leitores, id_origem);
                tLivro *livro = retornaLivroLista(biblioteca, id_livro);
                adicionaLivroLista(livro, retornaListaDesejados(leitor));
                break;
            }
            case 3: // Recomendar um Livro
            {
                tLivro *livro = retornaLivroLista(biblioteca, id_livro);
                recomendaLivroListaLeitores(leitores, livro, id_origem, id_destino);
                break;
            }
            case 4: // Aceitar Recomendação
            {
                tLivro *livro = retornaLivroLista(biblioteca, id_livro);
                // Origem e destino sao trocados segundo a documentacao
                aceitaRecomendacaoListaLeitores(leitores, livro, id_destino, id_origem);
                break;
            }
            case 5: // Remover Recomendação
            {
                tLivro *livro = retornaLivroLista(biblioteca, id_livro);
                // Origem e destino sao trocados segundo a documentacao
                recusaRecomendacaoListaLeitores(leitores, livro, id_destino, id_origem);
                break;
            }
            case 6: // Descobrir livro em comum entre Leitores
            {
                descobreLivrosComumListaLeitores(leitores, id_origem, id_destino);
                break;
            }
            case 7: // Verificar Afinidade
            {
                criaAfinidadesEntreLeitores(leitores);
                break;
            }
            case 8: // Imprime BookED
            {
                break;
            }
            default:
                printf("ERRO! Funcionalidade desconhecida: %d\n", funcionalidade);
                break;
        }
    }
    imprimeListaLeitores(leitores);
    liberaComandos(comandos_f);
    liberaListaLeitores(leitores);
    liberaBiblioteca(biblioteca);
    return 0;
}