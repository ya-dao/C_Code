#define _CRT_SECURE_NO_WARNINGS
#include "SqList.h"

void main(){
	int flag = 0;
	SqList *sqList = (SqList*)malloc(sizeof(SqList));
	init(sqList,10);
	int operateElement = -1;
	while (1) {
		int action = 0;
		printf("功能选项(输入序号):\n");
		printf("0.退出 1.插入 2.删除 3.修改 4.查询\n");
		scanf("%d",&action);
		switch (action)
		{
		case 0:
			flag = 1;
			break;
		case 1:
			printf("需插入元素:\n");
			scanf("%d", &operateElement);
			printf("指定插入位置(-1默认为最后一个):\n");
			int insertIndex = -1;
			scanf("%d", &insertIndex);
			insert(sqList, insertIndex, operateElement);
			display(sqList);
			break;
		case 2:
			printf("1.删除指定元素值 2.删除某一范围\n");
			int deleteOption = 1;
			scanf("%d",&deleteOption);
			if (deleteOption == 1)
			{
				printf("输入指定的元素值:\n");
				scanf("%d", &operateElement);
				deleteByValue(sqList, operateElement);
			}
			else {
				printf("输入指定的范围(逗号分隔):\n");
				int start = 0, end = 0;
				scanf("%d,%d", &start,&end);
				deleteByRange(sqList, start,end);
			}
			display(sqList);
			break;
		case 3:
			printf("需修改元素:\n");
			scanf("%d", &operateElement);
			printf("进行修改的值:\n");
			int newElement = 0;
			scanf("%d", &newElement);
			alterElement(sqList, operateElement, newElement);
			display(sqList);
			break;
		case 4:
			printf("1.获取指定位置的值 2.获取指定值的位置 3.显示当前表\n");
			int queryOption = 1;
			scanf("%d", &queryOption);
			int result = 0;
			if (queryOption == 1)
			{
				printf("输入指定的位置:\n");
				int queryIndex = 0;
				scanf("%d", &queryIndex);
				result = getElement(sqList,queryIndex);
				printf("%d位置的值为:%d\n", queryIndex, result);
			}
			else if(queryOption == 2){
				printf("输入指定的值:\n");
				scanf("%d", &operateElement);
				result = getIndex(sqList, operateElement);
				printf("%d的下标为:%d\n",operateElement,result);
			}
			else{
				display(sqList);
			}
			break;
		default:
			break;
		}

		if (flag == 1)
		{
			break;
		}

		printf("\n\n");
	}

	system("pause");
}