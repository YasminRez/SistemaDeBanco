#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define SENHA_PADRAO "money"
#define MAX_CONTAS 10 // Máximo de contas

void clean_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

// Estrutura para representar uma conta bancária
typedef struct
{
    int numero_conta;
    char nome_titular[50];
    double saldo;
} ContaBancaria;

ContaBancaria **contas;

// Função para criar uma nova conta bancária
ContaBancaria *criarConta()
{
    // Alocar memória para a estrutura da conta
    ContaBancaria *nova_conta = (ContaBancaria *)malloc(sizeof(ContaBancaria));

    // Verificar se a alocação foi bem-sucedida
    if (nova_conta == NULL)
    {
        fprintf(stderr, "Erro ao alocar memoria para a conta bancaria\n");
        exit(EXIT_FAILURE);
    }

    // Solicitar informações ao usuário
    printf("Digite o numero da conta: ");
    scanf("%d", &nova_conta->numero_conta);

    printf("Digite o nome do titular: ");
    clean_stdin();
    fgets(nova_conta->nome_titular, 50, stdin);
    nova_conta->nome_titular[strcspn(nova_conta->nome_titular, "\n")] = 0;

    printf("Digite o saldo inicial: R$ ");
    scanf("%lf", &nova_conta->saldo);

    // Retornar o ponteiro para a nova conta
    return nova_conta;
}

// Função para depositar em uma conta
void depositar()
{
    int numeroConta;
    double valor;

    printf("Digite o numero da conta para deposito: ");
    scanf("%d", &numeroConta);

    // Procurar a conta pelo número
    int i;
    for (i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        if (contas[i]->numero_conta == numeroConta)
        {
            printf("Digite o valor a ser depositado: R$ ");
            scanf("%lf", &valor);

            // Validar o valor do depósito
            if (valor > 0)
            {
                contas[i]->saldo += valor;
                printf("\n");
                printf("----------------------------\n");
                printf("Deposito realizado com sucesso!\n");
                printf("----------------------------\n");
                printf("\n");
            }
            else
            {
                printf("\n");
                printf("----------------------------\n");
                printf("Valor de deposito invalido. O valor deve ser maior que zero.\n");
                printf("----------------------------\n");
                printf("\n");
            }

            return; // Sair da função depois de realizar o depósito
        }
    }

    // Se a conta não for encontrada
    printf("\n");
    printf("----------------------------\n");
    printf("Conta nao encontrada. Verifique o numero da conta e tente novamente.\n");
    printf("----------------------------\n");
    printf("\n");
}

// Função para sacar de uma conta
void sacar()
{
    int numeroConta;
    double valor;

    printf("Digite o numero da conta para saque: ");
    scanf("%d", &numeroConta);

    // Procurar a conta pelo número
    int i;
    for (i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        if (contas[i]->numero_conta == numeroConta)
        {
            printf("Digite o valor a ser sacado: R$ ");
            scanf("%lf", &valor);

            // Validar o valor do saque
            if (valor > 0 && valor <= contas[i]->saldo)
            {
                contas[i]->saldo -= valor;
                printf("\n");
                printf("----------------------------\n");
                printf("Saque realizado com sucesso!\n");
                printf("----------------------------\n");
                printf("\n");
            }
            else if (valor <= 0)
            {
                printf("\n");
                printf("----------------------------\n");
                printf("Valor de saque invalido. O valor deve ser maior que zero.\n");
                printf("----------------------------\n");
                printf("\n");
            }
            else
            {
                printf("\n");
                printf("----------------------------\n");
                printf("Saldo insuficiente para realizar o saque.\n");
                printf("----------------------------\n");
                printf("\n");
            }

            return; // Sair da função depois de realizar o saque
        }
    }

    // Se a conta não for encontrada
    printf("\n");
    printf("----------------------------\n");
    printf("Conta nao encontrada. Verifique o numero da conta e tente novamente.\n");
    printf("----------------------------\n");
    printf("\n");
}

