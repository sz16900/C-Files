// neillsMicrowave.cpp : Defines the entry point for the console application.
//

#include "stdio.h"

#define N 5

int main()
{
	int a[N];
	int i, sum = 0;

	for (i = 0; i < N; i++) {
		a[i] = 7 + i * i;
	}

	for (i = 0; i < N; i++) {
		printf("a[%d] = %d \n ", i, a[i]);
	}

	for (i = 0; i < N; i++) {
		sum += a[i];
	}

	printf("\nsum = %d\n", sum);
    return 0;
}


