#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEICULOS 10
#define MAX_MARCA_MODELO 29

struct Veiculo
{
    char tipo[10];
    char marca[MAX_MARCA_MODELO + 1];
    char modelo[MAX_MARCA_MODELO + 1];
    int codigo;
};

void registrarVeiculo(struct Veiculo veiculos[], int *numVeiculos);
void gerarRelatorio(struct Veiculo veiculos[], int numVeiculos);
void atualizarVeiculo(struct Veiculo veiculos[], int numVeiculos);
void deletarVeiculo(struct Veiculo veiculos[], int *numVeiculos);

int main()
{
    struct Veiculo veiculos[MAX_VEICULOS];
    int numVeiculos = 0;
    int opcao;

    printf("----- Bem vindo -----\n");
    do
    {
        printf("\n--- Menu ---\n");
        printf("[1] Registrar Veiculo\n");
        printf("[2] Gerar Relatorio\n");
        printf("[3] Atualizar Veiculo\n");
        printf("[4] Deletar Veiculo\n");
        printf("[5] Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            printf("Erro na leitura da opcao. Saindo do programa...\n");
            return 1;
        }

        switch (opcao)
        {
        case 1:
            registrarVeiculo(veiculos, &numVeiculos);
            break;
        case 2:
            if (numVeiculos == 0)
            {
                printf("Nenhum veiculo registrado. Registre um veiculo antes de gerar o relatorio.\n");
            }
            else
            {
                gerarRelatorio(veiculos, numVeiculos);
            }
            break;
        case 3:
            if (numVeiculos == 0)
            {
                printf("Nenhum veiculo registrado. Registre um veiculo antes de atualiza-lo.\n");
            }
            else
            {
                atualizarVeiculo(veiculos, numVeiculos);
            }
            break;
        case 4:
            if (numVeiculos == 0)
            {
                printf("Nenhum veiculo registrado. Registre um veiculo antes de deleta-lo.\n");
            }
            else
            {
                deletarVeiculo(veiculos, &numVeiculos);
            }
            break;
        case 5:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}

void registrarVeiculo(struct Veiculo veiculos[], int *numVeiculos)
{
    if (*numVeiculos >= MAX_VEICULOS)
    {
        printf("Limite maximo de veiculos atingido!\n");
        return;
    }

    printf("\nRegistro de Veiculo:\n");

    int tipo;
    do
    {
        printf("--- Tipo de Veiculo ---\n[1] Carro\n[2] Moto\n[3] Caminhao\nQual opcao voce deseja: ");
        if (scanf("%d", &tipo) != 1)
        {
            printf("Erro na leitura do tipo de veiculo. Tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }
        if (tipo < 1 || tipo > 3)
        {
            printf("Opcao invalida! Escolha 1, 2 ou 3.\n");
        }
    } while (tipo < 1 || tipo > 3);

    strcpy(veiculos[*numVeiculos].tipo, (tipo == 1) ? "Carro" : (tipo == 2) ? "Moto" : "Caminhao");

    printf("Marca: ");
    scanf("%29s", veiculos[*numVeiculos].marca);
    printf("Modelo: ");
    scanf("%29s", veiculos[*numVeiculos].modelo);
    printf("Codigo: ");
    scanf("%d", &veiculos[*numVeiculos].codigo);

    (*numVeiculos)++;
    printf("Veiculo registrado com sucesso!\n");
}

void gerarRelatorio(struct Veiculo veiculos[], int numVeiculos)
{
    FILE *arquivo;
    arquivo = fopen("relatorio.txt", "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo! Verifique as permissoes.\n");
        return;
    }

    fprintf(arquivo, "----- Relatorio de Veiculos -----\n\n");
    for (int i = 0; i < numVeiculos; i++)
    {
        fprintf(arquivo, "Veiculo %d:\n", i + 1);
        fprintf(arquivo, "  Tipo: %s\n", veiculos[i].tipo);
        fprintf(arquivo, "  Marca: %s\n", veiculos[i].marca);
        fprintf(arquivo, "  Modelo: %s\n", veiculos[i].modelo);
        fprintf(arquivo, "  Codigo: %d\n\n", veiculos[i].codigo);
    }

    fclose(arquivo);
    printf("Relatorio gerado com sucesso em 'relatorio.txt'!\n");
}

void atualizarVeiculo(struct Veiculo veiculos[], int numVeiculos)
{
    int codigo, encontrado = 0;
    printf("Digite o codigo do veiculo que deseja atualizar: ");
    if (scanf("%d", &codigo) != 1)
    {
        printf("Erro na leitura do codigo. Tente novamente.\n");
        while (getchar() != '\n');
        return;
    }

    for (int i = 0; i < numVeiculos; i++)
    {
        if (veiculos[i].codigo == codigo)
        {
            printf("Atualizando veiculo %d:\n", codigo);

            int tipo;
            do
            {
                printf("--- Tipo de Veiculo ---\n[1] Carro\n[2] Moto\n[3] Caminhao\nQual opcao voce deseja: ");
                if (scanf("%d", &tipo) != 1)
                {
                    printf("Erro na leitura do tipo de veiculo. Tente novamente.\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (tipo < 1 || tipo > 3)
                {
                    printf("Opcao invalida! Escolha 1, 2 ou 3.\n");
                }
            } while (tipo < 1 || tipo > 3);

            strcpy(veiculos[i].tipo, (tipo == 1) ? "Carro" : (tipo == 2) ? "Moto" : "Caminhao");

            printf("Marca: ");
            scanf("%29s", veiculos[i].marca);
            printf("Modelo: ");
            scanf("%29s", veiculos[i].modelo);
            printf("Codigo: ");
            scanf("%d", &veiculos[i].codigo);

            printf("Veiculo atualizado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Veiculo com codigo %d nao encontrado.\n", codigo);
    }
}

void deletarVeiculo(struct Veiculo veiculos[], int *numVeiculos)
{
    int codigo, encontrado = 0;
    printf("Digite o codigo do veiculo que deseja deletar: ");
    if (scanf("%d", &codigo) != 1)
    {
        printf("Erro na leitura do codigo. Tente novamente.\n");
        while (getchar() != '\n');
        return;
    }

    for (int i = 0; i < *numVeiculos; i++)
    {
        if (veiculos[i].codigo == codigo)
        {
            for (int j = i; j < *numVeiculos - 1; j++)
            {
                veiculos[j] = veiculos[j + 1];
            }
            (*numVeiculos)--;
            printf("Veiculo deletado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Veiculo com codigo %d nao encontrado.\n", codigo);
    }
}