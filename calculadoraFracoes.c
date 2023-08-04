/*
Autor: Renan Zago
Data de Criação: 03/08/2023
Objetivo: Implementar e usar o TAD número racional.
*/

// Bibliotecas
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

// Declarações globais
typedef struct
{
    int n; // Numerador
    int d; // Denominador
} tRacional;
tRacional racional1, racional2, soma, sub, mult, divid;
int opcao;

// Protótipos
void mostrarOpcoes(int *);
void lerRacional(tRacional *);
void EscreverRacional(tRacional);
tRacional somar(tRacional, tRacional);
tRacional subtrair(tRacional, tRacional);
tRacional multiplicar(tRacional, tRacional);
tRacional dividir(tRacional, tRacional);
tRacional simplificar(tRacional);
bool desejaContinuar();

// Função principal
int main()
{
    do
    {
        mostrarOpcoes(&opcao);
        switch (opcao)
        {
        // Simplificar
        case 1: 
            printf("\n[SIMPLIFICAR]\n");
            lerRacional(&racional1);
            EscreverRacional(simplificar(racional1));
            break;

        // Somar
        case 2: 
            printf("\n[SOMAR]\n");
            printf("[fracao 1]\n");
            lerRacional(&racional1);
            printf("[fracao 2]\n");
            lerRacional(&racional2);

            soma = somar(racional1, racional2);
            EscreverRacional(simplificar(soma));
            break;

        // Subtrair 
        case 3: 
            printf("\n[SUBTRAIR]\n");
            printf("[fracao 1]\n");
            lerRacional(&racional1);
            printf("[fracao 2]\n");
            lerRacional(&racional2);

            sub = subtrair(racional1, racional2);
            EscreverRacional(simplificar(sub));
            break;

        // Multiplicar
        case 4: 
            printf("\n[MULTIPLICAR]\n");
            printf("[fracao 1]\n");
            lerRacional(&racional1);
            printf("[fracao 2]\n");
            lerRacional(&racional2);

            mult = multiplicar(racional1, racional2);
            EscreverRacional(simplificar(mult));
            break;

        // Dividir
        case 5: 
            printf("\n[DIVIDIR]\n");
            printf("[fracao 1]\n");
            lerRacional(&racional1);
            printf("[fracao 2]\n");
            lerRacional(&racional2);
            
            // Tratamento de erro
            if (racional1.d == 0 || racional2.d == 0) 
            {
                printf("Erro: divisao por zero.\n");
            }
            else
            {
                divid = dividir(racional1, racional2);
                EscreverRacional(simplificar(divid));
            }
            break;

        // Sair
        case 6: 
            printf("Saindo...");
            sleep(2);
            return 0;
        default: 

            // Tratamento de erro
            printf("Entrada invalida!\n");
            
            while (getchar() != '\n') //Limpar buffer
            {
                continue;
            }
        }
        sleep(2);

    } while (desejaContinuar());
    printf("Saindo...");
    sleep(2);
}

// Função: mostrarOpcoes
// Objetivo: Exibir um menu com opções de cálculos com números racionais.
// Parâmetros: opcao - Ponteiro para a variável que armazenará a opção escolhida pelo usuário.
// Valor de Retorno: Nenhum (tipo de retorno "void").
void mostrarOpcoes(int *opcao)
{
    char input[100];
    printf("\n[FRACOES]\n");
    printf("# Escolha uma opcao #\n");
    printf("1. Simplificar\n");
    printf("2. Somar\n");
    printf("3. Subtrair\n");
    printf("4. Multiplicar\n");
    printf("5. Dividir\n");
    printf("6. Sair\n");

    scanf("%s", input);

    // Converte "input" de string para int
    *opcao = atoi(input);
}

// Função: lerRacional
// Objetivo: Realizar a leitura de um número racional (fração) do usuário e simplificá-lo.
// Parâmetros: racional - Ponteiro para a estrutura tRacional que armazenará o número lido.
// Valor de Retorno: Nenhum (tipo de retorno "void")
void lerRacional(tRacional *racional)
{
    // Tratamento de erro
    bool validInput = false;
    while (!validInput)
    {
        printf("numerador: ");
        int result = scanf("%d", &racional->n);

        // Verifica se a leitura foi bem sucedida e se o próximo caractere é uma quebra de linha
        if (result != 1 || getchar() != '\n')
        {
            printf("Entrada invalida! Digite um valor numerico inteiro para o numerador.\n");
            // Limpa o buffer 
            while (getchar() != '\n')
                ;
            continue;
        }

        validInput = true;
    }

    validInput = false;

    while (!validInput)
    {
        printf("denominador: ");
        int result = scanf("%d", &racional->d);

        // Verifica se a leitura foi bem sucedida e se o próximo caractere é uma quebra de linha
        if (result != 1 || getchar() != '\n')
        {
            printf("Entrada invalida! Digite um valor numerico inteiro para o denominador.\n");

            while (getchar() != '\n') // Limpa o buffer
                ;
            continue;
        }

        validInput = true;
    }

    *racional = simplificar(*racional);
}

