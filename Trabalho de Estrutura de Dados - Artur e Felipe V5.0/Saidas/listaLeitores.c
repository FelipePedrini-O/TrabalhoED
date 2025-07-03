/*
 TAD Lista_de_Leitores.c
 BookEd

 Created by Artur Vitor Cintra Bernardes && Felipe Pedrini Oliveira in 2025/1 at UFES.
*/

#include "listaLeitores.h"
#include "utils.h"


static int leitoresValidos(tLeitor *origem, tLeitor *destino);

// Node
typedef struct node
{
    tLeitor* leitor;
    struct node* prox;
    struct node* ant;
}
tNode;

static tNode *criaNode(tLeitor *leitor)
{
    tNode *n = malloc(sizeof(*n));
    checkMemory(n);

    n->leitor = leitor;
    n->prox = NULL;
    n->ant = NULL;
    return n;
}

static void imprimeNode(tNode *n, FILE* saidas_f)
{
    if(n->leitor)
        imprimeLeitor(n->leitor, saidas_f);
}

static void liberaNode(tNode *n)
{
    if(n)
    {
        liberaLeitor(n->leitor); // Alteracao feita para liberar o leitor dentro da lista
        free(n);
    }
}

// Lista Leitores
struct listaLeitores
{
    tNode* prim;
    tNode* ult;
};

tListaLeitores *criaListaLeitores()
{
    tListaLeitores *l = malloc(sizeof(*l));
    checkMemory(l);

    l->prim = NULL;
    l->ult = NULL;
    return l;
}

void insereListaLeitores(tListaLeitores *l, tLeitor *leitor)
{
    if(l)
    {
        tNode *n = criaNode(leitor);
    
        if(l->ult)
            l->ult->prox = n;
        n->ant = l->ult;
        n->prox = NULL;
        l->ult = n;
    
        if(!l->prim)
            l->prim = n;
    }
}

void retiraListaLeitores(tListaLeitores *l, int id)
{
    if(l)
    {
        tNode *temp = l->prim;
        while(temp)
        {
            if(id == retornaIdLeitor(temp->leitor))
            {
                if(temp->ant)
                    temp->ant->prox = temp->prox;
                if(temp->prox)
                    temp->prox->ant = temp->ant;
                if(temp->ant == NULL)
                    l->prim = temp->prox;
                if(temp->prox == NULL)
                    l->ult = temp->ant;
    
                liberaNode(temp);
                return;
            }
            temp = temp->prox;
        }
    }
}

tLeitor *retornaLeitorListaLeitores(tListaLeitores *l, int id)
{
    if(l)
    {
        tNode *temp = l->prim;
        while(temp)
        {
            if(id == retornaIdLeitor(temp->leitor))
                return temp->leitor;
            temp = temp->prox;
        }
    }

    return NULL;
}

 /*
    A obrigacao de encontrar e verificar o livro eh do cliente
    Retorna 0 em caso de erro na verificacao e 1 em caso de exito
 */
int recomendaLivroListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino, FILE* saidas_f)
{
    tLeitor *origem = retornaLeitorListaLeitores(l, id_origem);
    tLeitor *destino = retornaLeitorListaLeitores(l, id_destino);

    if (!leitoresValidos(origem, destino))
    {
        if(origem == destino)
            fprintf(saidas_f, "%s não pode recomendar livros para si mesmo\n", retornaNomeLeitor(origem));
        if(!origem)
            fprintf(saidas_f, "Erro: Leitor recomendador com ID %d não encontrado\n", id_origem);
        if(!destino)
            fprintf(saidas_f, "Erro: Leitor destinatário com ID %d não encontrado\n", id_destino);
        return 0;
    }

    // Verifica se o livro já foi recomendado antes
    tLivro *jaRecomendado = retornaLivroLista(retornaListarecomendados(destino), retornaIdLivro(livro));
    tLivro *jaDesejado = retornaLivroLista(retornaListaDesejados(destino), retornaIdLivro(livro));
    tLivro *jaLido = retornaLivroLista(retornaListaLidos(destino), retornaIdLivro(livro));
    if (jaRecomendado)
    {
        //printf("Recomendacao ignorada! Livro '%s' ja foi recomendado ao leitor com id %d\n", 
        //        retornaNomeLivro(livro), id_destino);
        return 0;
    }
    else if(jaDesejado)
    {
        fprintf(saidas_f,"%s já deseja ler \"%s\", recomendação desnecessária\n", retornaNomeLeitor(destino), retornaNomeLivro(livro));
        return 0;
    }
    else if (jaLido)
    {
        fprintf(saidas_f, "%s não precisa da recomendação de \"%s\" pois já leu este livro\n", retornaNomeLeitor(destino), retornaNomeLivro(livro));
        return 0;
    }
    fprintf(saidas_f, "%s recomenda \"%s\" para %s\n", retornaNomeLeitor(origem), retornaNomeLivro(livro), retornaNomeLeitor(destino));
    adicionaLivroLista(livro, retornaListarecomendados(destino));
    return 1;
}

 /*
    A obrigacao de encontrar e verificar o livro eh do cliente
    Retorna 0 em caso de erro na verificacao e 1 em caso de exito
 */
int aceitaRecomendacaoListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino, FILE* saidas_f)
{
    tLeitor *origem = retornaLeitorListaLeitores(l, id_origem);
    tLeitor *destino = retornaLeitorListaLeitores(l, id_destino);

    if (!leitoresValidos(origem, destino))
    {
        if(!retornaLivroLista(retornaListarecomendados(destino), retornaIdLivro(livro)) && origem == destino)
        {
            fprintf(saidas_f, "%s não possui recomendação do livro ID %d feita por %s\n", retornaNomeLeitor(destino), retornaIdLivro(livro), retornaNomeLeitor(origem));
            return 0;
        }
        if(origem == destino)
            fprintf(saidas_f, "%s não pode recomendar livros para si mesmo\n", retornaNomeLeitor(origem));
        if(!origem)
            fprintf(saidas_f, "Erro: Leitor recomendador com ID %d não encontrado\n", id_origem);
        if(!destino)
            fprintf(saidas_f, "Erro: Leitor com ID %d não encontrado\n", id_destino);
        return 0;
    }
    else if(!retornaLivroLista(retornaListarecomendados(destino), retornaIdLivro(livro)))
    {
        fprintf(saidas_f, "%s não possui recomendação do livro ID %d feita por %s\n", retornaNomeLeitor(destino), retornaIdLivro(livro), retornaNomeLeitor(origem));
        return 0;
    }

    retiraLivro(retornaListarecomendados(destino), retornaIdLivro(livro));

    // Verificacao da unicidade do livro na lista
    tListaLivro *desejados = retornaListaDesejados(destino);
    tLivro *livroNaLista = retornaLivroLista(desejados, retornaIdLivro(livro));
    if(!livroNaLista)
    {
        adicionaLivroLista(livro, desejados);
        fprintf(saidas_f, "%s aceita recomendação \"%s\" de %s\n", retornaNomeLeitor(destino), retornaNomeLivro(livro), retornaNomeLeitor(origem));
    }
    else
    {
        return 0;
    }
    return 1;
}

 /*
    A obrigacao de encontrar e verificar o livro eh do cliente
    Retorna 0 em caso de erro na verificacao e 1 em caso de exito
 */
int recusaRecomendacaoListaLeitores(tListaLeitores *l, tLivro *livro, int id_origem, int id_destino, FILE* saidas_f)
{
    tLeitor *origem = retornaLeitorListaLeitores(l, id_origem);
    tLeitor *destino = retornaLeitorListaLeitores(l, id_destino);

    if (!leitoresValidos(origem, destino))
    {
        if(origem == destino)
            fprintf(saidas_f, "%s não pode recomendar livros para si mesmo\n", retornaNomeLeitor(origem));
        if(!origem)
            fprintf(saidas_f, "Erro: Leitor recomendador com ID %d não encontrado\n", id_origem);
        if(!destino)
            fprintf(saidas_f, "Erro: Leitor com ID %d não encontrado\n", id_destino);
        return 0;
    }
    else if(!retornaLivroLista(retornaListarecomendados(destino), retornaIdLivro(livro)))
    {
        fprintf(saidas_f, "%s não possui recomendação do livro ID %d feita por %s\n", retornaNomeLeitor(destino), retornaIdLivro(livro), retornaNomeLeitor(origem));
        return 0;
    }

    retiraLivro(retornaListarecomendados(destino), retornaIdLivro(livro));
    fprintf(saidas_f, "%s rejeita recomendação \"%s\" de %s\n", retornaNomeLeitor(destino), retornaNomeLivro(livro), retornaNomeLeitor(origem));
    return 1;
}


