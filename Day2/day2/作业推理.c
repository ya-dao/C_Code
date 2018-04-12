#include<stdio.h>
int main() {
	int num = -2;
	int num1 = 4294967294u;
	unsigned int data = 4294967294u;
	unsigned int data1 = -2;

	//-2µÄ²¹Âë:1111 1111 1111 1110
	printf("%d", num);		//-2
	printf("\n%u", num);	//4294967294
	printf("\n%d", num1);	//-2
	printf("\n%u", num1);   //4294967294
	printf("\n%u", data);   //4294967294
	printf("\n%d", data);	//-2
	printf("\n%u", data1);	//4294967294 
	printf("\n%d", data1);	//-2
	
	getchar();
	return 0;
}