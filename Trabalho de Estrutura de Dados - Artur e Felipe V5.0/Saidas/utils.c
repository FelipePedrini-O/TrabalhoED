/*
 Utils.c
 BookEd

 Created by Artur Vitor Cintra Bernardes && Felipe Pedrini Oliveira in 2025/1 at UFES.
*/

#include "utils.h"

void leLivros(tListaLivro* lista){
    FILE* f_livros = fopen("livros.txt", "r"); 
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
        insereListaLeitores(lista, criaLeitor(id, nome, gostos));
    }


    fclose(f_leitores);
}

FILE *incializaComandos()
{
    FILE* file = fopen("comandos.txt", "r");
    if(!file){
        fprintf(stderr, "ERRO! Arquivo comandos.txt nao encontrado\n");
        exit(1);
    }

    char header[256];
    fgets(header, sizeof(header), file);
    return file;
}

int leComando(FILE *comandos, int *funcionalidade, int *id_1, int *id_2, int *id_3)
{
    int flag = fscanf(comandos, "%d;%d;%d;%d", funcionalidade, id_1, id_2, id_3);
    if (flag == EOF) return 1;
    if (flag != 4) {
        fprintf(stderr, "ERRO! Linha malformada no arquivo de comandos\n");
        return 1;
    }
    return 0;
}

void liberaComandos(FILE *comandos)
{
    fclose(comandos);
}

void checkMemory(void *p)
{
    if(!p)
    {
        fprintf(stderr, "ERRO! Falta de memoria\n");
        exit(1);
    }
}

tLivro* retornaLivroBiblioteca(tListaLivro* lista, int key){
    return retornaLivroLista(lista, key);
}

void RunBookED(){
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
                if(livro && leitor)
                {
                    if(adicionaLivroLista(livro, retornaListaLidos(leitor)))
                        fprintf(saidas_f, "%s leu \"%s\"\n", retornaNomeLeitor(leitor), retornaNomeLivro(livro));
                    else
                        fprintf(saidas_f, "%s já leu \"%s\"\n", retornaNomeLeitor(leitor), retornaNomeLivro(livro));
                }
                if(!livro)
                    fprintf(saidas_f, "Erro: Livro com ID %d não encontrado\n", id_livro);
                if(!leitor)
                    fprintf(saidas_f, "Erro: Leitor com ID %d não encontrado\n", id_origem);
                break;
            }
            case 2: // Adicionar Livros Desejados
            {
                tLeitor *leitor = retornaLeitorListaLeitores(leitores, id_origem);
                tLivro *livro = retornaLivroLista(biblioteca, id_livro);
                if(livro && leitor)
                {
                    if(adicionaLivroLista(livro, retornaListaDesejados(leitor)))
                        fprintf(saidas_f, "%s deseja ler \"%s\"\n", retornaNomeLeitor(leitor), retornaNomeLivro(livro));
                    else
                        fprintf(saidas_f, "%s já deseja ler \"%s\"\n", retornaNomeLeitor(leitor), retornaNomeLivro(livro));
                }
                if(!livro)
                    fprintf(saidas_f, "Erro: Livro com ID %d não encontrado\n", id_livro);
                if(!leitor)
                    fprintf(saidas_f, "Erro: Leitor com ID %d não encontrado\n", id_origem);
                break;
            }
            case 3: // Recomendar um Livro
            {   
                tLivro *livro = retornaLivroLista(biblioteca, id_livro);
                if(!livro)
                {
                    tLeitor *origem = retornaLeitorListaLeitores(leitores, id_origem);
                    tLeitor *destino = retornaLeitorListaLeitores(leitores, id_destino);
                    if(!retornaLivroLista(retornaListarecomendados(destino), retornaIdLivro(livro)) && origem == destino)
                    {
                        fprintf(saidas_f, "%s não possui recomendação do livro ID %d feita por %s\n", retornaNomeLeitor(destino), id_livro, retornaNomeLeitor(origem));
                        break;
                    }
                    fprintf(saidas_f, "Erro: Livro com ID %d não encontrado\n", id_livro);
                    break;
                }
                recomendaLivroListaLeitores(leitores, livro, id_origem, id_destino, saidas_f);
                break;
            }
            case 4: // Aceitar Recomendação
            {
                tLivro *livro = retornaLivroLista(biblioteca, id_livro);
                if(!livro)
                {
                    tLeitor *origem = retornaLeitorListaLeitores(leitores, id_origem);
                    tLeitor *destino = retornaLeitorListaLeitores(leitores, id_destino);
                    if(!retornaLivroLista(retornaListarecomendados(destino), retornaIdLivro(livro)) && origem == destino)
                    {
                        fprintf(saidas_f, "%s não possui recomendação do livro ID %d feita por %s\n", retornaNomeLeitor(destino), id_livro, retornaNomeLeitor(origem));
                        break;
                    }
                    fprintf(saidas_f, "Erro: Livro com ID %d não encontrado\n", id_livro);
                    break;
                }
                // Origem e destino sao trocados segundo a documentacao
                aceitaRecomendacaoListaLeitores(leitores, livro, id_destino, id_origem, saidas_f);
                break;
            }
            case 5: // Remover Recomendação
            {
                tLivro *livro = retornaLivroLista(biblioteca, id_livro);
                if(!livro)
                {
                    tLeitor *origem = retornaLeitorListaLeitores(leitores, id_origem);
                    tLeitor *destino = retornaLeitorListaLeitores(leitores, id_destino);
                    if(!retornaLivroLista(retornaListarecomendados(destino), retornaIdLivro(livro)) && origem == destino)
                    {
                        fprintf(saidas_f, "%s não possui recomendação do livro ID %d feita por %s\n", retornaNomeLeitor(destino), id_livro, retornaNomeLeitor(origem));
                        break;
                    }
                    fprintf(saidas_f, "Erro: Livro com ID %d não encontrado\n", id_livro);
                    break;
                }
                // Origem e destino sao trocados segundo a documentacao
                recusaRecomendacaoListaLeitores(leitores, livro, id_destino, id_origem, saidas_f);
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
                if(leitor1 && leitor2)
                {
                    if(existeCaminhoAfinidade(leitor1, leitor2)){
                        fprintf(saidas_f, "Existe afinidade entre %s e %s\n", retornaNomeLeitor(leitor1), retornaNomeLeitor(leitor2));
                    }else{
                        fprintf(saidas_f, "Não existe afinidade entre %s e %s\n", retornaNomeLeitor(leitor1), retornaNomeLeitor(leitor2));
                    }

                }
                if(!leitor1)
                    fprintf(saidas_f, "Erro: Leitor com ID %d não encontrado\n", id_origem);
                if(!leitor2)
                    fprintf(saidas_f, "Erro: Leitor com ID %d não encontrado\n", id_destino);
                break;
            }
            case 8: // Imprime BookED
            {
                fprintf(saidas_f, "Imprime toda a BookED\n\n");
                imprimeListaLeitores(leitores, saidas_f); // Movido para o escopo do switch case
                break;
            }
            default:
                fprintf(saidas_f, "Erro: Comando %d não reconhecido\n", funcionalidade);
                break;
        }
    }
    liberaComandos(comandos_f);
    liberaListaLeitores(leitores);
    liberaBiblioteca(biblioteca);
    fclose(saidas_f);
}