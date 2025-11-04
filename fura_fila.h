#ifndef FURA_FILA_H
#define FURA_FILA_H

#include "paciente.h"

#define MAX 100

typedef struct
{
    Paciente heap[MAX];
    int tamanho;
} FilaHeap;

void inicializar(FilaHeap *fila);
void adicionar_paciente(FilaHeap *fila, const char *nome, int prioridade);
Paciente atender_paciente(FilaHeap *fila);
void listar_fila(FilaHeap *fila);

#endif
