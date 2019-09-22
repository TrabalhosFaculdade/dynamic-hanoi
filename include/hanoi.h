#ifndef HANOI
#define HANOI

#define UNDEFINED_RESULT 0

void naive(int n, char src, char dest, char temp, int *count);
void dynamic (int n, char src, char dest, char temp, int *count);

#endif