#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct funcionario
{
    char nome[50];
    int numero_doc;
    int acesso;
    char profissao[50];
    struct funcionario *prox;
} Funcionario;

typedef struct
{
    Funcionario *inicio;
    Funcionario *fim;
} ListaFuncionarios;

// Inicialização
void inicializar_lista(ListaFuncionarios *lista);

// Criação e cadastro
Funcionario *criar_funcionario(const char *nome, int numero_doc, int acesso, const char *profissao);
void cadastrar_funcionario(ListaFuncionarios *lista);
void equipe(ListaFuncionarios *lista);

// Listagem
void listar_funcionarios(const ListaFuncionarios *lista);

// Remoção
int remover_funcionario(ListaFuncionarios *lista, const char *nome, int numero_doc);

// Arquivos
int salvarFuncionariosEmArquivo(const ListaFuncionarios *lista);
int carregarFuncionarios(const char *nomeArquivo, ListaFuncionarios *lista);
int carregarFuncionariosDeArquivo(ListaFuncionarios *lista);

#endif
