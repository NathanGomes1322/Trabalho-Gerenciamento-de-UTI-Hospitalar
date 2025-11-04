#ifndef ABRIR_ARQ_H
#define ABRIR_ARQ_H

#define MAX_NOME 100
#define MAX_NASCIMENTO 20
#define MAX_CIDADE 50
#define MAX_NOME_MAE 100

typedef struct
{
    char nome[MAX_NOME];
    char nascimento[MAX_NASCIMENTO];
    char cidade[MAX_CIDADE];
    char nome_mae[MAX_NOME_MAE];
    int caso_clinico;
    int prioridade;
} arquivo;

int carregararquivos(const char *nomeArquivo, arquivo arquivos[], int max);
void imprimirarquivos(arquivo arquivos[], int total);

#endif
