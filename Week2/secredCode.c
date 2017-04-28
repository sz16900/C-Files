#include <stdio.h>
#include <stdlib.h>


int main()
{
	int user_code;
	printf("Please, enter your words to be converted to the SECRET CODE!!!! \n");
	while (((user_code = getchar()) != EOF)) {

		if (user_code >= 65 && user_code <= 90) {
			putchar(155 - user_code);
		}
		else if (user_code == 10) {

		}
		else if (isspace(user_code) != 0) {
			putchar(user_code);
		}

		else {
			putchar(219 - user_code);
		}
	}

	return 0;
}

