#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"


void inicializaFila(Fila *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaVazia(const Fila *f)
{
    return f->total == 0;
}

int filaCheia(const Fila *f)
{
    return f->total == MAX_PACIENTES;
}

/* Inserção FIFO (não ordena mais pela prioridade) */
int enfileira(Fila *f, Paciente p)
{
    if (filaCheia(f))
    {
        printf("Fila cheia!\n");
        return 0;
    }

    f->vet[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_PACIENTES;
    f->total++;
    return 1;
}

/* Remoção FIFO circular */
int desenfileira(Fila *f, Paciente *p)
{
    if (filaVazia(f))
    {
        printf("Fila vazia!\n");
        return 0;
    }

    *p = f->vet[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_PACIENTES;
    f->total--;

    return 1;
}

void listarFila(const Fila *f)
{
    if (filaVazia(f))
    {
        printf("\nNenhum paciente na fila!\n");
        return;
    }

    printf("\n#------ LISTA DE PACIENTES (FIFO) ------#\n");

    int i = f->inicio;
    for (int count = 0; count < f->total; count++)
    {
        Paciente p = f->vet[i];
        printf("Nome: %s\nNascimento: %s\nCidade: %s\nNome da mãe: %s\nPrioridade: %d\n\n",
               p.nome, p.nascimento, p.cidade, p.nome_mae, p.prioridade);

        i = (i + 1) % MAX_PACIENTES;
    }

    printf("#---------------------------------------#\n");
}

/* Agora só altera o valor, não reordena mais a fila */
void alterarPrioridade(Fila *f, const char *nome, int novaPrioridade)
{
    if (filaVazia(f))
    {
        printf("Fila vazia!\n");
        return;
    }

    int i = f->inicio;
    int encontrado = 0;

    for (int count = 0; count < f->total; count++)
    {
        if (strcmp(f->vet[i].nome, nome) == 0)
        {
            f->vet[i].prioridade = novaPrioridade;
            encontrado = 1;
            break;
        }
        i = (i + 1) % MAX_PACIENTES;
    }

    if (encontrado)
        printf("Prioridade do paciente %s alterada para %d.\n", nome, novaPrioridade);
    else
        printf("Paciente %s não encontrado na fila.\n", nome);
}

/* =======================================================
   ARQUIVOS
   ======================================================= */

void salvarPacientesEmArquivo(const Fila *fila)
{
    FILE *arq = fopen("pacientes.txt", "w");
    if (!arq)
    {
        printf("Erro ao abrir arquivo pacientes.txt para escrita.\n");
        return;
    }

    if (filaVazia(fila))
    {
        printf("Nenhum paciente para salvar.\n");
        fclose(arq);
        return;
    }

    int i = fila->inicio;
    for (int count = 0; count < fila->total; count++)
    {
        Paciente p = fila->vet[i];
        fprintf(arq, "Nome: %s\n", p.nome);
        fprintf(arq, "Nascimento: %s\n", p.nascimento);
        fprintf(arq, "Cidade: %s\n", p.cidade);
        fprintf(arq, "Nome da mãe: %s\n", p.nome_mae);
        fprintf(arq, "Prioridade: %d\n", p.prioridade);
        fprintf(arq, "-----------------------------\n");

        i = (i + 1) % MAX_PACIENTES;
    }

    fclose(arq);
    printf("Histórico de pacientes salvo em pacientes.txt\n");
}

int carregarPacientesDeArquivo(Fila *fila)
{
    FILE *arq = fopen("pacientes.txt", "r");
    if (!arq)
    {
        printf("Arquivo pacientes.txt não encontrado. Começando com fila vazia.\n");
        return 0;
    }

    inicializaFila(fila);

    char buffer[200];
    Paciente p;
    int lidos = 0;

    while (fgets(buffer, sizeof(buffer), arq))
    {
        if (strncmp(buffer, "Nome: ", 6) == 0)
            sscanf(buffer + 6, "%[^\n]", p.nome);

        else if (strncmp(buffer, "Nascimento: ", 12) == 0)
            sscanf(buffer + 12, "%[^\n]", p.nascimento);

        else if (strncmp(buffer, "Cidade: ", 8) == 0)
            sscanf(buffer + 8, "%[^\n]", p.cidade);

        else if (strncmp(buffer, "Nome da mãe: ", 13) == 0)
            sscanf(buffer + 13, "%[^\n]", p.nome_mae);

        else if (strncmp(buffer, "Prioridade: ", 12) == 0)
        {
            sscanf(buffer + 12, "%d", &p.prioridade);
            enfileira(fila, p);
            lidos++;
        }
    }

    fclose(arq);
    printf("%d pacientes carregados do arquivo.\n", lidos);
    return lidos;
}
