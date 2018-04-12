//背包问题：有m件物品和一个承重为t的背包。第i件物品的重量是w[i]，价值是v[i]。 

//求解将哪些物品装入背包可使这些物品的重量总和不超过背包承重量t，且价值总和最大。 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 

#include <string.h> 



int f[1010], w[1010], v[1010];//f记录不同承重量背包的总价值，w记录不同物品的重量，v记录不同物品的价值 



int getMax(int x, int y) {//返回x,y的最大值 

	if (x>y) return x;

	return y;

}



int main() {

	int t, m, i, j;

	memset(f, 0, sizeof(f));  //总价值初始化为0 

	printf("输入背包承重量t、物品的数目m:\n");
	scanf("%d %d", &t, &m);  //输入背包承重量t、物品的数目m 

	printf("输入m组物品的重量w[i]和价值v[i]:\n");
	for (i = 1; i <= m; i++)
		scanf("%d%d", &w[i], &v[i]);  //输入m组物品的重量w[i]和价值v[i] 

	for (i = 1; i <= m; i++) {  //尝试放置每一个物品 

		for (j = t; j >= w[i]; j--) {

			f[j] = getMax(f[j - w[i]] + v[i], f[j]);

			//在放入第i个物品前后，检验不同j承重量背包的总价值，如果放入第i个物品后比放入前的价值提高了，则修改j承重量背包的价值，否则不变 

		}

	}


	printf("最大价值:%d\n", f[t]);  //输出承重量为t的背包的总价值 

	system("pause");

	return 0;

}