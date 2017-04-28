// neillsMicrowave.cpp : Defines the entry point for the console application.
//

#include "stdio.h"

void swap(int *p, int *q);
int main()
{
	int a = 3, b = 7;

	printf("%d %d \n", a, b);
	swap(&a, &b);
	printf("%d %d \n", a, b);

    return 0;
}

void swap(int *p, int *q) {
	int tmp = 0;
	tmp = *p;
	*p = *q;
	*q = tmp;

}
