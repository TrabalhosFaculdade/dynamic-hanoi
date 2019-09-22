#include <stdlib.h>
#include <stdio.h>

#include "hanoi.h"

//comentar para imprimir os movimentos
#define DEBUG

int main()
{
    int dinamicCounter, naiveCounter;
    dinamicCounter = naiveCounter = 0;

    int n = 0;

    //eu iria sugerir nao passar de 15 discos :)
    printf("Numero de discos: ");
    scanf("%d", &n);

    naive(n, 'A', 'B', 'C', &naiveCounter);
    dynamic(n, 'A', 'B', 'C', &dinamicCounter);

    printf("Number of calls for naive solution: %d\n", naiveCounter);
    printf("Number of calls for dinamic solution: %d\n", dinamicCounter);
}