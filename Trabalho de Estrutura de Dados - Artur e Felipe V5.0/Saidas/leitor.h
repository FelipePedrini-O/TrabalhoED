/*
 Leitor.h
 BookEd

 Created by Artur Vitor Cintra Bernardes && Felipe Pedrini Oliveira in 2025/1 at UFES.
*/

#ifndef LEITOR_H
#define LEITOR_H

#include "lista.h"
#include "livro.h"
#include "listaLivros.h"

typedef struct leitor tLeitor;

/**
 * @brief Cria e inicializa uma nova estrutura tLeitor.
 * Pre_condicao: nome e gostos não nulos.
 * Pos_condicao: Retorna um ponteiro para tLeitor alocado dinamicamente.
 * 
 * @param id Identificador do leitor.
 * @param nome Nome do leitor.
 * @param gostos Lista de gostos do leitor (tLista*).
 * @return Ponteiro para nova estrutura tLeitor.
 */
tLeitor* criaLeitor(int id, char* nome, tLista* gostos);

/**
 * @brief Retorna o ID de um leitor
 * Pre_condicao: Uma estrutura leitor, de preferência inicializada
 * Pos_condicao: Não altera a estrutura
 *
 * @param l  Estrutura tLeitor inicializada
 * @return ID do Leitor ou -999 caso ele não exista
 */
int retornaIdLeitor(tLeitor *l);

/**
 * @brief Retorna o nome do leitor.
 * Pre_condicao: Ponteiro para estrutura tLeitor inicializada.
 * Pos_condicao: Não altera a estrutura.
 * 
 * @param l Ponteiro para tLeitor.
 * @return Nome do leitor (char*).
 */
char *retornaNomeLeitor(tLeitor* l);

/**
 * @brief Imprime os dados do leitor no arquivo de saída fornecido.
 * Pre_condicao: Ponteiro para tLeitor inicializado e arquivo aberto para escrita.
 * Pos_condicao: Os dados do leitor são escritos no arquivo; nenhuma alteração na estrutura.
 * 
 * @param l Ponteiro para tLeitor.
 * @param saidas_f Ponteiro para arquivo de saída.
 */
void imprimeLeitor(tLeitor* l, FILE* saidas_f);

/**
 * @brief Retorna a lista de livros lidos por um leitor.
 * Pre_condicao: Leitor inicializado.
 * Pos_condicao: Não altera a estrutura.
 * 
 * @param l Ponteiro para tLeitor.
 * @return Ponteiro para lista de livros lidos.
 */
tListaLivro* retornaListaLidos(tLeitor* l);

/**
 * @brief Retorna a lista de livros recomendados para um leitor.
 * Pre_condicao: Leitor inicializado.
 * Pos_condicao: Não altera a estrutura.
 * 
 * @param l Ponteiro para tLeitor.
 * @return Ponteiro para lista de livros recomendados.
 */
tListaLivro* retornaListarecomendados(tLeitor* l);

/**
 * @brief Retorna a lista de livros desejados de um leitor.
 * Pre_condicao: Leitor inicializado.
 * Pos_condicao: Não altera a estrutura.
 * 
 * @param l Ponteiro para tLeitor.
 * @return Ponteiro para lista de livros desejados.
 */
tListaLivro* retornaListaDesejados(tLeitor* l);

/**
 * @brief Retorna a lista de gostos de um leitor.
 * Pre_condicao: Leitor inicializado.
 * Pos_condicao: Não altera a estrutura.
 * 
 * @param l Ponteiro para tLeitor.
 * @return Ponteiro para lista de gostos.
 */
tLista* retornaGostos(tLeitor* l);

/**
 * @brief Retorna a estrutura de afinidades de um leitor.
 * Pre_condicao: Leitor inicializado.
 * Pos_condicao: Não altera a estrutura.
 * 
 * @param l Ponteiro para tLeitor.
 * @return Ponteiro genérico para estrutura de afinidades.
 */
void* retornaAfinidades(tLeitor* l);

/**
 * @brief Adiciona um livro à lista de livros.
 * Pre_condicao: Ponteiros válidos para tLivro e tListaLivro.
 * Pos_condicao: Livro é adicionado à lista, se ainda não existir.
 * 
 * @param livro Ponteiro para tLivro.
 * @param lista Ponteiro para lista de livros.
 * @return 1 se foi adicionado, 0 caso contrário.
 */
int adicionaLivroLista(tLivro* livro, tListaLivro* lista);

/**
 * @brief Remove um livro da lista com base em sua chave.
 * Pre_condicao: Lista válida e chave correspondente existente.
 * Pos_condicao: Livro com chave igual a `key` (ID do livro) é removido da lista.
 * 
 * @param lista Ponteiro para lista de livros.
 * @param key Chave identificadora do livro a ser removido.
 */
void retiraLivroLista(tListaLivro* lista, int key);

/**
 * @brief Verifica se dois leitores possuem pelo menos um gosto em comum.
 * Pre_condicao: Ponteiros válidos para dois leitores inicializados.
 * Pos_condicao: Nenhuma alteração nas estruturas.
 * 
 * @param l1 Primeiro leitor.
 * @param l2 Segundo leitor.
 * @return 1 se existe gosto em comum, 0 caso contrário.
 */
int existeGostoEmComum(tLeitor* l1, tLeitor* l2);


/**
 * @brief Libera toda a memória alocada para um leitor.
 * Pre_condicao: Leitor foi criado com alocação dinâmica.
 * Pos_condicao: Toda a memória associada ao leitor é liberada.
 * 
 * @param leitor Ponteiro para o leitor a ser liberado.
 */
void liberaLeitor(void* leitor);

#endif