// Função para exibir um menu de operações em uma conta (depósito ou saque)
void depositarSacar()

{
    int escolha;
    while (escolha != 3)
    {

        printf("\n------------ MENU DE OPERACOES EM CONTA ------------\n");
        printf("1 - Deposito\n");
        printf("2 - Saque\n");
        printf("3 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            depositar();
            break;
        case 2:
            sacar();
            break;
        default:
            printf("Opcao invalida.\n");
        }
    }
}

// No seu switch-case, você pode chamar essa função quando o usuário escolher a opção 3

void mostrarSaldoTotal()
{
    double saldoTotal = 0.0;

    // Iterar sobre todas as contas e somar os saldos
    printf("\n------------ LISTA DE CONTAS ------------\n");
    for (int i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        printf("Conta: %d\n", contas[i]->numero_conta);
        printf("Titular: %s\n", contas[i]->nome_titular);
        printf("Saldo: R$%.2lf\n", contas[i]->saldo);
        printf("-----------------------------\n");
    }
    for (int i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        saldoTotal += contas[i]->saldo;
    }

    // Exibir o saldo total
    printf("Saldo total de todas as contas: R$ %.2lf\n", saldoTotal);
}

// Função para editar informações do titular de uma conta
void editarInformacoes(ContaBancaria *conta)
{
    // Solicitar novas informações ao usuário
    printf("Digite o novo nome do titular: ");
    clean_stdin();
    fgets(conta->nome_titular, 50, stdin);
    conta->nome_titular[strcspn(conta->nome_titular, "\n")] = 0;

    printf("Digite o novo saldo: R$ ");
    scanf("%lf", &conta->saldo);

    printf("\n");
    printf("----------------------------\n");
    printf("Informacoes da conta atualizadas com sucesso!\n");
    printf("----------------------------\n");
    printf("\n");
}

// Função para encontrar uma conta pelo número
ContaBancaria *encontrarConta(int numeroConta)
{
    for (int i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        if (contas[i]->numero_conta == numeroConta)
        {
            return contas[i];
        }
    }
    return NULL; // Retorna NULL se a conta não for encontrada
}

// Função para remover uma conta bancária
void removerConta(int numeroConta)
{
    // Encontrar a conta pelo número
    ContaBancaria *contaParaRemover = encontrarConta(numeroConta);

    if (contaParaRemover != NULL)
    {
        // Exibir informações da conta antes de remover
        printf("\n------------ INFORMACOES DA CONTA ------------\n");
        printf("Conta: %d\n", contaParaRemover->numero_conta);
        printf("Titular: %s\n", contaParaRemover->nome_titular);
        printf("Saldo: R$%.2lf\n", contaParaRemover->saldo);
        printf("----------------------------------------------\n");

        int confirmacao;
        printf("Tem certeza que deseja remover esta conta?\n");
        printf("1 - Sim\n");
        printf("2 - Nao\n");
        printf("Escolha: ");
        scanf("%d", &confirmacao);

        if (confirmacao == 1)
        {
            // Encontrar a posição da conta no array
            int posicaoRemover = -1;
            for (int i = 0; i < MAX_CONTAS; i++)
            {
                if (contas[i] == contaParaRemover)
                {
                    posicaoRemover = i;
                    break;
                }
            }

            if (posicaoRemover != -1)
            {
                // Remover a conta (liberar memória)
                free(contaParaRemover);

                // Deslocar as contas restantes para preencher o espaço vazio
                for (int j = posicaoRemover; j < MAX_CONTAS - 1; j++)
                {
                    contas[j] = contas[j + 1];
                }

                // Última posição do array deve ser nula
                contas[MAX_CONTAS - 1] = NULL;

                // Realocar o array para liberar espaço
                ContaBancaria **temp = (ContaBancaria **)realloc(contas, MAX_CONTAS * sizeof(ContaBancaria *));
                if (temp == NULL)
                {
                    fprintf(stderr, "Erro ao realocar memoria para o vetor de contas\n");
                    exit(EXIT_FAILURE);
                }

                contas = temp;

                printf("\n----------------------------\n");
                printf("Conta removida com sucesso!\n");
                printf("----------------------------\n");
                return;
            }
        }
        else if (confirmacao == 2)
        {
            printf("\n----------------------------\n");
            printf("Remocao cancelada pelo usuario.\n");
            printf("----------------------------\n");
        }
        else
        {
            printf("\n----------------------------\n");
            printf("Opcao invalida. Remocao cancelada.\n");
            printf("----------------------------\n");
        }
    }
    else
    {
        printf("\n----------------------------\n");
        printf("Conta nao encontrada. Verifique o numero da conta e tente novamente.\n");
        printf("----------------------------\n");
    }
}

