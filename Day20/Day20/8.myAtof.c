#include<stdio.h>
#include<stdlib.h>
float myAtof(char *p) {
	//先判空
	if (p == NULL)
	{
		return 0.0f;
	}
	char *value = p;
	float result = 0.0f;
	int flag = 1;
	//判断符号位
	if (*value == '-')
	{
		flag = -1;
		value++;
	}
	//逐个取出字符进行转化,结束符'\0'ASCII为0,而字符'0'ASCII码为48
	//判断当前是处理小数部分还是整数部分
	int isInteger = 1;
	//小数点的基数,第一位*0.1,第二位*0.01
	float radix = 0.1f;
	while (*value != 0)
	{
		if ((*value < '0' || *value >'9') && *value != '.')
		{
			return 0.0f;
		}
		//遇到小数点跳过本次循环去处理小数部分
		if (*value == '.')
		{
			//跳过小数点
			value++;
			isInteger = 0;
			continue;
		}
		if (isInteger == 1)
		{
			result *= 10.f;
			result += (*value) - '0';
		}
		else
		{
			float temp = (*value - '0') * radix;
			result += temp;
			radix *= 0.1f;
		}
		value++;
	}
	return result * flag;
}
void main() {
	char *p = "-3.1004";
	//float result = atof(p);
	float result = myAtof(p);
	printf("%f\n",result);
	system("pause");
}