int descobreLivrosComumListaLeitores(tListaLeitores *l, int id_origem, int id_destino, FILE* saidas_f){
    tLeitor *origem = retornaLeitorListaLeitores(l, id_origem);
    tLeitor *destino = retornaLeitorListaLeitores(l, id_destino);

    if (!leitoresValidos(origem, destino)){
        if(!origem)
            fprintf(saidas_f, "Erro: Leitor com ID %d não encontrado\n", id_origem);
        if(!destino)
            fprintf(saidas_f, "Erro: Leitor com ID %d não encontrado\n", id_destino);
        return 0;
    }

    tListaLivro* origemLidos = retornaListaLidos(origem);
    tListaLivro* destinoLidos = retornaListaLidos(destino);

    tListaLivro* livros_em_comum = retornaLivrosEmComumListaLivro(origemLidos, destinoLidos);
    
    fprintf(saidas_f, "Livros em comum entre %s e %s: ", retornaNomeLeitor(origem), retornaNomeLeitor(destino));
    if(!listaVazia(livros_em_comum)){
        imprimeListaLivro(livros_em_comum, saidas_f);
        fprintf(saidas_f, "\n");
    }else{
        fprintf(saidas_f, "Nenhum livro em comum\n");
    }

    liberaListaLivro(livros_em_comum);

    return 1;
}

void imprimeNomesListaLeitores(tListaLeitores* l, FILE* saidas_f){
    if(l)
    {
        tNode *temp = l->prim;
        if(temp == NULL)
            fprintf(saidas_f, "\n");
        while(temp)
        {
            if(temp->prox != NULL){
                fprintf(saidas_f, "%s, ", retornaNomeLeitor(temp->leitor));
            }else{
                fprintf(saidas_f, "%s\n", retornaNomeLeitor(temp->leitor));
            }
            temp = temp->prox;
        }
    }
}

// Funcao de uso unico e exclusivo para a liberacao das afinidades/afins
void liberaLeitoresDaListaAfinidadesLeitores(tListaLeitores *l)
{
    if(l)
    {
        tNode *temp = l->prim;
        while(temp)
        {
            tNode *aux = temp;
            temp = temp->prox;
            free(aux); 
        }
        free(l);
    }
}

static void insereAfinidadeEntreLeitores(tListaLeitores* l, tLeitor* target){
    if(l)
    {
        tNode* p  = l->prim;
    
        while(p != NULL){
            if(p->leitor != target && existeGostoEmComum(p->leitor, target)){
                // Só insere se ainda não estiver presente
                if (!retornaLeitorListaLeitores(retornaAfinidades(target), retornaIdLeitor(p->leitor))) {
                    insereListaLeitores(retornaAfinidades(target), p->leitor);
                }

            }
            p = p->prox;
        }
    }
}

void criaAfinidadesEntreLeitores(tListaLeitores* l){
    if(l)
    {
        tNode* aux = l->prim;
    
        while(aux != NULL){
            insereAfinidadeEntreLeitores(l, aux->leitor);
            aux = aux->prox;
        }
    }
}

