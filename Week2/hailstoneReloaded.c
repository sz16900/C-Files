// hailstoneReloaded.cpp : Defines the entry point for the console application.
//

#include "stdio.h"

int hailstone(void);


int main()
{
	hailstone();
    return 0;
}

int hailstone() {

	int initialNumber = 3;
	int sequence = 1;
	int x = 0, y = 0, z = 0;
	int initialNumberStorer = 0;
	int sequenceStorer = 0;

	for (initialNumber = 3; initialNumber < 50000; initialNumber = initialNumber + 1) {

		x = initialNumber;

		while (x > 1) {
			if (x % 2 == 0) {
				x = x / 2;
			}
			else {
				x = (3 * x) + 1;
			}


			if (x > y) { /*This is to check the largest number in the sequence*/
				z = initialNumber;
				y = x;
			}

			sequence = sequence + 1;
		}

		if (sequence > sequenceStorer) {
			initialNumberStorer = initialNumber;
			sequenceStorer = sequence;
		}

		sequence = 1;
	}

	printf("The biggest Initial Number less than 50,000 is %d with %d Sequences. \n", initialNumberStorer, sequenceStorer);
	printf("\n");
	printf("The largest number in the sequence is %d which is inside number %d \n", y, z);
}




