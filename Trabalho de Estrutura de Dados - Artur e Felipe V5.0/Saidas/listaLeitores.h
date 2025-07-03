/*
 TAD Lista_de_Leitores.h
 BookEd

 Created by Artur Vitor Cintra Bernardes && Felipe Pedrini Oliveira in 2025/1 at UFES.
*/

#ifndef LISTA_LEITORES_H
#define LISTA_LEITORES_H

#include "leitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaLivros.h"

typedef struct listaLeitores tListaLeitores;

/**
 * @brief Cria e inicializa uma nova lista de leitores vazia.
 * Pre_condicao: Memória suficiente para alocar uma estrutura do tipo tListaLeitores
 * Pos_condicao: Retorna ponteiro para lista de leitores vazia.
 * 
 * @return Ponteiro para estrutura tListaLeitores recém-criada.
 */
tListaLeitores* criaListaLeitores();

/**
 * @brief Insere um leitor na lista de leitores.
 * Pre_condicao: Ponteiros válidos para lista e para leitor inicializado.
 * Pos_condicao: O leitor é adicionado à lista.
 * 
 * @param l Ponteiro para lista de leitores.
 * @param leitor Ponteiro para o leitor a ser inserido.
 */
void insereListaLeitores(tListaLeitores* l, tLeitor* leitor);

/**
 * @brief Remove e libera um leitor da lista com base no seu ID.
 * Pre_condicao: Lista e ID válidos.
 * Pos_condicao: O leitor com o ID correspondente é removido e sua memória liberada.
 * 
 * @param l Ponteiro para lista de leitores.
 * @param id Identificador do leitor a ser removido.
 */
void retiraListaLeitores(tListaLeitores* l, int id);

/**
 * @brief Retorna um leitor com determinado ID na lista.
 * Pre_condicao: Lista válida.
 * Pos_condicao: Nenhuma alteração na lista.
 * 
 * @param l Ponteiro para lista de leitores.
 * @param id ID do leitor a ser buscado.
 * @return Ponteiro para tLeitor, ou NULL se não encontrado.
 */
tLeitor* retornaLeitorListaLeitores(tListaLeitores* l, int id);

/**
 * @brief Recomenda um livro de um leitor a outro, se houver afinidade.
 * Pre_condicao: IDs válidos e leitores existentes na lista. A obrigação de encontrar e verificar o livro é do cliente
 * Pos_condicao: Recomendação é registrada ou rejeitada, e escrita no arquivo de saída.
 * 
 * @param l Lista de leitores.
 * @param livro Livro a ser recomendado.
 * @param id_origem ID do leitor que recomenda.
 * @param id_destino ID do leitor que recebe a recomendação.
 * @param saidas_f Arquivo de saída.
 * @return 1 se a recomendação foi feita, 0 caso contrário.
 */
int recomendaLivroListaLeitores(tListaLeitores* l, tLivro* livro, int id_origem, int id_destino, FILE* saidas_f);

/**
 * @brief Aceita uma recomendação de livro entre dois leitores.
 * Pre_condicao: Leitores com IDs válidos e recomendação existente. A obrigação de encontrar e verificar o livro é do cliente
 * Pos_condicao: Livro é adicionado à lista do leitor destino; mensagem registrada no arquivo.
 * 
 * @param l Lista de leitores.
 * @param livro Livro recomendado.
 * @param id_origem ID do leitor que recomendou.
 * @param id_destino ID do leitor que recebe.
 * @param saidas_f Arquivo de saída.
 * @return 1 se aceito, 0 caso contrário.
 */
int aceitaRecomendacaoListaLeitores(tListaLeitores* l, tLivro* livro, int id_origem, int id_destino, FILE* saidas_f);

