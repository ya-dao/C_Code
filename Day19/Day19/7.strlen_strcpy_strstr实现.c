#include<stdio.h>
#include<stdlib.h>
int myStrlen(const char *str) {
	if (str == NULL)
	{
		return -1;
	}
	int length = 0;
	for (char *p = str; *p; p++)
	{
		length++;
	}
	return length;
}
char* myStrcpy(char *destination,const char *source) {
	if (destination == NULL || source == NULL)
	{
		return NULL;
	}
	char *temp = destination;
	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}
	return temp;
}
int myStrstr(const char *destination,const char *source) {
	if (destination == NULL || source == NULL)
	{
		return -1;
	}
	int sourceIndex = 0;
	while (*(source + sourceIndex) != '\0')
	{
		int i = 0;
		while (*(destination + i) == *(source + sourceIndex + i))
		{
			i++;
		}
		if (*(destination + i) == '\0')
		{
			return 1;
		}
		if (i == 0)
		{
			sourceIndex += i + 1;
		}
		else {
			sourceIndex += i;
		}
	}
	return 0;
}
int myStrstr2(const char *destination, const char *source) {
	int sourceLength = myStrlen(source);
	int destinationLength = myStrlen(destination);
	int flag = 1;
	for (int i = 0; i < sourceLength - destinationLength; i++)
	{
		//假设这段和目标串相等
		flag = 1;
		for (int j = 0; j < destinationLength; j++)
		{
			if (*(destination + j) != *(source + i + j))
			{
				flag = 0;
				break;
			}
		}
	}
	return flag;
}
void main() {
	char *p1 = "abcde";
	char p2[8] = { 0 };
	char *p3 = "bced";
	
	int length = myStrlen(p1);
	printf("strlen = %d\n", length);

	printf("%s\n", myStrcpy(p2, p1));

	printf("%d\n", myStrstr(p3, p1));
	printf("%d\n", myStrstr2(p3, p1));
	system("pause");
}