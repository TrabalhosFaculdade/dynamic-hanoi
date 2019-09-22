//Bárbara Este Fernandez - 31937039
//Daniel Dias de Lima - 31687679
//Lucas Morita - XXXXXXXX

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Implementacao ingenua de Torres de Hanoi
void naiveHanoi(int n, char src, char dest, char temp, int *count)
{
    if (n > 0)
    {
        //incluindo na contagem apenas as chamadas 
        //com movimentos, ou seja, considerando T(0) = 0
        (*count)++; 

        naiveHanoi(n - 1, src, temp, dest, count);
        printf("Mova o disco do topo da da torre %c para a torre %c\n", src, dest);
        naiveHanoi(n - 1, temp, dest, src, count);
    }
}

//Implementação dinâmica de Torres de Hanoi usando memoization:

//Uma maneira de construir o algoritmo dinamico para a Torres
//de Hanoi é ter uma matriz para alocar os resultados, com n+1
//linhas para cada disco e 6 colunas para cada possibilidade
//de passagem de um disco de uma torre a outra (permutacao de
// tres torres duas a duas).

//Para qualquer [i][j], com 0 <= i < n+1 e j pertencente a
//['src->dest', 'src->temp', 'dest->src', 'dest->temp', 'temp->src', 'temp->dest'],
//0 indica que nao se tem calculado a resposta para o disco n
//no movimento j.

char *auxDynamicHanoi(char memoMatrix[][6][100], int n, int index, char src, char dest, char temp)
{
    int i;
    if (n == 0)
        return ""; //Caso base: quando n = 0, nenhum disco esta sendo movido.

    if (memoMatrix[n][index][0] == 0)
    {
        char *movimento = malloc(2 * sizeof(char));
        strcat(movimento, dest);
        strcat(movimento, src);

        char *temp1 = auxDynamicHanoi(memoMatrix, n - 1, 1, src, temp, dest);
        char *temp2 = auxDynamicHanoi(memoMatrix, n - 1, 5, temp, dest, src);

        char *temp3 = malloc(sizeof(movimento) + sizeof(temp1));
        strcat(temp3, movimento);
        strcat(temp3, temp2);

        free(movimento);
        free(temp1);
        free(temp2);

        char *temp4 = malloc(sizeof(temp1) + sizeof(temp3));
        strcat(temp4, temp1);
        strcat(temp4, temp3); //Aqui o pointeiro temp4 contem o endereco para o resultado de n discos

        memoMatrix[n][index][0] = malloc(sizeof(temp4));
        memoMatrix[n][index][0] = temp4;

        free(temp3);
        free(temp4);
    }

    for (i = 0; i < 100; i++)
    {
        printf(" %c ", memoMatrix[n][index][i]);
    }
    return memoMatrix[n][index][0];
}

void dynamicHanoi(int n, char src, char dest, char temp)
{
    char memoMatrix[n + 1][6][100]; //Inicializando a matriz de memoizacao
    for (int x = 0; x < n + 1; n++)
    {
        for (int y = 0; y < 6; y++)
        {
            for (int z = 0; z < 100; z++)
            {
                memoMatrix[x][y][z] = 0;
            }
        }
    }

    auxDynamicHanoi(memoMatrix, n, 0, src, dest, temp);
}

int main()
{
    int n;
    char src = 'A', dest = 'B', temp = 'C';

    int naiveCount = 0;

    printf("\nNro de discos = ");
    scanf(" %d", &n);

    // dynamicHanoi(n, src, dest, temp);
    naiveHanoi(n, src, dest, temp, &naiveCount);
    printf("Naive result: %d", naiveCount);
}
