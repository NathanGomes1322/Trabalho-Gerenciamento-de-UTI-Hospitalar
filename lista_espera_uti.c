#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_espera_uti.h"

void inicializarListaEspera(ListaEspera *lista)
{
    lista->inicio = NULL;
    lista->fim = NULL;
}

void inserirListaEspera(ListaEspera *lista, Paciente novo)
{
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->prox = NULL;
    novoNo->ant = NULL;

    if (lista->inicio == NULL)
    {
        lista->inicio = lista->fim = novoNo;
        return;/*não usar vazio - void não retorna nada*/
    }

    No *atual = lista->inicio;
    while (atual != NULL && atual->dados.prioridade >= novo.prioridade)
    {
        atual = atual->prox;
    }

    if (atual == lista->inicio)
    {
        novoNo->prox = lista->inicio;
        lista->inicio->ant = novoNo;
        lista->inicio = novoNo;
    }
    else if (atual == NULL)
    {
        novoNo->ant = lista->fim;
        lista->fim->prox = novoNo;
        lista->fim = novoNo;
    }
    else
    {
        novoNo->prox = atual;
        novoNo->ant = atual->ant;
        atual->ant->prox = novoNo;
        atual->ant = novoNo;
    }
}

void listarListaEspera(ListaEspera *lista)
{
    No *aux = lista->inicio;
    if (aux == NULL)
    {
        printf("Nenhum paciente na lista de espera.\n");
        return;
    }

    printf("\n--- LISTA DE ESPERA UTI ---\n");
    while (aux != NULL)
    {
        printf("Nome: %s | Prioridade: %d\n", aux->dados.nome, aux->dados.prioridade);
        aux = aux->prox;
    }
}

Paciente removerListaEspera(ListaEspera *lista)
{
    Paciente vazio = {"", "", "", "", -1};

    if (lista->inicio == NULL)
    {
        printf("Lista de espera vazia.\n");
        return vazio;
    }

    // Remove o primeiro (mais prioritário)
    No *remover = lista->inicio;
    Paciente pacienteRemovido = remover->dados;

    lista->inicio = remover->prox;
    if (lista->inicio != NULL)
        lista->inicio->ant = NULL;
    else
        lista->fim = NULL;

    free(remover);
    return pacienteRemovido;
}

