/*
 TAD Lista_de_Livros.h
 BookEd

 Created by Artur Vitor Cintra Bernardes && Felipe Pedrini Oliveira in 2025/1 at UFES.
*/

#ifndef LISTA_LIVROS_H
#define LISTA_LIVROS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "livro.h"

typedef struct listaLivro tListaLivro;


/**
 * @brief Cria e inicializa uma nova lista de livros vazia.
 * Pre_condicao: Memória suficiente para alocar uma estrutura do tipo tListaLivro
 * Pos_condicao: Retorna ponteiro para lista de livros válida e vazia.
 * 
 * @return Ponteiro para estrutura tListaLivro recém-criada.
 */
tListaLivro* criaListaLivro();

/**
 * @brief Insere um livro na lista.
 * Pre_condicao: Ponteiros válidos para lista e livro.
 * Pos_condicao: O livro é adicionado à lista.
 * 
 * @param l Ponteiro para a lista de livros.
 * @param livro Ponteiro para o livro a ser inserido.
 */
void insereLivro(tListaLivro* l, tLivro* livro);

/**
 * @brief Remove um livro da lista com base na sua chave (ID).
 * Pre_condicao: Lista válida e chave existente na lista.
 * Pos_condicao: O livro é removido da lista.
 * 
 * @param l Ponteiro para a lista de livros.
 * @param key Chave identificadora do livro a ser removido.
 */
void retiraLivro(tListaLivro* l, int key);

/**
 * @brief Retorna o livro com a chave especificada na lista.
 * Pre_condicao: Lista válida.
 * Pos_condicao: Nenhuma alteração na lista.
 * 
 * @param l Ponteiro para a lista de livros.
 * @param key Identificador do livro.
 * @return Ponteiro para o livro, ou NULL se não encontrado.
 */
tLivro* retornaLivroLista(tListaLivro* l, int key);

/**
 * @brief Verifica se a lista de livros está vazia.
 * Pre_condicao: Lista de livros válida.
 * Pos_condicao: Nenhuma alteração na estrutura.
 * 
 * @param l Ponteiro para a lista.
 * @return 1 se vazia, 0 caso contrário.
 */
int listaVazia(tListaLivro* l);

/**
 * @brief Retorna uma nova lista contendo os livros em comum entre duas listas.
 * Pre_condicao: Ambas as listas devem ser válidas.
 * Pos_condicao: Uma nova lista com os livros em comum é criada.
 * 
 * @param orig Primeira lista de livros.
 * @param dest Segunda lista de livros.
 * @return Ponteiro para nova lista com livros em comum.
 */
tListaLivro* retornaLivrosEmComumListaLivro(tListaLivro* orig, tListaLivro* dest);

/**
 * @brief Imprime os livros da lista em um arquivo de saída.
 * Pre_condicao: Lista e arquivo de saída válidos.
 * Pos_condicao: Os livros são escritos no arquivo.
 * 
 * @param l Ponteiro para a lista de livros.
 * @param saidas_f Ponteiro para o arquivo de saída.
 */
void imprimeListaLivro(tListaLivro* l, FILE* saidas_f);

/**
 * @brief Libera a memória da lista e de seus nós, sem liberar os livros em si.
 * Pre_condicao: Lista válida.
 * Pos_condicao: Toda a estrutura da lista é liberada.
 * 
 * @param l Ponteiro para a lista de livros.
 */
void liberaListaLivro(tListaLivro* l);

/**
 * @brief Libera todos os livros da biblioteca representada pela lista.
 * Pre_condicao: Lista válida contendo livros.
 * Pos_condicao: Todos os livros e a lista são liberados da memória.
 * 
 * @param l Ponteiro para a lista de livros.
 */
void liberaBiblioteca(tListaLivro* l);

#endif