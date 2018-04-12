#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void show(int poker[54]) {
	for (int i = 0; i < 54; i++)
	{
		if (i % 10 == 0) {
			printf("\n");
		}
		printf("%2d ", poker[i]);
	}
	printf("\n");
}
void main() {
	srand(time(NULL));

	int poker[54] = { 0 };
	for (int i = 0;i < 54;i++)
	{
		poker[i] = i + 1;
	}

	show(poker);

	for (int i = 0; i < 54;i++) 
	{
		int other = rand() % (54);
		int temp = poker[i];
		poker[i] = poker[other];
		poker[other] = temp;
	}

	show(poker);

	system("pause");
}
