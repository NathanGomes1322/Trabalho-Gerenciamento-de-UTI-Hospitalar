#include "funcionario.h"

// Inicializa a lista encadeada
void inicializar_lista(ListaFuncionarios *lista)
{
    lista->inicio = NULL;
    lista->fim = NULL;
}

// Aloca e cria um novo funcionário
Funcionario *criar_funcionario(const char *nome, int numero_doc, int acesso, const char *profissao)
{
    Funcionario *novo = (Funcionario *)malloc(sizeof(Funcionario));
    if (!novo)
        return NULL;

    strcpy(novo->nome, nome);
    novo->numero_doc = numero_doc;
    novo->acesso = acesso;
    strcpy(novo->profissao, profissao);
    novo->prox = NULL;

    return novo;
}

// Cadastro individual
void cadastrar_funcionario(ListaFuncionarios *lista)
{
    char nome[50], profissao[50];
    int numero_doc, acesso;

    printf("\n=== Cadastro de Funcionário ===\n");
    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Número do documento: ");
    scanf("%d", &numero_doc);
    getchar();

    printf("Nível de acesso (1 a 5): ");
    scanf("%d", &acesso);
    getchar();

    printf("Profissão: ");
    fgets(profissao, sizeof(profissao), stdin);
    profissao[strcspn(profissao, "\n")] = '\0';

    Funcionario *novo = criar_funcionario(nome, numero_doc, acesso, profissao);
    if (!novo)
    {
        printf("Erro ao alocar memória!\n");
        return;
    }

    if (!lista->inicio)
        lista->inicio = lista->fim = novo;
    else
    {
        lista->fim->prox = novo;
        lista->fim = novo;
    }

    printf("Funcionário cadastrado com sucesso!\n");
}

// Cadastro em lote
void equipe(ListaFuncionarios *lista)
{
    int qtd;
    printf("\nQuantos funcionários deseja cadastrar? ");
    scanf("%d", &qtd);
    getchar();

    for (int i = 0; i < qtd; i++)
    {
        printf("\n--- Funcionário %d ---\n", i + 1);
        cadastrar_funcionario(lista);
    }
}

// Listagem
void listar_funcionarios(const ListaFuncionarios *lista)
{
    if (!lista->inicio)
    {
        printf("\nNenhum funcionário cadastrado.\n");
        return;
    }

    printf("\n=== LISTA DE FUNCIONÁRIOS ===\n");
    Funcionario *atual = lista->inicio;
    while (atual)
    {
        printf("Nome: %s\n", atual->nome);
        printf("Documento: %d\n", atual->numero_doc);
        printf("Acesso: %d\n", atual->acesso);
        printf("Profissão: %s\n", atual->profissao);
        printf("-----------------------------\n");
        atual = atual->prox;
    }
}

// Salva no formato simples (4 linhas por funcionário)
int salvarFuncionariosEmArquivo(const ListaFuncionarios *lista)
{
    FILE *arq = fopen("funcionarios.txt", "w");
    if (!arq)
        return 0;

    Funcionario *atual = lista->inicio;
    while (atual)
    {
        fprintf(arq, "%s\n", atual->nome);
        fprintf(arq, "%d\n", atual->numero_doc);
        fprintf(arq, "%d\n", atual->acesso);
        fprintf(arq, "%s\n", atual->profissao);

        atual = atual->prox;
    }

    fclose(arq);
    return 1;
}

// Carrega do formato simples
int carregarFuncionarios(const char *nomeArquivo, ListaFuncionarios *lista)
{
    FILE *arq;
    arq = fopen(nomeArquivo, "r");
    if (!arq)
    {
        printf("Arquivo %s não encontrado.\n", nomeArquivo);
        return 0;
    }

    inicializar_lista(lista);

    char nome[50], profissao[50];
    int numero_doc, acesso, carregados = 0;

    while (fgets(nome, sizeof(nome), arq))
    {
        nome[strcspn(nome, "\n")] = '\0';

        if (fscanf(arq, "%d\n", &numero_doc) != 1)
            break;
        if (fscanf(arq, "%d\n", &acesso) != 1)
            break;

        fgets(profissao, sizeof(profissao), arq);
        profissao[strcspn(profissao, "\n")] = '\0';

        Funcionario *novo = criar_funcionario(nome, numero_doc, acesso, profissao);
        if (!novo)
            continue;

        if (!lista->inicio)
            lista->inicio = lista->fim = novo;
        else
        {
            lista->fim->prox = novo;
            lista->fim = novo;
        }

        carregados++;
    }

    fclose(arq);
    return carregados;
}

int carregarFuncionariosDeArquivo(ListaFuncionarios *lista)
{
    return carregarFuncionarios("funcionarios.txt", lista);
}

// Remove funcionário por nome OU documento
int remover_funcionario(ListaFuncionarios *lista, const char *nome, int numero_doc)
{
    Funcionario *atual = lista->inicio;
    Funcionario *anterior = NULL;

    while (atual)
    {
        if ((nome && strcmp(atual->nome, nome) == 0) ||
            (!nome && atual->numero_doc == numero_doc))
        {
            if (anterior == NULL)
                lista->inicio = atual->prox;
            else
                anterior->prox = atual->prox;

            if (atual == lista->fim)
                lista->fim = anterior;

            free(atual);
            return 1;
        }

        anterior = atual;
        atual = atual->prox;
    }

    return 0;
}
