#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define N 50
#define R 20


typedef struct
{
    int codigo;
    char nome[N];
    char email[N];
    char cpf[R];
    char dataNascimento[R];
    char dataCadastro[R];
} Cliente;
typedef struct
{
    int numero;
    Cliente cliente;
    float saldo;
    float limite;
    float saldoTotal;
} Conta;

void menu();
void infoCliente(Cliente cliente);
void infoConta(Conta conta);
void criarConta();
void efetuarSaque();
void efetuarDeposito();
void efetuarTransferencia();
void listarContas();
float atualizaSaldoTotal(Conta conta);
Conta buscarContaPorNumero(int numero);
void sacar(Conta conta, float valor);
void depositar(Conta conta, float valor);
void transferir(Conta contaOrigem, Conta contaDestino, float valor);

static Conta contas[50];
static int contador_contas = 0;
static int contador_clientes = 0;


int main()
{
    menu();
    return 0;
}

void menu()
{
    int opcao;

    printf("--- Bem Vindo ---\n"); // apresenta as opções ao usuário
    printf("Selecione uma das opcoes abaixo\n");
    printf("1 - Criar conta\n");
    printf("2 - Efetuar saque \n");
    printf("3 - Efetuar deposito \n");
    printf("4 - Efetuar transferencia \n");
    printf("5 - Listar contas\n");
    printf("6 - Sair do sistema \n");

    scanf("%d", &opcao); // pega a opção desejada
    getchar();

    switch(opcao)  // para cada sistuação
    {
    case 1: // cria conta
        criarConta();
        break;
    case 2: // sacar
        efetuarSaque();
        break;
    case 3: // depositar
        efetuarDeposito();
        break;
    case 4: // transferir
        efetuarTransferencia();
        break;
    case 5: // listar
        listarContas();
        break;
    case 6: // sair do sistema
        printf("Ate a proxima\n");
        printf("Volte sempre\n");
        Sleep(4);
        exit(0);
    default: // caso nenhuma das opções seja satisfeita
        printf("opcao invalida\n");
        Sleep(2);
        menu();
        break;
    }



}
// informa os dados desejados
void infoCliente(Cliente cliente)
{
    printf("Nome: %s\nCodigo: %d\nNascimento: %s\nCadastro: %s\n",
           strtok(cliente.nome, "\n"), cliente.codigo, strtok(cliente.dataNascimento, "\n"),
           strtok(cliente.dataCadastro, "\n"));
}
// informa os dados da conta desejada
void infoConta(Conta conta)
{
    printf("Nome: %s\nConta: %d\nNascimento: %s\nCadastro: %s\nSaldo total: %.2f\n",
           strtok(conta.cliente.nome, "\n"), conta.numero, strtok(conta.cliente.dataNascimento, "\n"),
           strtok(conta.cliente.dataCadastro, "\n"), conta.saldoTotal);
}
// cria uma conta a partir dos dados fornecidos
void criarConta()
{
    Cliente cliente;

    // Data de cadastro
    char dia[3];
    char mes[3];
    char ano[5];
    char dataCadastro[20];
    time_t t = time(NULL);

    struct tm tm = *localtime(&t);

    if(tm.tm_mday < 10)
        sprintf(dia, "0%d",  tm.tm_mday);
    else
        sprintf(dia, "%d", tm.tm_mday);
    if((tm.tm_mon + 1) < 10)
        sprintf(mes, "0%d", (tm.tm_mon + 1));
    else
        sprintf(mes, "%d", (tm.tm_mon + 1));
    // ano
    sprintf(ano, "%d", (tm.tm_year + 1900));


    // concatenando a data do cadastro para a variável dataCadastro

    strcpy(dataCadastro, "");
    strcat(dataCadastro, dia);
    strcat(dataCadastro,"/");
    strcat(dataCadastro,mes);
    strcat(dataCadastro,"/");
    strcat(dataCadastro,ano);
    strcat(dataCadastro,"\0");

    strcpy(cliente.dataCadastro, dataCadastro);
    // criar cliente
    printf("informe seus dados\n");
    cliente.codigo = contador_clientes + 1;

    printf("Informe seu Nome\n");
    fgets(cliente.nome,N,stdin);

    printf("Informe seu Email\n");
    fgets(cliente.email,N,stdin);

    printf("Informe seu cpf\n");
    fgets(cliente.cpf,R,stdin);

    printf("Informe sua data de nascimento\n");
    fgets(cliente.dataNascimento,R,stdin);

    contador_clientes++;

    // Criar a conta

    contas[contador_contas].numero = contador_contas + 1;
    contas[contador_contas].cliente = cliente;
    contas[contador_contas].saldo = 0.0;
    contas[contador_contas].limite = 0.0;
    contas[contador_contas].saldoTotal = atualizaSaldoTotal(contas[contador_contas]);


    printf("Conta criada com sucesso\n");
    printf("\n");
    printf("Dados da conta criada\n");
    infoConta(contas[contador_contas]);

    contador_contas++;

    Sleep(4);
    menu();
}
void efetuarSaque()
{
    if(contador_contas)
    {
        int numero;
        printf("Informe o numero da conta\n");
        scanf("%d", &numero);

        Conta conta = buscarContaPorNumero(numero);
        if(conta.numero == numero)
        {
            int valor;
            printf("informe o valor do saque\n");
            scanf("%f", &valor);
            depositar(conta, valor);
        }
        else
        {
            printf("nao foi encontrada nenhuma conta com o numero informado\n");
        }

    }
    else
    {
        printf("Nao existem contas cadastradas\n");
    }
    Sleep(4);
    menu();
}
void efetuarDeposito()
{
    if(contador_contas)
    {
        int numero;
        printf("Informe o numero da conta\n");
        scanf("%d", &numero);

        Conta conta = buscarContaPorNumero(numero);
        if(conta.numero == numero)
        {
            int valor;
            printf("informe o valor do saque\n");
            scanf("%f", &valor);
            sacar(conta, valor);
        }
        else
        {
            printf("nao foi encontrada nenhuma conta com o numero informado\n");
        }

    }
    else
    {
        printf("Nao existem contas cadastradas\n");
    }
    Sleep(4);
    menu();
}
void efetuarTransferencia()
{
    if(contador_contas)
    {
        int numeroOrigem,numeroDestino;
        printf("Informe o numero da sua conta\n");
        scanf("%d", &numeroOrigem);

        Conta contaOrigem = buscarContaPorNumero(numeroOrigem);

        if(contaOrigem.numero == numeroOrigem)
        {
            printf("Informe o numero da conta do destinatario\n");
            scanf("%d", &numeroDestino);

            Conta contaDestino = buscarContaPorNumero(numeroDestino);

            if(contaDestino.numero == numeroDestino)
            {
                float valor;
                printf("informe o valor do saque\n");
                scanf("%f", &valor);
                transferir(contaOrigem, contaDestino, valor);
            }
            else
            {
                printf("Conta de numero %d nao foi encontrada\n", contaDestino.numero);
            }
        }
        else
        {
            printf("Conta de numero %d nao foi encontrada\n", contaOrigem.numero);
        }

    }
    else
    {
        printf("Nao existem contas cadastradas\n");
    }
    Sleep(4);
    menu();
}
// Informa as contas existentes
void listarContas()
{
    if(contador_contas > 0){
        for(int i = 0; i < contador_contas; i++){
            infoConta(contas[i]);
            printf("-------------------\n");
            Sleep(2);
        }
    }else
    {
        printf("Nao existem contas cadastradas\n");
    }
    Sleep(4);
    menu();
}
// atualiza o saldo total
float atualizaSaldoTotal(Conta conta)
{
    return conta.saldo + conta.limite; // atualizando o saldo total -> saldo + limite
}

