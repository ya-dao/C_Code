#include <stdio.h>
#include <stdlib.h>

void show3(char **p) {
	printf("show3\n");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			printf("%d ", p[i][j]);
		}
		printf("\n");
	}
}

void show2(char *p1, char *p2) {
	printf("show2\n");
	char *p[2] = { p1,p2 };
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			printf("%d ", p[i][j]);
		}
		printf("\n");
	}

	show3(p);
}

void show1(char *mac) {
	printf("show1\n");
	for (int i = 0; i < 6; i++)
	{
		printf("%d ", mac[i]);
	}
	printf("\n");
}

void show(char (*mac)[6]) {
	printf("show\n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			mac[i][j] = (*(mac + i))[j];
			printf("%d ",(*(mac + i))[j]);
		}
		printf("\n");
	}
}

int main1() {
	char (*mac)[6] = calloc(3 , sizeof(char ) * 6);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			(*(mac + i))[j] = (i + 1) * (j + 1);

		}
	}
	show(mac);
	show1(*(mac + 1));
	//show1(mac + 1);

	show2(*(mac + 1), *(mac + 2));

	char *p = NULL;
	p = *(mac + 1);

	free(mac);
	system("pause");
	return 0;

}