#ifndef LISTA_ESPERA_UTI_H
#define LISTA_ESPERA_UTI_H

#include "paciente.h"

typedef struct No
{
    Paciente dados;
    struct No *prox;
    struct No *ant;
} No;

typedef struct
{
    No *inicio;
    No *fim;
} ListaEspera;

void inicializarListaEspera(ListaEspera *lista);
void inserirListaEspera(ListaEspera *lista, Paciente novo);
void listarListaEspera(ListaEspera *lista);

#endif