// Procura por uma conta a partir do numero da conta
Conta buscarContaPorNumero(int numero)
{
    Conta c;
    if(contador_contas > 0)
    {
        for(int i = 0; i < contador_contas; i++)
        {
            if(contas[i].numero == numero)
            {
                c = contas[i];
            }
        }
    }
    return c;
}

void sacar(Conta conta, float valor)
{
    if(valor > 0 && conta.saldoTotal >= valor)
    {
        for(int i = 0; i < contador_contas; i++)
        {
            if(contas[i].numero == conta.numero)
            {
                if(contas[i].saldo >= valor)
                {
                    contas[i].saldo = contas[i].saldo - valor;
                    contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
                    printf("saque efetuado com sucesso\n");
                }
                else
                {
                    float restante = contas[i].saldo - valor;
                    contas[i].limite += restante;
                    contas[i].saldo = 0.0;
                    contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
                    printf("saque efetuado com sucesso\n");
                }
            }
        }
    }
    else
    {
        printf("Saque nao realizado. Tente novamente\n");
    }
}
void depositar(Conta conta, float valor)
{
    if(valor > 0)
    {
        for(int i = 0; i < contador_contas; i++)
        {
            if(contas[i].numero == conta.numero)
            {
                contas[i].saldo += valor;
                contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
                printf("Deposito efetuado com sucesso\n");
            }
        }
    }
    else
    {
        printf("O valor foi digitado de forma incorreta\n");
    }
}
void transferir(Conta contaOrigem, Conta contaDestino, float valor)
{
    if(valor > 0 && contaOrigem.saldoTotal >= valor)
    {
        for(int co = 0; co < contador_contas; co++)
        {
            if(contas[co].numero == contaOrigem.numero) {}
            for(int cd = 0; cd < contador_contas; cd++)
            {
                if(contas[cd].numero == contaDestino.numero)
                {
                    if(contas[co].saldo >= valor)
                    {
                        contas[co].saldo  -= valor;
                        contas[co].saldoTotal = atualizaSaldoTotal(contas[co]);
                        contas[cd].saldo += valor;
                        contas[cd].saldoTotal = atualizaSaldoTotal(contas[cd]);
                        printf("Transferencia realizada com sucesso");
                    }
                    else
                    {
                        float restante = contas[co].saldo - valor;
                        contas[co].limite += restante;
                        contas[co].saldo = 0.0;
                        contas[cd].saldo += valor;
                        contas[co].saldoTotal = atualizaSaldoTotal(contas[co]);
                        contas[cd].saldoTotal = atualizaSaldoTotal(contas[cd]);
                        printf("Transferencia realizada com sucesso");
                    }
                }
            }
        }
    }
    else
    {
        printf("Transferencia nao autorizada\n");
    }
}
