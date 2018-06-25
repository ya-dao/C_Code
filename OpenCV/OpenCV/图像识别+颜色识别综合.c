#include "ImageRecognize.h"

void RecognizeShape() {

	shape simpleShapes[15];
	int shapeCount = 0;

	char* color[6] = {"红","绿","蓝","青","黄","紫"};
	int circleCount = 0;
	int rectangleCount = 0;
	int triangleCount = 0;
	//图片名
	char *fileName = "./src1.jpg";
	//阀值
	int threshold = 250;

	IplImage* src = cvLoadImage(fileName,CV_LOAD_IMAGE_COLOR);
	IplImage* grayImage = cvLoadImage(fileName,CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* binaryImage = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
	IplImage* contourImage = cvCreateImage(cvGetSize(src),IPL_DEPTH_32F,3);

	//这幅图阀值大于160所有轮廓才能全部看到
	cvThreshold(grayImage,binaryImage, threshold,255,CV_THRESH_BINARY);

	/*cvNamedWindow("test");
	cvShowImage("test", binaryImage);
	cvWaitKey(0);*/

	//寻找该图的轮廓
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* seq;
	int contours = cvFindContours(binaryImage,storage,&seq,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_NONE,cvPoint(0,0)) - 1;

	//用于多边形逼近的内存和序列
	CvMemStorage* storage1 = cvCreateMemStorage(0);
	CvSeq* vertexSeq;

	for(;seq->h_next != 0;seq = seq->h_next){
		int minX = 10000,maxX = 0;
		int minY = 10000,maxY = 0;
		int centralPointY = 0;
		for(int i = 0; i < seq->total;i++){
			CvPoint* point = (CvPoint*)cvGetSeqElem(seq,i);
			cvSet2D(contourImage,point->y,point->x,CV_RGB(255,0,0));
			
			//在这里将这个轮廓里面最小和最大的X和Y坐标全部统计出来,由于只想要圆的中心点，所以
			if(point->x < minX){
				minX = point->x;
				centralPointY = point->y;
			}
			if(point->x > maxX){
				maxX = point->x;
			}
			if(point->y < minY){
				minY = point->y;
			}
			if(point->y > maxY){
				maxY = point->y;
			}
		}
		//算出这两个相隔这最远的点的距离并除以2作为判断是否为圆的半径
		int radius = (maxX - minX) / 2;
		
		//有了半径之后就可以取出该轮廓的中心点
		//(特指如果是圆的情况下,不是圆肯定不会是中心点。当然这个中心点是有误差的，由于轮廓是像素点，中心点的Y坐标会上下浮动几个像素点)
		CvPoint centralPoint = cvPoint(minX + radius,centralPointY);
		cvSet2D(contourImage,centralPointY,centralPoint.x,CV_RGB(255,0,0));
		
		//判断是否为圆
		int isCircleResult = isCircle(seq,centralPoint,radius);
		int shapeName = 0;
		int colorInfo[7] = {0};

		if(isCircleResult){
			
			circleCount++;
			shapeName = 1;

			//当形状判断完之后直接对其进行颜色识别
			recognizeColor(src,minX,minY,maxX,maxY,colorInfo);
		}else{
			//不为圆则进行多边形逼近,得到顶点数目
			vertexSeq = cvApproxPoly(seq,sizeof(CvContour),storage,CV_POLY_APPROX_DP,cvContourPerimeter(seq) * 0.02,0);
			int vertexCount = getVertexCount(vertexSeq);
			
			if(3 == vertexCount){
				
				triangleCount++;
				shapeName = 2;

				//当形状判断完之后直接对其进行颜色识别
				recognizeColor(src,minX,minY,maxX,maxY,colorInfo);
			}else if(4 == vertexCount){
				//这里要先进行颜色识别，如果是一个颜色则为矩形，如果有两种以上的颜色则需要进行下一步处理
				recognizeColor(src,minX,minY,maxX,maxY,colorInfo);
				
				if(1 == colorInfo[0]){
					rectangleCount++;
					shapeName = 3;
				}else if(2 == colorInfo[0]){
					triangleCount += 2;
					shapeName = 2;
				}
			}
		}
		
		//对识别出来的图形形状和颜色进行保存，便于后面清点
		if(1 == colorInfo[0]){
			simpleShapes[shapeCount].shapeName = shapeName;
			simpleShapes[shapeCount].colorName = colorInfo[1];
			shapeCount++;
		}else if(2 == colorInfo[0]){
			simpleShapes[shapeCount].shapeName = shapeName;
			simpleShapes[shapeCount].colorName = colorInfo[1];
			shapeCount++;
			simpleShapes[shapeCount].shapeName = shapeName;
			simpleShapes[shapeCount].colorName = colorInfo[2];
			shapeCount++;
		}
	}

	//测试 清点里面红色三角形的个数
	int count = 0;
	for(int i = 0;i < shapeCount;i++){
		if(2 == simpleShapes[i].shapeName && 0 == simpleShapes[i].colorName){
			count++;
		}
	}
	printf("共%d个红色三角形\n",count);

	cvNamedWindow("contourImage",CV_WINDOW_AUTOSIZE);
	cvShowImage("contourImage",contourImage);

	cvWaitKey(0);
}
//该函数用来判断是否为圆，如果是则返回1，否则返回0
int isCircle(CvSeq* seq,CvPoint centralPoint,int radius){
	//运用求距离的公式来算出每个点到中心点的距离是否大致相等(误差控制在(10-20)的范围中
	for(int i = 0;i < seq->total;i++){
		CvPoint* point = (CvPoint*)cvGetSeqElem(seq,i);
		int x1 = centralPoint.x;
		int x2 = point->x;

		int y1 = centralPoint.y;
		int y2 = point->y;

		int distance = (int)sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
		
		if(abs(radius - distance) > 20){
			return 0;
		}
	}
		
	return 1;
}

//将传入的序列进行遍历，得到顶点数并返回
int getVertexCount(CvSeq* seq){
	int count = 0;
	for(int i = 0;i < seq->total;i++){
		
		count++;
	}
	return count;
}

//获取该轮廓内的颜色
void recognizeColor(IplImage* src,int minX,int minY,int maxX,int maxY,int colorInfo[7]){
	int width = maxX - minX;
	int	height = maxY - minY;

	cvSetImageROI(src,cvRect(minX,minY,width,height));
	IplImage* copySrc = cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,3);
	cvCopy(src,copySrc,NULL);	
	cvResetImageROI(src);
	
	/*
	cvNamedWindow("test");
	cvShowImage("test",copySrc);
	cvWaitKey(0);
	*/
	
	int colors[6] = {0};		//这里存入每个颜色出现的次数,下标对应颜色顺序出现的次数
	getColorCount(copySrc,colors);
	getColorName(colors,colorInfo);
}

