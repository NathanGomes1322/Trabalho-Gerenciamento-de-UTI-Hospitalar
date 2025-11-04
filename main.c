#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"
#include "funcionario.h"
#include "fura_fila.h"
#include "abrir_arq.h"
#include "uti.h"
#include "lista_espera_uti.h"

int main(void)
{
    Fila filaPacientes;
    FilaHeap filaPrioridade;
    ListaFuncionarios lista;
    ListaEspera listaEspera;
    arquivo pacientes_arquivo[MAX_PACIENTES];
    int leitosUTI[MAX_UTI] = {0};
    int menu, total, i;

    inicializaFila(&filaPacientes);
    inicializar(&filaPrioridade);
    inicializar_lista(&lista);
    inicializarListaEspera(&listaEspera);

    total = carregarFuncionarios("funcionarios.txt", &lista);
    if (total == 0)
        printf("Nenhum funcionário carregado ou erro ao abrir arquivo.\n");
    else
        printf("%d funcionários carregados com sucesso.\n", total);

    total = carregararquivos("lista_pacientes.txt", pacientes_arquivo, MAX_PACIENTES);
    if (total == 0)
        printf("Nenhum paciente carregado do arquivo ou erro ao abrir.\n");
    else
    {
        for (i = 0; i < total; i++)
        {
            Paciente p;
            strcpy(p.nome, pacientes_arquivo[i].nome);
            strcpy(p.nascimento, pacientes_arquivo[i].nascimento);
            strcpy(p.cidade, pacientes_arquivo[i].cidade);
            strcpy(p.nome_mae, pacientes_arquivo[i].nome_mae);
            p.prioridade = pacientes_arquivo[i].prioridade;

            enfileira(&filaPacientes, p);
            adicionar_paciente(&filaPrioridade, p.nome, p.prioridade);
        }
        printf("%d pacientes carregados com sucesso.\n", total);
    }

    do
    {
        printf("\n#----------------------------------------#\n");
        printf("#     SELECIONE A OPÇÃO DESEJADA         #\n");
        printf("#----------------------------------------#\n");
        printf("# 1  - Cadastrar paciente no sistema     #\n");
        printf("# 2  - Listar pacientes                  #\n");
        printf("# 3  - Atender paciente prioritário      #\n");
        printf("# 4  - Internar paciente na UTI          #\n");
        printf("# 5  - Verificar disponibilidade UTI     #\n");
        printf("# 6  - Dar alta de paciente da UTI       #\n");
        printf("# 7  - Cadastrar funcionários (lista)    #\n");
        printf("# 8  - Cadastrar funcionário (individual)#\n");
        printf("# 9  - Listar funcionários               #\n");
        printf("# 10 - Remover funcionário               #\n");
        printf("# 11 - Listar lista de espera da UTI     #\n");
        printf("# 12 - Sair                              #\n");
        printf("#----------------------------------------#\n");
        printf("Digite a opção: ");

        if (scanf("%d", &menu) != 1)
        {
            printf("Entrada inválida! Digite um número.\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        getchar();

        switch (menu)
        {
        case 1:
        {
            Paciente novo;
            printf("Nome: ");
            fgets(novo.nome, sizeof(novo.nome), stdin);
            novo.nome[strcspn(novo.nome, "\n")] = '\0';

            printf("Nascimento: ");
            fgets(novo.nascimento, sizeof(novo.nascimento), stdin);
            novo.nascimento[strcspn(novo.nascimento, "\n")] = '\0';

            printf("Cidade: ");
            fgets(novo.cidade, sizeof(novo.cidade), stdin);
            novo.cidade[strcspn(novo.cidade, "\n")] = '\0';

            printf("Nome da mãe: ");
            fgets(novo.nome_mae, sizeof(novo.nome_mae), stdin);
            novo.nome_mae[strcspn(novo.nome_mae, "\n")] = '\0';

            printf("Prioridade (1 a 5): ");
            scanf("%d", &novo.prioridade);
            getchar();

            int indice = verificarDisponibilidadeUTI(leitosUTI, MAX_UTI);

            if (indice != -1)
            {
                leitosUTI[indice] = 1;
                printf("Paciente %s internado no leito %d.\n", novo.nome, indice);
            }
            else
            {
                printf("UTI lotada! Adicionado à lista de espera.\n");
                inserirListaEspera(&listaEspera, novo);
            }

            enfileira(&filaPacientes, novo);
            adicionar_paciente(&filaPrioridade, novo.nome, novo.prioridade);

            printf("Paciente cadastrado!\n");
            break;
        }

        case 2:
            listarFila(&filaPacientes);
            break;

        case 3:
            if (filaPrioridade.tamanho == 0)
                printf("Nenhum paciente na fila!\n");
            else
            {
                Paciente atendido = atender_paciente(&filaPrioridade);
                printf("Atendido: %s | Prioridade: %d\n", atendido.nome, atendido.prioridade);
            }
            break;

        case 4:
            cadastrarNaUTI(&filaPrioridade, leitosUTI, MAX_UTI);
            break;

        case 5:
        {
            int pos = verificarDisponibilidadeUTI(leitosUTI, MAX_UTI);
            if (pos != -1)
                printf("Leito disponível: %d\n", pos);
            else
                printf("Nenhum leito disponível.\n");
            break;
        }

        case 6:
            darAltaUTI(leitosUTI, MAX_UTI, &listaEspera);
            break;

        case 7:
            equipe(&lista);
            break;

        case 8:
            cadastrar_funcionario(&lista);
            break;

        case 9:
            listar_funcionarios(&lista);
            break;

        case 10:
        {
            int opc;
            printf("\nRemover por:\n1 - Nome\n2 - Documento\nEscolha: ");
            scanf("%d", &opc);
            getchar();

            if (opc == 1)
            {
                char nome[50];
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                if (remover_funcionario(&lista, nome, 0))
                    printf("Funcionário removido!\n");
                else
                    printf("Funcionário não encontrado.\n");
            }
            else if (opc == 2)
            {
                int doc;
                printf("Documento: ");
                scanf("%d", &doc);
                getchar();

                if (remover_funcionario(&lista, NULL, doc))
                    printf("Funcionário removido!\n");
                else
                    printf("Funcionário não encontrado.\n");
            }
            else
                printf("Opção inválida.\n");

            break;
        }

        case 11:
            listarListaEspera(&listaEspera);
            break;

        case 12:
            printf("Salvando dados e encerrando...\n");
            salvarPacientesEmArquivo(&filaPacientes);
            salvarFuncionariosEmArquivo(&lista);
            break;

        default:
            printf("Opção inválida!\n");
            break;
        }

    } while (menu != 12);

    return 0;
}
