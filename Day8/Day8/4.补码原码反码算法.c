#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
/*
	求一个数的原码,补码,反码
	将一个十进制的数据转成二进制需要注意的有:
		1.一个int类型的数据长度是32位,但是我们需要创建一个长度为33的数据,留出'\0',不然会因为没有字符结束标志打印出'烫烫烫'这种乱码.
		2.我们将值为1的数左移31位,然后目标数据分别与其相与,每次只能得到0或者非0的数,然后进行判断在对应的数组下标处填充1或者0.
		3.由于相与的最高位,如果是1那么肯定是个负数,所以不能判断相与是否大于0,只能判断是否!=0
			以8位的举例:
			目标:0100 0001			1000 0010
				&			左移1位:
			掩码:1000 0000			1000 0000
				 0000 0000			1000 0000
				相与得到0			相与得到255(即非0,该位二进制位为1)

	求补码思路:
		1.由于计算机中存储数字都是以补码形式存储,所以直接将该数转化为二进制即是补码.
			正数的补码/原码/反码全部是他本身,负数的形式各不一致
	求反码思路:
		1.由于正数的各个形式都是一致的,我们只需要对负数进行处理即可
		2.由于补码=反码+1,而计算机中的数字都是补码形式存储的,所以我们直接以该数-1即是反码
	求原码思路:
		1.由于正数的各个形式都是一致的,我们只需要对负数进行处理即可
		2.由于补码=原码取反+1,所以我们可以通过对其补码取反+1或者补码-1取反,都可以达到该目的
*/
void buMa(int number,char *p) {
	int mask = 1 << 31;
	for (int i = 0;i < 32;i++) {
		if (number & mask) {
			p[i] = '1';
		}
		else {
			p[i] = '0';
		}
		number <<= 1;
	}
}
void fanMa(int number, char *p) {
	int mask = 1 << 31;
	//如果目标小于0,则反码的值是补码-1
	if (number < 0) {
		number = number - 1;
	}
	for (int i = 0; i < 32;i++) {
		if (number & mask) {
			p[i] = '1';
		}
		else {
			p[i] = '0';
		}
		number <<= 1;
	}
}
void yuanMa(int number, char *p) {
	int mask = 1 << 31;
	
	if (number < 0) {
		//原码等于补码取反+1
		number = ~number + 1;
		//将符号位更改为1标识是个负数
		number = number | mask;
	}
	for (int i = 0; i < 32; i++) {
		if (number & mask) {
			p[i] = '1';
		}
		else {
			p[i] = '0';
		}

		number <<= 1;
	}
}
void main() {
	int number = 0;
	char buMaArr[33] = { 0 };
	char yuanMaArr[33] = { 0 };
	char fanMaArr[33] = { 0 };

	scanf("%d",&number);

	buMa(number, buMaArr);
	fanMa(number, fanMaArr);
	yuanMa(number, yuanMaArr);

	printf("补码:%s\n", buMaArr);
	printf("反码:%s\n", fanMaArr);
	printf("原码:%s\n",yuanMaArr);
	system("pause");
}