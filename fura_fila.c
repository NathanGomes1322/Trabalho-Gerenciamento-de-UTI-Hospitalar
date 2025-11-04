#include <stdio.h>
#include <string.h>
#include "fura_fila.h"

// Inicializa a fila
void inicializar(FilaHeap *fila)
{
    fila->tamanho = 0;
}

void adicionar_paciente(FilaHeap *fila, const char *nome, int prioridade)
{
    if (fila->tamanho >= MAX)
    {
        printf("Fila cheia!\n");
    }
    else
    {

        Paciente novo;
        strcpy(novo.nome, nome);
        novo.prioridade = prioridade;

        // Coloca o paciente no final do heap
        int i = fila->tamanho;
        fila->heap[i] = novo;
        fila->tamanho++;

        // Reorganiza o heap para manter o maior no topo
        while (i > 0)
        {
            int pai = (i - 1) / 2;
            int continuar = 1;

            if (fila->heap[pai].prioridade >= fila->heap[i].prioridade)
            {
                continuar = 0;
            }

            if (continuar)
            {
                /* Troca pai e filho */
                Paciente temp = fila->heap[pai];
                fila->heap[pai] = fila->heap[i];
                fila->heap[i] = temp;

                i = pai;
            }
            else
            {
                /* Força saída sem break */
                i = 0;
            }
        }
    }
}

// Atende o paciente mais crítico (maior prioridade)
Paciente atender_paciente(FilaHeap *fila)
{
    Paciente vazio = {"", "", "", "", -1};

    if (fila->tamanho == 0)
        return vazio;

    Paciente atendido = fila->heap[0];

    // Move o último elemento para o topo
    fila->heap[0] = fila->heap[fila->tamanho - 1];
    fila->tamanho--;

    // Refaz o Max-Heap
    int i = 0;
    while (1)
    {
        int maior = i;
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;

        if (esq < fila->tamanho && fila->heap[esq].prioridade > fila->heap[maior].prioridade)
            maior = esq;

        if (dir < fila->tamanho && fila->heap[dir].prioridade > fila->heap[maior].prioridade)
            maior = dir;

        if (maior == i)
            break;

        Paciente temp = fila->heap[i];
        fila->heap[i] = fila->heap[maior];
        fila->heap[maior] = temp;

        i = maior;
    }

    return atendido;
}

// Lista todos os pacientes na fila
void listar_fila(FilaHeap *fila)
{
    printf("\nFila de Prioridade (maior prioridade primeiro):\n");
    for (int i = 0; i < fila->tamanho; i++)
    {
        printf("Paciente: %s | Prioridade: %d\n", fila->heap[i].nome, fila->heap[i].prioridade);
    }
    printf("\n");
}
