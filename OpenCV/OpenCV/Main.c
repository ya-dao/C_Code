#include "ImageRecognize.h"

int main() {
	while (1) {
		printf("看形状的演示按1,车牌的演示按2.\n");
		int option = 0;
		scanf("%d",&option);
		if (option == 1)
		{
			RecognizeShape();
		}
		else if(option == 2){
			recognizeLicensePlate();
		}
		else
		{
			printf("听话,莫搞事!\n");
		}
	}
	return 0;
}