/*
    Funcionamento: O algoritmo do Depth First Search funciona marcando os 'vértices', no nosso caso os leitores que já visitamos,
    e adentrando cada vez mais as afinidades dos leitores (de forma recursiva), parando caso chegue nos casos bases
    de encontrar o leitor que queriamos saber se tinhamos afinidade ou parando caso já tenhamos visitado esse leitor antes.

    O funcionamento é parecido com a busca em árvores, que buscamos na esquerda e depois na direita, entretando, como não possuí uma
    hierarquia é possível que ocorram ciclos(um elemento pode ser visitado mais de uma vez), 
    por isso sendo necessário a lista de visitados

    A recursão é usada pois queremos explorar profundamente cada caminho de afinidades antes de voltar e tentar o próximo.

------------------------------------------------------------- "" ------------------------------------------------------------------------
    Conclusão: Ao aplicar DFS, conseguimos verificar se existe um caminho de afinidades, direto ou indireto, entre dois leitores.
*/
static int dfs(tLeitor* atual, tLeitor* destino, tListaLeitores* visitados) {
    if(retornaIdLeitor(atual) == retornaIdLeitor(destino)){
        return 1; // Chegamos no destino (Encontramos o nosso leitor destino - Caso base)
    }

    if(retornaLeitorListaLeitores(visitados, retornaIdLeitor(atual))){
        return 0; // Já visitado (Já visitamos esse leitor - Evita ciclo infinito e também é um caso base)
    }

    insereListaLeitores(visitados, atual); // Marca como visitado

    tListaLeitores* afinidades = retornaAfinidades(atual);
    if (!afinidades) //Se afinidades for NULL retorna 0
        return 0;

    tNode* p = afinidades->prim;
    while(p != NULL){
        if(dfs(p->leitor, destino, visitados)){//Recursividade do algoritmo sendo aplicada
            return 1; // Caminho encontrado
        }
        p = p->prox;
    }

    return 0; // Nenhum caminho encontrado a partir deste leitor
}

int existeCaminhoAfinidade(tLeitor* origem, tLeitor* destino){
    if (!origem || !destino) return 0;

    tListaLeitores* visitados = criaListaLeitores();

    int achou = dfs(origem, destino, visitados);

    liberaLeitoresDaListaAfinidadesLeitores(visitados);

    return achou;
}

// int existeAfinidadeIndireta(tLeitor* origem, tLeitor* target){
//     //Verificar se algum gosto das afinidades da origem é em comum com o meu leitor de destino (target)
    
//     if(existeElementoEmComum(retornaAfinidades(origem), retornaAfinidades(target))){//Verifica o vizinho direto
//         return 1;
//     }

//     tListaLeitores* indiretas = retornaAfinidades(origem);

//     tNode* p = indiretas->prim;
//     while(p != NULL){//Verifica todos os casos para ver se algumas das afinidades da origem compartilha gosto em comum com target
//         tLista* gostosOrig = retornaGostos(p->leitor);
//         tLista* gostosTarget = retornaGostos(target);
//         if(existeElementoNaOutraLista(gostosOrig, gostosTarget, strcmp)){
//             return 1;
//         }
//         p = p->prox;
//     }

//     return 0;
// }
//Fim das Funcoes (2)

//F(3)
// int existeElementoEmComum(tListaLeitores* l1, tListaLeitores* l2){
//     if(l1 && l2)
//     {
//         tNode* aux = l1->prim;
    
//         while(aux != NULL){
//             tNode* p = l2->prim;
//             while(p != NULL){
//                 if(strcmp(retornaNomeLeitor(aux->leitor), retornaNomeLeitor(p->leitor)) == 0){//Compara os nomes
//                     return 1;
//                 }
//                 p = p->prox;
//             }
//             aux = aux->prox;
//         }
//     }

//     return 0;
// }
//Fim(3)

void imprimeListaLeitores(tListaLeitores *l, FILE* saidas_f)
{
    if(l)
    {
        tNode *temp = l->prim;
        while(temp)
        {
            imprimeLeitor(temp->leitor, saidas_f);
            temp = temp->prox;
        }
    }
}

void liberaListaLeitores(tListaLeitores *l)
{
    if(l)
    {
        tNode *temp = l->prim;
        while(temp)
        {
            tNode *aux = temp;
            temp = temp->prox;
            liberaNode(aux);
        }
        free(l);
    }
}

static int leitoresValidos(tLeitor *origem, tLeitor *destino)
{
    if (!origem)
    {
        return 0;
    }
    if (!destino)
    {
        return 0;
    }
    if(origem == destino) 
    {
        return 0;
    }
    return 1;
}