// função para transferir valor
void transferirValor()
{
    int origemConta, destinoConta;
    double valor;

    printf("Digite o numero da conta de origem: ");
    scanf("%d", &origemConta);

    // Encontrar a conta de origem pelo número
    ContaBancaria *contaOrigem = encontrarConta(origemConta);

    if (contaOrigem == NULL)
    {
        printf("\n----------------------------\n");
        printf("Conta de origem nao encontrada. Verifique o numero da conta e tente novamente.\n");
        printf("----------------------------\n\n");
        return;
    }

    printf("Digite o numero da conta de destino: ");
    scanf("%d", &destinoConta);

    // Encontrar a conta de destino pelo número
    ContaBancaria *contaDestino = encontrarConta(destinoConta);

    if (contaDestino == NULL)
    {
        printf("\n----------------------------\n");
        printf("Conta de destino nao encontrada. Verifique o numero da conta e tente novamente.\n");
        printf("----------------------------\n\n");
        return;
    }

    printf("Digite o valor a ser transferido: R$");
    scanf("%lf", &valor);

    // Verificar se o saldo é suficiente para a transferência
    if (valor > 0 && valor <= contaOrigem->saldo)
    {
        contaOrigem->saldo -= valor;
        contaDestino->saldo += valor;

        printf("\n----------------------------\n");
        printf("Transferencia realizada com sucesso!\n");
        printf("----------------------------\n\n");
    }
    else if (valor <= 0)
    {
        printf("\n----------------------------\n");
        printf("Valor de transferencia invalido. O valor deve ser maior que zero.\n");
        printf("----------------------------\n\n");
    }
    else
    {
        printf("\n----------------------------\n");
        printf("Saldo insuficiente para realizar a transferencia.\n");
        printf("----------------------------\n\n");
    }
}

