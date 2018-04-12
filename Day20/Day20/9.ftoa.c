#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void* ftoa(float value,void *buffer,int size) {
	//判空
	if (buffer == NULL || size == 0)
	{
		return NULL;
	}
	char *buffer_temp = buffer;
	//前面操作的位置要小于指定的整体字符串的长度
	int currentIndex = 0;
	//判负
	if (value < 0)
	{
		*buffer_temp = '-';
		buffer_temp++;
		currentIndex++;
	}
	//获取整数部分长度
	int integer = (int)value;
	int int_length = 0;
	while (integer > 0)
	{
		integer /= 10;
		int_length++;
	}
	//干活,先转整数部分
	//再次重置整数部分的值
	integer = (int)value;
	//备份长度,下面要用
	int  length_backup = int_length;
	while (length_backup > 0)
	{
		//如果当前已经操作临界位置,就在最后一位添加'\0'并返回,由于是从0开始的下标,所以实际下标和长度相差1
		if (currentIndex == size - 1)
		{
			*buffer_temp = '\0';
			return buffer;
		}
		*(buffer_temp + length_backup - 1) = integer % 10 + '0';
		integer /= 10;
		length_backup--;
		currentIndex++;
	}
	//越过整数部分并添加小数点
	buffer_temp += int_length;
	*buffer_temp = '.';
	buffer_temp++;
	currentIndex++;
	//处理小数点
	//先获取小数
	float decimal = value - (int)value;
	while (decimal > 0)
	{
		//如果当前已经操作临界位置,就在最后一位添加'\0'并返回,由于是从0开始的下标,所以实际下标和长度相差1
		if (currentIndex == size - 1)
		{
			*buffer_temp = '\0';
			return buffer;
		}
		//小数每次乘以10再取整都可以获取一位整数
		decimal *= 10;
		int int_decimal = (int)decimal;
		//将得到的那个整数进行转换
		*buffer_temp = int_decimal + '0';
		buffer_temp++;
		//小数减去前面的整数就得到了新的小数
		decimal -= int_decimal;
		currentIndex++;
	}
	return buffer;
}
void main() {
	float number = 3.14f;
	char buffer[8] = { 0 };
	//实数转字符串实际用例中可以用sprintf来解决
	//sprintf(buffer, "%f", number);
	ftoa(number,buffer,4);
	printf("%s\n",buffer);
	system("pause");
}