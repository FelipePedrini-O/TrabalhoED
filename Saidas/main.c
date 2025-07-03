#include "leitor.h"
#include "listaLeitores.h"
#include "listaLivros.h"
#include "livro.h"
#include "utils.h"

int main(void)
{
    // Incializacao dos arquivos
    FILE *comandos_f = incializaComandos();

    tListaLeitores *leitores = criaListaLeitores();
    leLeitores(leitores);

    tListaLivro *biblioteca = criaListaLivro();
    leLivros(biblioteca);

    FILE *saidas_f = fopen("saida.txt", "w");
    if(!saidas_f){
        printf("Erro ao abrir arquivo saidas.txt");
        exit(1);
    }

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
                fprintf(saidas_f, "%s leu \"%s\"\n", retornaNomeLeitor(leitor), retornaNomeLivro(livro));
                break;
            }
            case 2: // Adicionar Livros Desejados
            {
                tLeitor *leitor = retornaLeitorListaLeitores(leitores, id_origem);
                tLivro *livro = retornaLivroLista(biblioteca, id_livro);
                adicionaLivroLista(livro, retornaListaDesejados(leitor));
                fprintf(saidas_f, "%s deseja ler \"%s\"\n", retornaNomeLeitor(leitor), retornaNomeLivro(livro));
                break;
            }
            case 3: // Recomendar um Livro
            {   
                tLeitor *leitor1 = retornaLeitorListaLeitores(leitores, id_origem);
                tLeitor *leitor2 = retornaLeitorListaLeitores(leitores, id_destino);
                tLivro *livro = retornaLivroLista(biblioteca, id_livro);
                recomendaLivroListaLeitores(leitores, livro, id_origem, id_destino);
                fprintf(saidas_f, "%s recomenda \"%s\" para %s\n", retornaNomeLeitor(leitor1), retornaNomeLivro(livro), retornaNomeLeitor(leitor2));
                break;
            }
            case 4: // Aceitar Recomendação
            {
                tLeitor *leitor1 = retornaLeitorListaLeitores(leitores, id_origem);
                tLeitor *leitor2 = retornaLeitorListaLeitores(leitores, id_destino);
                tLivro *livro = retornaLivroLista(biblioteca, id_livro);
                // Origem e destino sao trocados segundo a documentacao
                aceitaRecomendacaoListaLeitores(leitores, livro, id_destino, id_origem);
                fprintf(saidas_f, "%s aceita recomendação \"%s\" de %s\n", retornaNomeLeitor(leitor1), retornaNomeLivro(livro), retornaNomeLeitor(leitor2));
                break;
            }
            case 5: // Remover Recomendação
            {
                tLeitor *leitor1 = retornaLeitorListaLeitores(leitores, id_origem);
                tLeitor *leitor2 = retornaLeitorListaLeitores(leitores, id_destino);
                tLivro *livro = retornaLivroLista(biblioteca, id_livro);
                // Origem e destino sao trocados segundo a documentacao
                recusaRecomendacaoListaLeitores(leitores, livro, id_destino, id_origem);
                fprintf(saidas_f, "%s rejeita recomendação \"%s\" de %s\n", retornaNomeLeitor(leitor1), retornaNomeLivro(livro), retornaNomeLeitor(leitor2));
                break;
            }
            case 6: // Descobrir livro em comum entre Leitores
            {
                descobreLivrosComumListaLeitores(leitores, id_origem, id_destino, saidas_f);//Funcao que printa os livros em comum
                break;
            }
            case 7: // Verificar Afinidade
            {
                criaAfinidadesEntreLeitores(leitores);
                tLeitor *leitor1 = retornaLeitorListaLeitores(leitores, id_origem);
                tLeitor *leitor2 = retornaLeitorListaLeitores(leitores, id_destino);
                if(existeAfinidadeLeitores(leitor1, leitor2)){
                    fprintf(saidas_f, "Existe afinidade entre %s e %s\n", retornaNomeLeitor(leitor1), retornaNomeLeitor(leitor2));
                }else{
                    fprintf(saidas_f, "Não existe afinidade entre %s e %s\n", retornaNomeLeitor(leitor1), retornaNomeLeitor(leitor2));
                }
                break;
            }
            case 8: // Imprime BookED
            {
                fprintf(saidas_f, "Imprime toda a BookED\n\n");
                imprimeListaLeitores(leitores, saidas_f); // Movido para o escopo do switch case
                break;
            }
            default:
                fprintf(saidas_f, "ERRO! Funcionalidade desconhecida: %d\n", funcionalidade);
                break;
        }
    }
    liberaComandos(comandos_f);
    liberaListaLeitores(leitores);
    liberaBiblioteca(biblioteca);
    fclose(saidas_f);
    return 0;
}