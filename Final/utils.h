/*
 Utils.h
 BookEd

 Created by Artur Vitor Cintra Bernardes && Felipe Pedrini Oliveira in 2025/1 at UFES.
*/

#ifndef UTILS_H
#define UTILS_H

#include "listaLivros.h"
#include "listaLeitores.h"
#include "leitor.h"
#include "lista.h"
#include "livro.h"
#include <stdio.h>

/**
 * @brief Adiciona livros a uma lista de livros
 * Pre_condicao: Arquivo livros.txt existir onde o programa estiver sendo executado.
 * Pos_condicao: Lista de livros contendo os livros necessários para a execução do programa.
 */
void leLivros(tListaLivro* lista);

/**
 * @brief Checa se tem espaço na memória.
 * Pre_condicao: Nenhuma.
 * Pos_condicao: Caso não tenha memória o programa é encerrado, se não continua normalmente.
 */
void checkMemory(void *p);

/**
 * @brief Adiciona leitores a uma lista de leitores
 * Pre_condicao: Arquivo leitores.txt existir onde o programa estiver sendo executado.
 * Pos_condicao: Lista de leitores contendo os leitores necessários para a execução do programa.
 */
void leLeitores(tListaLeitores* lista);

/**
 * @brief Inicializa o arquivo de comandos.
 * Pre_condicao: Arquivo comandos.txt existir onde o programa estiver sendo executado.
 * Pos_condicao: Arquivo comandos aberto e sua memória alocada.
 * @return Ponteiro para arquivo comandos retornado
 */
FILE *incializaComandos();

/**
 * @brief Lê os comandos
 * Pre_condicao: Arquivo comandos estar aberto.
 * Pos_condicao: Ponteiro dos parâmetros com seus devidos valores.
 * 
 * @param comandos Ponteiro para Arquivo.
 * @param funcionalidade Ponteiro para a funcionalidade que será executada no loop principal
 * @param id_1 Parâmetro 1.
 * @param id_2 Parâmetro 2.
 * @param id_3 Parâmetro 3.
 */
int leComando(FILE *comandos, int *funcionalidade, int *id_1, int *id_2, int *id_3);

/**
 * @brief Libera o arquivo de comandos.
 * Pre_condicao: Arquivo comandos estar aberto.
 * Pos_condicao: Arquivo comandos fechado e sua memória liberada.
 * 
 * @param comandos Ponteiro para Arquivo.
 */
void liberaComandos(FILE *comandos);

/**
 * @brief Roda o programa do BookED.
 * Pre_condicao: Memória suficiente para rodar o programa.
 * Pos_condicao: Programa rodado.
 */
void RunBookED();

#endif