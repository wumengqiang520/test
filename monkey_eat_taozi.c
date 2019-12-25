#include <stdio.h>

int main()
{
	int day = 9;
	int total;
	int x = 1;
	while (day>0) {

				total = (x+1)*2;
				x = total;
				day--;
	}
	printf("桃子总数是%d\n",total);	
	return 0;
}
