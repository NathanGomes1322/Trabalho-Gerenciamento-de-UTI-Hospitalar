#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* Necessário para atoi() */
#include "abrir_arq.h"

int carregararquivos(const char *nomeArquivo, arquivo arquivos[], int max)
{
    FILE *arq = fopen(nomeArquivo, "r");
    int i = 0;
    char buffer[200];
    int leitura_ok = 1;

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return 0;
    }

    while (i < max && leitura_ok)
    {
        /* Nome */
        if (fgets(arquivos[i].nome, MAX_NOME, arq) == NULL)
        {
            leitura_ok = 0;
        }
        else
        {
            arquivos[i].nome[strcspn(arquivos[i].nome, "\r\n")] = '\0';

            /* Nascimento */
            if (fgets(arquivos[i].nascimento, MAX_NASCIMENTO, arq) == NULL)
            {
                leitura_ok = 0;
            }
            else
            {
                arquivos[i].nascimento[strcspn(arquivos[i].nascimento, "\r\n")] = '\0';

                /* Cidade */
                if (fgets(arquivos[i].cidade, MAX_CIDADE, arq) == NULL)
                {
                    leitura_ok = 0;
                }
                else
                {
                    arquivos[i].cidade[strcspn(arquivos[i].cidade, "\r\n")] = '\0';

                    /* Nome da mãe */
                    if (fgets(arquivos[i].nome_mae, MAX_NOME_MAE, arq) == NULL)
                    {
                        leitura_ok = 0;
                    }
                    else
                    {
                        arquivos[i].nome_mae[strcspn(arquivos[i].nome_mae, "\r\n")] = '\0';

                        /* Caso clínico */
                        if (fgets(buffer, sizeof(buffer), arq) == NULL)
                        {
                            leitura_ok = 0;
                        }
                        else
                        {
                            arquivos[i].caso_clinico = atoi(buffer);

                            /* Prioridade */
                            if (fgets(buffer, sizeof(buffer), arq) == NULL)
                            {
                                leitura_ok = 0;
                            }
                            else
                            {
                                arquivos[i].prioridade = atoi(buffer);

                                /* Apenas agora incrementa */
                                i++;
                            }
                        }
                    }
                }
            }
        }
    }

    fclose(arq);
    return i;
}

void imprimirarquivos(arquivo arquivos[], int total)
{
    int i;

    printf("#------ LISTA DE PACIENTES ------#\n");

    for (i = 0; i < total; i++)
    {
        printf("\nNome: %s\n", arquivos[i].nome);
        printf("Nascimento: %s\n", arquivos[i].nascimento);
        printf("Cidade: %s\n", arquivos[i].cidade);
        printf("Nome da mãe: %s\n", arquivos[i].nome_mae);
        printf("Caso clínico: %d\n", arquivos[i].caso_clinico);
        printf("Prioridade: %d\n", arquivos[i].prioridade);
    }
}
