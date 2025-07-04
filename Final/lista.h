/*
 TAD Lista.h
 BookEd

 Created by Artur Vitor Cintra Bernardes && Felipe Pedrini Oliveira in 2025/1 at UFES.
*/

#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista tLista;

/*
    Ponteiros de funções
*/
typedef void (*libera)(void*);
typedef void (*imprime)(void*);
typedef int (*compara_fptr)(const char*, const char*);

/**
 * @brief Cria e inicializa uma nova lista vazia.
 * Pre_condicao: Memória suficiente para alocar uma estrutura do tipo tLista
 * Pos_condicao: Retorna ponteiro para uma lista válida e vazia.
 * 
 * @return Ponteiro para estrutura tLista recém-criada.
 */
tLista* criaLista();

/**
 * @brief Insere um item no início da lista.
 * Pre_condicao: Ponteiro para tLista válido; ponteiro de função `libera_item` deve ser fornecido para liberação posterior.
 * Pos_condicao: O item é inserido na primeira posição da lista.
 * 
 * @param l Ponteiro para a lista.
 * @param item Ponteiro para o item a ser inserido.
 * @param libera_item Função de liberação para o item.
 */
void insereListaInicio(tLista* l, void* item, libera libera_item);

/**
 * @brief Insere um item no final da lista.
 * Pre_condicao: Lista válida, `libera_item` e `imprime_item` devem ser funções válidas para o tipo armazenado.
 * Pos_condicao: O item é adicionado ao final da lista.
 * 
 * @param l Ponteiro para a lista.
 * @param item Ponteiro para o item a ser inserido.
 * @param libera_item Função usada para liberar o item.
 * @param imprime_item Função usada para imprimir o item.
 */
void insereListaFinal(tLista* l, void* item, libera libera_item, imprime imprime_item);

/**
 * @brief Remove da lista o item que possui a chave especificada.
 * Pre_condicao: Lista válida e chave correspondente existente.
 * Pos_condicao: Item com chave igual a `key` é removido da lista, se existir.
 * 
 * @param l Ponteiro para lista.
 * @param key Identificador do item a ser removido.
 */
void retiraLista(tLista* l, int key);

/**
 * @brief Verifica se há pelo menos um elemento de uma lista presente na outra.
 * Pre_condicao: Listas válidas e função `compara` adequada para comparar elementos.
 * Pos_condicao: Nenhuma alteração nas listas.
 * 
 * @param l1 Primeira lista.
 * @param l2 Segunda lista.
 * @param compara Função de comparação que retorna 1 se os elementos forem considerados iguais.
 * @return 1 se existir pelo menos um elemento em comum, 0 caso contrário.
 */
int existeElementoNaOutraLista(tLista* l1, tLista* l2, compara_fptr compara);

/**
 * @brief Imprime todos os elementos da lista.
 * Pre_condicao: Lista válida com ponteiros de função de impressão corretamente definidos nos nós.
 * Pos_condicao: Os elementos da lista são enviados para a saída padrão ou arquivo, conforme a função `imprime`.
 * 
 * @param l Ponteiro para lista.
 */
void imprimeLista(tLista* l);

/**
 * @brief Libera toda a memória alocada para a lista e seus elementos.
 * Pre_condicao: Lista válida e funções de liberação previamente definidas nos nós.
 * Pos_condicao: Todos os elementos da lista e a própria estrutura são liberados da memória.
 * 
 * @param l Ponteiro para lista a ser liberada.
 */
void liberaLista(tLista* l);

#endif