//Bárbara Este Fernandez - 31937039

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Implementação ingênua de Torres de Hanoi:
void naiveHanoi(int n, char src, char dest, char temp) {
	if(n > 0) {
		naiveHanoi(n-1, src, temp, dest);
		printf("\nMova o disco %d da torre %c para a torre %c", n, src, dest);
		naiveHanoi(n-1, temp, dest, src);
	}
}

//Implementação dinâmica de Torres de Hanoi usando memoization:

//Uma maneira de construir o algoritmo dinâmico para a Torres
//de Hanoi é ter uma matriz para alocar os resultados, com n+1
//linhas para cada disco e 6 colunas para cada possibilidade
//de passagem de um disco de uma torre à outra (permutação de
// três torres duas a duas).

//Para qualquer [i][j], com 0 <= i < n+1 e j pertencente a
//{'src->dest', 'src->temp', 'dest->src', 'dest->temp', 'temp->src', 'temp->dest'},
//0 indica que não se tem calculado a resposta para o disco n
//no movimento j.

void auxDynamicHanoi(char memoMatrix[][6], int n, int index, char src, char dest, char temp) {
	if(n == 0) return; //Caso base: quando n = 0, nenhum disco está sendo movido.
	
	if(memoMatrix[n][index] == 0) {
		char *movimento = malloc(2 * sizeof(char));
		movimento = strcat(src, dest);

		char *resultado =  malloc(sizeof(strcat(auxDynamicHanoi(memoMatrix, n-1, index, src, temp, dest), strcat(movimento, auxDynamicHanoi(memoMatrix, n-1, index, temp, dest, src)))));
		resultado = strcat(auxDynamicHanoi(memoMatrix, n-1, index, src, temp, dest), strcat(movimento, auxDynamicHanoi(memoMatrix, n-1, index, temp, dest, src)));
		memoMatrix[n][index] = resultado;
	}
	return memoMatrix[n][index];
}

void dynamicHanoi(int n, char src, char dest, char temp) {
	char memoMatrix[n+1][6] = {{0}}; //Inicializando a matriz de memoização com zeros
	
	
}

int main() {
	int n;
	char src = 'A', dest = 'B', temp = 'C';
	
	printf("\nNro de discos = ");
	scanf(" %d", &n);
	
	naiveHanoi(n, src, dest, temp);
}
