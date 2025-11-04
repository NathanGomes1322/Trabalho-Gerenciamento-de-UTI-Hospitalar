#include <stdio.h>
#include <stdlib.h>
#include "lista_espera_uti.h"
#include "fura_fila.h"
#include "uti.h"

int verificarDisponibilidadeUTI(int uti[], int tamanho)
{
    int resultado;
    if (tamanho == 0)
        return -1;

    if (uti[0] == 0)
        return 0;

    resultado = verificarDisponibilidadeUTI(uti + 1, tamanho - 1);
    if (resultado != -1)
        return resultado + 1;

    return -1;
}

void cadastrarNaUTI(FilaHeap *filaPrioridade, int leitosUTI[], int tamanhoUTI)
{
    int leito, i;
    leito = -1;
    // Encontra o primeiro leito livre
    for (i = 0; i < tamanhoUTI; i++)
    {
        if (leitosUTI[i] == 0)
        {
            leito = i;
            break;
        }
    }

    // Caso base: se não há leitos disponíveis, parar
    if (leito == -1)
    {
        printf("\nTodos os leitos da UTI estão ocupados.\n");
        return;
    }

    // Retira paciente da fila de prioridade
    Paciente paciente = atender_paciente(filaPrioridade);

    // Caso base: se não há pacientes na fila, parar
    if (paciente.prioridade == -1)
    {
        printf("\nTodos os pacientes foram cadastrados na UTI.\n");
        return;
    }

    // Ocupa o leito
    leitosUTI[leito] = 1;

    // Exibe confirmação
    printf("\nPaciente internado na UTI!\n");
    printf("Nome: %s\n", paciente.nome);
    printf("Prioridade: %d\n", paciente.prioridade);
    printf("Leito: %d\n", leito);

    // Chama recursivamente para o próximo paciente
    cadastrarNaUTI(filaPrioridade, leitosUTI, tamanhoUTI);
}

void darAltaUTI(int leitos[], int tamanho, ListaEspera *lista)
{
    int leito;
    printf("Digite o número do leito para dar alta: ");
    scanf("%d", &leito);
    getchar();

    if (leito < 0 || leito >= tamanho || leitos[leito] == 0)
    {
        printf("Leito inválido ou já está vazio.\n");
        return;
    }

    leitos[leito] = 0;
    printf("Alta concedida para o leito %d.\n", leito);

    // Se houver paciente na lista de espera, interna o primeiro
    if (lista->inicio != NULL)
    {
        Paciente proximo = removerListaEspera(lista);
        leitos[leito] = 1;
        printf("Paciente %s (prioridade %d) foi internado no leito %d.\n",
               proximo.nome, proximo.prioridade, leito);
    }
    else
    {
        printf("Nenhum paciente aguardando na lista de espera.\n");
    }
}