// Função para salvar dados das contas em um arquivo
void salvarDados()
{
    FILE *arquivo;
    arquivo = fopen("dados_contas.txt", "w");

    if (arquivo == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
    {
        fprintf(arquivo, "N° da conta: %d | Titular: %s | Saldo: R$%.2lf\n", contas[i]->numero_conta, contas[i]->nome_titular, contas[i]->saldo);
    }

    fclose(arquivo);
    printf("\n");
    printf("----------------------------\n");
    printf("Dados das contas salvos no arquivo com sucesso!\n");
    printf("----------------------------\n");
    printf("\n");
}

// função voltar ao menu ou sair
void realizarAcao()
{
    int escolha;
    do
    {
        // Adicione aqui a chamada para a ação que deseja realizar
        printf("\nDeseja voltar ao menu?\n");
        printf("1 - Sim\n");
        printf("2 - Nao - para encerrar a sessao no banco\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            // Voltar ao menu
            break;
        case 2:
            printf("--------------\n");
            printf("FIM da operacao BANCO MASSA DE MAIS VEI.\n");
            exit(0); // Terminar o programa
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (escolha != 1);
}

int main()
{
    char BancoNome[] = "BANCO MASSA DE MAIS VEI";
    char senhaDigitada[20];
    int opcao;
    setlocale(LC_ALL, "");

    contas = (ContaBancaria **)malloc(MAX_CONTAS * sizeof(ContaBancaria *));
    if (contas == NULL)
    {
        fprintf(stderr, "Erro ao alocar memoria para o vetor de contas\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_CONTAS; i++)
    {
        contas[i] = NULL;
    }

    do
    {

        printf("Digite a senha para acessar o sistema do banco: ");
        scanf("%s", senhaDigitada);

        if (strcmp(senhaDigitada, SENHA_PADRAO) != 0)
        {
            printf("Senha incorreta! Tente novamente.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            getchar();
        }
    } while (strcmp(senhaDigitada, SENHA_PADRAO) != 0);

    while (1)
    {

        printf("%s\n", BancoNome);
        printf("\n------------ MENU ------------\n");
        printf("1 - Criar nova Conta\n");
        printf("2 - Depositar e sacar dinheiro em uma nova conta\n");
        printf("3 - Mostrar saldo total de cada conta\n");
        printf("4 - Editar informacoes do titular de uma conta\n");
        printf("5 - Remover conta\n");
        printf("6 - Transferir valor de uma conta para outra\n");
        printf("7 - Salvar dados de uma conta em um arquivo\n");
        printf("8 - SAIR\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:;
            // Chamar a função
            ContaBancaria *minha_conta = criarConta();

            // Encontrar um espaço vazio no array
            int i;
            for (i = 0; i < MAX_CONTAS && contas[i] != NULL; i++)
            {
            }

            // Checar se o número de contas
            if (i < MAX_CONTAS)
            {
                contas[i] = minha_conta;
                printf("\n");
                printf("----------------------------\n");
                printf("Conta criada com sucesso!\n");
                printf("----------------------------\n");
                printf("\n");
            }
            else
            {
                printf("\n");
                printf("----------------------------\n");
                printf("Limite de contas atingido. Nao eh possivel criar mais contas.\n");
                printf("----------------------------\n");
                printf("\n");

                free(minha_conta); // Liberar memória, se possível
            }
            realizarAcao();
            break;
        case 2:
            depositarSacar();
            break;
        case 3:
            mostrarSaldoTotal();
            realizarAcao();
            break;

        case 4:
        {
            int numeroContaEditar;
            printf("Digite o numero da conta que deseja editar: ");
            scanf("%d", &numeroContaEditar);

            // Encontrar a conta pelo número
            ContaBancaria *contaParaEditar = encontrarConta(numeroContaEditar);

            if (contaParaEditar != NULL)
            {
                // Chamar a função para editar as informações
                editarInformacoes(contaParaEditar);
            }
            else
            {
                printf("\n");
                printf("----------------------------\n");
                printf("Conta nao encontrada. Verifique o numero da conta e tente novamente.\n");
                printf("----------------------------\n");
                printf("\n");
            }
            realizarAcao();
            break;
        }
        case 5:;
            {
                int numeroConta;
                printf("Digite o numero da conta que deseja remover: ");
                scanf("%d", &numeroConta);
                removerConta(numeroConta);
                realizarAcao();
                break;
            }
        case 6:
            transferirValor();
            realizarAcao();
            break;
        case 7:
            salvarDados();
            realizarAcao();
            break;
        case 8:;
            printf("--------------\n");
            printf("FIM da operacao %s\n", BancoNome);

            for (int i = 0; i < MAX_CONTAS; i++)
            {
                free(contas[i]);
            }
            return 0;
        case 9:;

            break;
            // Liberar memoria quando o código terminar
            free(contas);

            exit(0);
        default:
            printf("Opcao incorreta. Pressione Enter para continuar...");
            getchar();
            getchar();
            break;
        }
    }

    return 0;
}