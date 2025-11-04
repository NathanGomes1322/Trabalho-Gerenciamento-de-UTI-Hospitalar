#ifndef PACIENTE_H
#define PACIENTE_H

#define MAX_PACIENTES 100

typedef struct
{
    char nome[100];
    char nascimento[20];
    char cidade[50];
    char nome_mae[100];
    int prioridade;
} Paciente;

typedef struct
{
    Paciente vet[MAX_PACIENTES];
    int inicio, fim, total;
} Fila;

void inicializaFila(Fila *f);
int filaVazia(const Fila *f);
int filaCheia(const Fila *f);
int enfileira(Fila *f, Paciente p);
int desenfileira(Fila *f, Paciente *p);
void listarFila(const Fila *f);
void alterarPrioridade(Fila *f, const char *nome, int novaPrioridade);
void salvarPacientesEmArquivo(const Fila *fila);
int carregarPacientesDeArquivo(Fila *fila);

#endif
