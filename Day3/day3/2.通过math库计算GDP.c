#include<stdio.h>
/*
2.计算GDP，10 ->  1.07     50->1.02   中国GDP多少年可以达到世界30%  math
*/
int main() {
	float china = 10.0f;
	float chinaIncrease = 1.07f;
	float world = 50.0f;
	float worldIncrease = 1.02f;
	int i = 1;
	while (china - world * 0.3f <= 0) {
		china = china * (chinaIncrease * i);
		world = world * (worldIncrease * i);
		i++;
		printf("%f,%f\n", china, world);
	}

	printf("%d年后,天朝达到世界的30%\n", i);

	getchar();
	return 0;
}