#include <stdio.h>
#include <stdlib.h> // atoi, among other things
#include <string.h> // strlen, strcpy, strcat

char ***memo = NULL;
int memoSize;
char empty[1] = {'\0'};

/**
01 - 1
02 - 2
10 - 3
11 - 4
12 - 5
20 - 6
21 - 7
*/
void decodeMovementValue(int move)
{
    char first = 'A', second = 'B', third = 'C';
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

    printf("Mova o disco do topo da da torre %c para a torre %c\n", src, dest);
}

void buildMemoizationTable(int memoSize)
{
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
}

char *dynamicHanoi(int n, int src, int dest, int temp, int *count)
{
    int index = src * 3 + dest; // Column in memo

    if (memo[n][index] == NULL) // Not computed yet
    {
        (*count)++;
        char *hold = dynamicHanoi(n - 1, src, temp, dest, count),
             *result = (char *)calloc(2 * (strlen(hold) + 1), sizeof *result);
        char addend[2] = "0";
        addend[0] = (char)('0' + 3 * src + dest);
        strcpy(result, hold);
        strcat(result, addend);
        strcat(result, dynamicHanoi(n - 1, temp, dest, src, count));
        memo[n][index] = result;
    }
    return memo[n][index];
}

int main()
{
    int size = 5;
    int count = 0;

    char *answer;

    buildMemoizationTable(size);
    answer = dynamicHanoi(size, 0, 1, 2, &count);

    for (unsigned int i = 0; i < strlen(answer); i++)
    {
        //converting a character movement in a specific position of 'answer' to int
        char movementChar = answer[i];
        int movementInt = movementChar - '0';

        //decode movement, and print result
        decodeMovementValue(movementInt);
    }

    printf("Resulting number of calls: %d\n", count);
}
