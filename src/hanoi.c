
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hanoi.h"

void printMovement(char src, char dest)
{
    #ifdef DEBUG
    printf("Mova o disco do topo da da torre %c para a torre %c\n", src, dest);
    #endif
}

char *solveDinamically(int n, int src, int dest, int temp, int *count, char ***memo)
{
    (*count)++;

    int index = src * 3 + dest; // Column in memo
    if (memo[n][index] == NULL) // Not computed yet
    {

        char *hold = solveDinamically(n - 1, src, temp, dest, count, memo),
             *result = (char *)calloc(2 * (strlen(hold) + 1), sizeof *result);
        char addend[2] = "0";
        addend[0] = (char)('0' + 3 * src + dest);
        strcpy(result, hold);
        strcat(result, addend);
        strcat(result, solveDinamically(n - 1, temp, dest, src, count, memo));
        memo[n][index] = result;
    }
    return memo[n][index];
}

char ***buildMemoizationTable(int memoSize)
{
    char empty[1] = {'\0'};
    char ***memo = NULL;

    int row, col;
    if (memo != NULL)
    { // Row zero cells point at the global variable empty
        free(memo[0]);
        for (row = 1; row <= memoSize; row++)
        {
            for (col = 0; col < 8; col++)
            {
                if (memo[row][col] != NULL)
                    free(memo[row][col]);
            }
            free(memo[row]);
        }
        free(memo);
        memo = NULL;
    }
    memo = (char ***)calloc(memoSize + 1, sizeof *memo);
    for (row = 0; row <= memoSize; row++)
        memo[row] = (char **)calloc(8, sizeof *memo[row]);
    for (col = 0; col < 8; col++)
        memo[0][col] = empty;

    return memo;
}

/*
A ideia da presente solução é trocar tempo exponencial 
por espaço exponencial, assim sendo, a ideia é diminuir 
a quantidade de memória usada pela tabela de memoization

Nesse sentido, a sequência de movimentos é gravada em uma
string onde cada caracter, cujo valor fica entre 1 e 7,
representa um movimento.

Cada valor pode então ser convertido para seu valor em base 
terciária, e usar os dois caractereres dessa conversão para 
dizer qual pilar é o src e qual é o dest.

Essa conversão segue os valores abaixo, 
onde 0 - first, 1 - second e 3 - third:

01 - 1
02 - 2
10 - 3
11 - 4
12 - 5
20 - 6
21 - 7
*/
void decodeMovementValue(int move, char first, char second, char third)
{
    char src, dest;

    switch (move)
    {
    case 1:
        //1 - 01
        src = first;
        dest = second;
        break;

    case 2:
        //2 - 02
        src = first;
        dest = third;
        break;

    case 3:
        // 10 - 3
        src = second;
        dest = first;
        break;

    case 4:
        // 11 - 4
        perror("Move 4 does not make much sense, since we would be moving from B to B");
        exit(EXIT_FAILURE);
        break;

    case 5:
        // 12 - 5
        src = second;
        dest = third;
        break;

    case 6:
        // 20 - 6
        src = third;
        dest = first;
        break;

    case 7:
        //21 - 7
        src = third;
        dest = second;
        break;

    default:
        perror("Movement code could not be found\n");
        exit(EXIT_FAILURE);
        break;
    }

    printMovement(src, dest);
}

//Implementacao ingenua de Torres de Hanoi
void naive(int n, char src, char dest, char temp, int *count)
{
    if (n > 0)
    {
        //incluindo na contagem apenas as chamadas
        //com movimentos, ou seja, considerando T(0) = 0
        (*count)++;

        naive(n - 1, src, temp, dest, count);
        printMovement(src, dest);
        naive(n - 1, temp, dest, src, count);
    }
}

/*
Implementação dinâmica de Torres de Hanoi usando memoization:

Uma maneira de construir o algoritmo dinamico para a Torres
de Hanoi é ter uma matriz para alocar os resultados, com n+1
linhas para cada disco e 6 colunas para cada possibilidade
de passagem de um disco de uma torre a outra (permutacao de
tres torres duas a duas).

Para qualquer [i][j], com 0 <= i < n+1 e j pertencente a
['src->dest', 'src->temp', 'dest->src', 
'dest->temp', 'temp->src', 'temp->dest'],
0 indica que nao se tem calculado a resposta para o disco n
no movimento j.
*/
void dynamic(int n, char src, char dest, char temp, int *count)
{
    char ***memo = buildMemoizationTable(n);
    char *answer = solveDinamically(n, 0, 1, 2, count, memo);

    for (unsigned int i = 0; i < strlen(answer); i++)
    {
        //converting a character movement in a specific position of 'answer' to int
        char movementChar = answer[i];
        int movementInt = movementChar - '0';

        //decode movement, and print result
        decodeMovementValue(movementInt, src, temp, dest);
    }
}