//识别出对应图像中有几种颜色，并识别出具体颜色。返回一个数组，里面按顺序存入颜色名
void getColorCount(IplImage* src,int colors[6]){
	int nChannels = src->nChannels;
	int widthStep = src->widthStep;
	char* imageData = src->imageData;

	for(int i = 0;i < src->height;i++){
		unsigned char* row = (unsigned char*)(imageData + i * widthStep);
		for(int j = 0;j < src->width;j++){
			int b = *(row + (j * nChannels + 0));
			int g = *(row + (j * nChannels + 1));
			int r = *(row + (j * nChannels + 2));

			// 允许误差,只要满足需要判断的那种颜色值大于150,其他颜色小于50,基本斗还是那种颜色.这个值的思路勒是借鉴的那边提供的源代码.
			if (150 <= r && g <= 90 && b <= 90) { // 判别红色
				colors[0]++;
			}
			else if (r <= 90 && 150 <= g && b <= 90) { // 判别绿色
				colors[1]++;
			}
			else if (r <= 90 && g <= 90 && 150 <= b) { // 判别蓝色
				colors[2]++;
			}
			else if (r <= 90 && 150 <= g && 150 <= b) { // 判别青色
				colors[3]++;
			}
			else if (150 <= r && 150 <= g && b <= 90) { // 判别黄色
				colors[4]++;
			}
			else if (150 <= r && g <= 90 && 150 <= b) { // 判别紫色
				colors[5]++;
			}
		}
	}
}

//从前一函数获取统计的颜色出现的次数并进行统计存入第一个下标,后面的按
void getColorName(int colors[6],int colorInfo[7]){
	int colorCount = 0;

	int j = 1;
	for(int i = 0;i < 6;i++){
		if(0 != colors[i]){
			//printf("j:%d,i:%d\n",j,i);
			colorCount++;
			colorInfo[j++] = i;
		}
	}
	colorInfo[0] = colorCount;
}
