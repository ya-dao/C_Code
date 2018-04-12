#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 54

/*
	四个人，54 -》 13 14 13 14
	要求必须使用递归
	思路：按照黑、红、梅、方从1到10的顺序存储，约定最后两张为大小王,54 and 53
	3   4   5  6
	红	方	梅 黑
*/
void show(int *arr);
void swap(int *arr,int count);
void deals(int cardIndex,int *arr,int *arr_A,int *arr_B,int *arr_C,int *arr_D);
void showCard(char player,int *arr);
//currentIndex:发到当前牌库哪一张了
int currentIndex = 0;

void main(){
	int arr[N] = {0};
	int arr_A[14] = {0};
	int arr_B[14] = {0};
	int arr_C[14] = {0};
	int arr_D[14] = {0};

	int i = 0;
	for(;i < 54;i++){
		arr[i] = i + 1;
	}

	srand(NULL);
	swap(arr,50);

	deals(0,arr,arr_A,arr_B,arr_C,arr_D);

	showCard('A',arr_A);
	showCard('B',arr_B);
	showCard('C',arr_C);
	showCard('D',arr_D);

	/*show(arr_A);
	show(arr_B);
	show(arr_C);
	show(arr_D);*/

	system("pause");
}

/*发牌
	cardIndex:手上第几张牌
*/
void deals(int cardIndex,int *arr,int *arr_A,int *arr_B,int *arr_C,int *arr_D){
	if(cardIndex == 13){
		*(arr_B + cardIndex) = *(arr + currentIndex++);
		*(arr_D + cardIndex) = *(arr + currentIndex++);
	}else{
		deals(cardIndex + 1,arr,arr_A,arr_B,arr_C,arr_D);
		*(arr_A + cardIndex) = *(arr + currentIndex++);
		*(arr_B + cardIndex) = *(arr + currentIndex++);
		*(arr_C + cardIndex) = *(arr + currentIndex++);
		*(arr_D + cardIndex) = *(arr + currentIndex++);
	}
}

//把牌顺序打乱
void swap(int *arr,int count){
	int i = 0;
	for(;i < count;i++){
		int index_1 = rand() % 54;
		int index_2 = rand() % 54;
		if(index_1 != index_2){
			int temp = *(arr + index_1);
			*(arr + index_1) = *(arr + index_2);
			*(arr + index_2) = temp;
		}
	}	
}

//显示手上的牌对应牌库里面的下标
void show(int *arr){
	int i = 0;
	for(i = 0;i < 14;i++){
		if (arr[i] == 0) {
			continue;
		}
		printf("%2d ",arr[i]);
		if((i + 1) % 14 == 0){
			printf("\n");
		}
	}
	printf("\n");
}
//显示手上的牌对应的花色和点数
void showCard(char player,int *arr){
	int i = 0;
	printf("player%c:",player);
	for(i = 0;i < 14;i++){
		if (*(arr + i) == 0) {
			continue;
		}
		int points = *(arr + i) / 4 + 1;
		int color = *(arr + i) % 4 + 3;
		if(points == 1){	//A
			printf("%c%2c ",color,'A');
		}else if(points == 11){		//J
			printf("%c%2c ",color,'J');
		}else if(points == 12){		//Q
			printf("%c%2c ",color,'Q');
		}else if(points == 13){		//K
			printf("%c%2c ",color,'K');
		}else if(points == 14){		//大王 小王
			if(color = 3){
				printf("%2c ",'$');
			}else{
				printf("%2c ",'&');
			}
		}else{
			printf("%c%3d ",color,points);
		}
		
	}
	printf("\n\n");
}
