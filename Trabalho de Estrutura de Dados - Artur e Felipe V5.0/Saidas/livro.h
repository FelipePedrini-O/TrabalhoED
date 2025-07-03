/*
 TAD Livro.h
 BookEd

 Created by Artur Vitor Cintra Bernardes && Felipe Pedrini Oliveira in 2025/1 at UFES.
*/

#ifndef LIVRO_H
#define LIVRO_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct livro tLivro;

/**
 * @brief Aloca memória para uma estrutura tLivro.
 * Pre_condicao: Memória suficiente para alocar uma estrutura do tipo tLivro.
 * Pos_condicao: Memória alocada para tLivro.
 * 
 * @param titulo Titulo de um livro.
 * @param autor Autor de um livro.
 * @param genero Genero de um livro.
 * @param ano_publicacao Ano que um livro foi publicado.
 * @param id Identificador de um livro.
 * @return Ponteiro para o livro.
 */
tLivro* criaLivro(char* titulo, char* autor, char* genero, int ano_publicacao, int id);

/**
 * @brief Retorna o título de um livro
 * Pre_condicao: Ser um ponteiro válido para uma struct do tipo tLivro
 * Pos_condicao: Nenhuma alteração.
 * 
 * @param livro Ponteiro para um livro.
 * @return Titulo de um livro (Nome do livro).
 */
char* retornaNomeLivro(void* livro);

/**
 * @brief Retorna o Identificador (ID) de um livro
 * Pre_condicao: Ser um ponteiro válido para uma struct do tipo tLivro
 * Pos_condicao: Nenhuma alteração.
 * 
 * @param livro Ponteiro para um livro.
 * @return Identificador de um livro (ID).
 */
int retornaIdLivro(void *livro);

/**
 * @brief Libera um livro
 * Pre_condicao: Ser um ponteiro válido para uma struct do tipo tLivro
 * Pos_condicao: Memória do livro liberada e ponteiro para livro apontando para NULL.
 * 
 * @param livro Ponteiro para um livro.
 */
void liberaLivro(void* livro);

#endif