/**
 * @brief Recusa uma recomendação de livro entre dois leitores.
 * Pre_condicao: Leitores com IDs válidos. A obrigação de encontrar e verificar o livro é do cliente
 * Pos_condicao: Recomendação é rejeitada e mensagem é escrita no arquivo.
 * 
 * @param l Lista de leitores.
 * @param livro Livro recomendado.
 * @param id_origem ID do leitor que recomendou.
 * @param id_destino ID do leitor que recusou.
 * @param saidas_f Arquivo de saída.
 * @return 1 se recusa registrada, 0 caso contrário.
 */
int recusaRecomendacaoListaLeitores(tListaLeitores* l, tLivro* livro, int id_origem, int id_destino, FILE* saidas_f);

/**
 * @brief Verifica e imprime os livros em comum entre dois leitores.
 * Pre_condicao: Leitores com IDs válidos devem existir na lista.
 * Pos_condicao: Lista de livros em comum é escrita no arquivo.
 * 
 * @param l Lista de leitores.
 * @param id_origem ID de um leitor.
 * @param id_destino ID do outro leitor.
 * @param saidas_f Arquivo de saída.
 * @return Número de livros em comum.
 */
int descobreLivrosComumListaLeitores(tListaLeitores* l, int id_origem, int id_destino, FILE* saidas_f);

/**
 * @brief Imprime os nomes de todos os leitores da lista no arquivo especificado.
 * Pre_condicao: Lista de leitores válida; arquivo aberto para escrita.
 * Pos_condicao: Nomes dos leitores são escritos no arquivo.
 * 
 * @param l Lista de leitores.
 * @param saidas_f Arquivo de saída.
 */
void imprimeNomesListaLeitores(tListaLeitores* l, FILE* saidas_f);

/**
 * @brief Libera apenas o nó e não o leitor para evitar double free de afinidades/afins
 * Pre_condicao: Lista válida contendo leitores.
 * Pos_condicao: Memória de todos os nós da lista liberados.
 * 
 * @param l Lista de leitores.
 */
void liberaLeitoresDaListaAfinidadesLeitores(tListaLeitores* l);

/**
 * @brief Cria afinidades entre leitores da lista com base em gostos em comum.
 * Pre_condicao: Lista válida e leitores com gostos definidos.
 * Pos_condicao: Afinidades são registradas internamente.
 * 
 * @param l Lista de leitores.
 */
void criaAfinidadesEntreLeitores(tListaLeitores* l);

/**
 * @brief Verifica se existe um caminho de afinidade entre dois leitores.
 * Pre_condicao: Lista de visitados inicializada; leitores válidos.
 * Pos_condicao: Nenhuma alteração nas estruturas.
 * 
 * @param visitados Lista de leitores já visitados na busca.
 * @param origem Leitor de origem.
 * @param destino Leitor de destino.
 * @return 1 se há caminho, 0 caso contrário.
 */
int existeCaminhoAfinidade(tLeitor* origem, tLeitor* destino);

/**
 * @brief Verifica se há pelo menos um leitor em comum entre duas listas.
 * Pre_condicao: Listas válidas.
 * Pos_condicao: Nenhuma alteração nas listas.
 * 
 * @param l1 Primeira lista de leitores.
 * @param l2 Segunda lista de leitores.
 * @return 1 se há leitor em comum, 0 caso contrário.
 */
int existeElementoEmComum(tListaLeitores* l1, tListaLeitores* l2);

/**
 * @brief Imprime os dados completos de todos os leitores da lista no arquivo.
 * Pre_condicao: Lista e arquivo válidos.
 * Pos_condicao: Dados são escritos no arquivo.
 * 
 * @param l Lista de leitores.
 * @param saidas_f Arquivo de saída.
 */
void imprimeListaLeitores(tListaLeitores* l, FILE* saidas_f);

/**
 * @brief Libera toda a memória alocada pela lista de leitores e seus elementos.
 * Pre_condicao: Lista válida e leitores alocados dinamicamente.
 * Pos_condicao: Todos os leitores e a lista são removidos da memória.
 * 
 * @param l Ponteiro para a lista de leitores.
 */
void liberaListaLeitores(tListaLeitores* l);

#endif