// Função: EscreverRacional
// Objetivo: Imprimir na tela um número racional no formato numerador/denominador.
// Parâmetros: a - Estrutura tRacional contendo o número racional a ser impresso.
// Valor de Retorno: Nenhum (tipo de retorno "void")
void EscreverRacional(tRacional racional)
{
    printf("\n[Resultado]\n");
    printf("numerador: %d\n", racional.n);
    printf("denominador: %d\n", racional.d);
}

// Função: mdc
// Objetivo: Calcular o máximo divisor comum (MDC) entre dois números inteiros.
// Parâmetros: a - Primeiro número inteiro.
//             b - Segundo número inteiro.
// Valor de Retorno: O MDC entre a e b (tipo de retorno "int").
int mdc(int a, int b)
{
    int temp;
    while (b != 0)
    {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Função: simplificar
// Objetivo: Simplificar um número racional reduzindo-o à sua forma mais básica.
// Parâmetros: racional - Estrutura tRacional contendo o número racional a ser simplificado.
// Valor de Retorno: O número racional simplificado (tipo de retorno "tRacional").
tRacional simplificar(tRacional racional)
{
    int divisor = mdc(racional.n, racional.d);

    racional.n /= divisor;
    racional.d /= divisor;

    return racional;
}

// Função: somar
// Objetivo: Realizar a soma de dois números racionais.
// Parâmetros: racional1 - Estrutura tRacional contendo o primeiro número racional.
//             racional2 - Estrutura tRacional contendo o segundo número racional.
// Valor de Retorno: O resultado da soma como um número racional (tipo de retorno "tRacional").
tRacional somar(tRacional racional1, tRacional racional2)
{
    tRacional soma;
    if (racional1.d == racional2.d)
    {
        soma.n = racional1.n + racional2.n;
        soma.d = racional1.d;
    }
    else
    {
        soma.n = racional2.d * racional1.n + racional1.d * racional2.n;
        soma.d = racional1.d * racional2.d;
    }
    return soma;
}

// Função: subtrair
// Objetivo: Realizar a subtração de dois números racionais.
// Parâmetros: racional1 - Estrutura tRacional contendo o primeiro número racional.
//             racional2 - Estrutura tRacional contendo o segundo número racional.
// Valor de Retorno: O resultado da subtração como um número racional (tipo de retorno "tRacional").
tRacional subtrair(tRacional racional1, tRacional racional2)
{
    tRacional sub;
    if (racional1.d == racional2.d)
    {
        sub.n = racional1.n - racional2.n;
        sub.d = racional1.d;
    }
    else
    {
        sub.n = racional2.d * racional1.n - racional1.d * racional2.n;
        sub.d = racional1.d * racional2.d;
    }
    return sub;
}

// Função: multiplicar
// Objetivo: Realizar a multiplicação de dois números racionais.
// Parâmetros: racional1 - Estrutura tRacional contendo o primeiro número racional.
//             racional2 - Estrutura tRacional contendo o segundo número racional.
// Valor de Retorno: O resultado da multiplicação como um número racional (tipo de retorno "tRacional").
tRacional multiplicar(tRacional racional1, tRacional racional2)
{
    tRacional mult;
    mult.n = racional1.n * racional2.n;
    mult.d = racional1.d * racional2.d;

    return mult;
}

// Função: dividir
// Objetivo: Realizar a divisão de dois números racionais.
// Parâmetros: racional1 - Estrutura tRacional contendo o numerador e o denominador do primeiro número racional.
//             racional2 - Estrutura tRacional contendo o numerador e o denominador do segundo número racional.
// Valor de Retorno: O resultado da divisão como um número racional (tipo de retorno "tRacional").
tRacional dividir(tRacional racional1, tRacional racional2)
{
    tRacional div;
    div.n = racional1.n * racional2.d;
    div.d = racional2.n * racional1.d;

    return div;
}

// Função: desejaContinuar
// Objetivo: Perguntar ao usuário se ele deseja continuar realizando cálculos.
// Parâmetros: Nenhum.
// Valor de Retorno: True se o usuário deseja continuar, False caso contrário (tipo de retorno "bool").
bool desejaContinuar()
{
    char resposta;
    printf("Deseja continuar calculando? (s/n): ");
    scanf(" %c", &resposta);
    // Tratamento de erro
    while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N')
    {
        printf("Entrada invalida! Digite 's' para continuar ou 'n' para sair: ");
        while (getchar() != '\n') // Limpar o buffer
            ;
        scanf(" %c", &resposta);
    }

    return (resposta == 's' || resposta == 'S');
}
