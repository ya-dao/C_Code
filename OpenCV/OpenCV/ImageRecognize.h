#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<cv.h>
#include<highgui.h>

typedef struct shapeStruct {
	int shapeName;
	int colorName;
}shape;

int isCircle(CvSeq* seq, CvPoint point, int radius);
int getVertexCount(CvSeq* seq);
void recognizeColor(IplImage* src, int minX, int minY, int maxX, int maxY, int colorInfo[7]);
void getColorCount(IplImage* src, int color[6]);
void getColorName(int colors[6], int colorInfo[7]);
void RecognizeShape();
void recognizeLicensePlate();

#define CIRCLE 1		//Ô²
#define TRIANGLE 2		//Èý½ÇÐÎ
#define RECTANGLE 3		//¾ØÐÎ

#define RED 1			//ºì
#define GREEN 2			//ÂÌ
#define BLUE 3			//À¶
#define CYAN 4			//Çà
#define YELLOW 5		//»Æ
#define PURPLE 6		//×Ï

char recongnize(int i, IplImage* image);
char recongnizeEnglishCharacter(IplImage* image);
char recongnizeIntegerCharacter(IplImage* image);
CvSeq* findContour(IplImage* src);
void RecognizeShape();

char recongnize(int i, IplImage* image);
char recongnizeEnglishCharacter(IplImage* image);
char recongnizeIntegerCharacter(IplImage* image);
CvSeq* findContour(IplImage* src);
void recognizeLicensePlate();