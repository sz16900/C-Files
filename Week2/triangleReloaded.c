// trianglesReloaded.c.cpp : Defines the entry point for the console application.
//

#include "stdio.h"

int addTheNext(void);

int main()
{
	addTheNext();	

    return 0;
}

int addTheNext(){
    int i = 2, sum_of_numbers = 1, end = 1;
    printf("The nth triangle # is 1 based on the equation nth = n*(n+1)/2 \n");
    while (i<50) {
		sum_of_numbers = (i *(i+1)/2);
		i++;
		printf("The nth triangle # is %d based on the equation nth = n*(n+1)/2 \n", sum_of_numbers);
		}
}

