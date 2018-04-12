#include<stdio.h>
void all(){
	int i = 0,j = 0;
	for(i = 1;i <= 9;i++){
		for(j = 1;j <= 9;j++){
			printf("%2d*%2d=%2d",i,j,i * j);
		}
		putchar(10);
	}	
}
void leftBottom(){
	int i = 0,j = 0;
	for(i = 1;i <= 9;i++){
		for(j = 1;j <= 9;j++){
			if(j <= i){
				printf("%2d*%2d=%2d",i,j,i * j);
			}
		}
		putchar(10);
	}
}
void leftTop(){
	int i = 0,j = 0;
	for(i = 1;i <= 9;i++){
		for(j = 1;j <= 9;j++){
			if(j <= (9 - i + 1)){
				printf("%2d*%2d=%2d",i,j,i * j);
			}
		}
		putchar(10);
	}
}

void leftMiddle(){
	int i = 0,j = 0;
	for(i = 1;i <= 9;i++){
		for(j = 1;j <= 9;j++){
			if((j <= i) && (j <= (9 - i + 1))){
				printf("%2d*%2d=%2d",i,j,i * j);
			}else{
				printf("%8s","");
			}
		}
		putchar(10);
	}
}

void middleTop(){
	int i = 0,j = 0;
	for(i = 1;i <= 9;i++){
		for(j = 1;j <= 9;j++){
			if((j >= i) && (j <= (9 - i + 1))){
				printf("%2d*%2d=%2d",i,j,i * j);
			}else{
				printf("%8s","");
			}
		}
		putchar(10);
	}
}

void rightMiddle(){
	int i = 0,j = 0;
	for(i = 1;i <= 9;i++){
		for(j = 1;j <= 9;j++){
			if((j >= i) && (j >= (9 - i + 1))){
				printf("%2d*%2d=%2d",i,j,i * j);
			}else{
				printf("%8s","");
			}
		}
		putchar(10);
	}
}

void rightBottom(){
	int i = 0,j = 0;
	for(i = 1;i <= 9;i++){
		for(j = 1;j <= 9;j++){
			if(j >= (9 - i + 1)){
				printf("%2d*%2d=%2d",i,j,i * j);
			}else{
				printf("%8s","");
			}
		}
		putchar(10);
	}
}

void bottomMiddle(){
	int i = 0,j = 0;
	for(i = 1;i <= 9;i++){
		for(j = 1;j <= 9;j++){
			if((j <= i) && (j >= (9 - i + 1))){
				printf("%2d*%2d=%2d",i,j,i * j);
			}else{
				printf("%8s","");
			}
		}
		putchar(10);
	}
}

void main(){
	all();
	putchar(10);

	leftBottom();
	putchar(10);

	leftMiddle();
	putchar(10);

	leftTop();
	putchar(10);

	middleTop();
	putchar(10);

	rightMiddle();
	putchar(10);
	
	rightBottom();
	putchar(10);

	bottomMiddle();
	putchar(10);
}