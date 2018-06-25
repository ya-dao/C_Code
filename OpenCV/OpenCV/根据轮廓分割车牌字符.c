#include "ImageRecognize.h"

char* IntegerUrl[10] = {"../image/IntegerCharacter/no0.bmp","../image/IntegerCharacter/no1.bmp","../image/IntegerCharacter/no2.bmp",
						"../image/IntegerCharacter/no3.bmp","../image/IntegerCharacter/no4.bmp","../image/IntegerCharacter/no5.bmp",
						"../image/IntegerCharacter/no6.bmp","../image/IntegerCharacter/no7.bmp","../image/IntegerCharacter/no8.bmp",
						"../image/IntegerCharacter/no9.bmp"};

//里面没有I和O，车牌里面也没有这两个字母，为了防止跟1和0混淆,后面在处理的时候，由于缺少两个字母，匹配的下标可能会存在误差。
//如果匹配的下标小于I，则原数直接返回，如果大于I小于O，则需要加1，如果大于O，则需要加2返回
char* EnglishUrl[24]= {"../image/EnglishCharacter/A.bmp","../image/EnglishCharacter/B.bmp","../image/EnglishCharacter/C.bmp",
						"../image/EnglishCharacter/D.bmp","../image/EnglishCharacter/E.bmp","../image/EnglishCharacter/F.bmp",
						"../image/EnglishCharacter/G.bmp","../image/EnglishCharacter/H.bmp","../image/EnglishCharacter/J.bmp",
						"../image/EnglishCharacter/K.bmp","../image/EnglishCharacter/L.bmp","../image/EnglishCharacter/M.bmp",
						"../image/EnglishCharacter/N.bmp","../image/EnglishCharacter/P.bmp","../image/EnglishCharacter/Q.bmp",
						"../image/EnglishCharacter/R.bmp","../image/EnglishCharacter/S.bmp","../image/EnglishCharacter/T.bmp",
						"../image/EnglishCharacter/U.bmp","../image/EnglishCharacter/V.bmp","../image/EnglishCharacter/W.bmp",
						"../image/EnglishCharacter/X.bmp","../image/EnglishCharacter/Y.bmp","../image/EnglishCharacter/Z.bmp"};

void recognizeLicensePlate(){
	
	IplImage* src = cvLoadImage("+../image/plate1.jpg",CV_LOAD_IMAGE_ANYCOLOR);
	IplImage* graySrc = cvLoadImage("../image/plate1.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* binarySrc = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	
	cvThreshold(graySrc,binarySrc,140,255,CV_THRESH_BINARY);

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* seq;
	//这里我们需要字符整体分割出来，所以我们需要使用CV_RETR_CCOMP提取外轮廓，不要用list，因为list会包含内轮廓和外轮廓
	int contourCount = cvFindContours(binarySrc,storage,&seq,sizeof(CvContour),CV_RETR_CCOMP,CV_CHAIN_APPROX_NONE,cvPoint(0,0)) - 1;
	
	CvSeq* contours = seq;
	for(;contours->h_next != 0;contours = contours->h_next){
		CvRect rect = cvBoundingRect(contours,0);

		cvDrawRect(src,cvPoint(rect.x,rect.y),cvPoint(rect.x + rect.width , rect.y + rect.height),CV_RGB(255,0,0),1,8,0);
	}

	CvSeq* copyContours = seq;
	IplImage* splitCharacter[7];
	//这个数组是为了后面给分割出来的字符排序用的
	int minXArr[7];
	for(int i = 0;copyContours->h_next != 0;copyContours = copyContours->h_next,i++){
		int minX = 10000,minY = 10000,maxX = 0,maxY = 0;
		for(int j = 0;j < copyContours->total;j++){
			CvPoint* point = (CvPoint*)cvGetSeqElem(copyContours,j);
			if(point->x < minX){
				minX = point->x;
			}
			if(point->x > maxX){
				maxX = point->x;
			}
			if(point->y > maxY){
				maxY = point->y;
			}
			if(point->y < minY){
				minY = point->y;
			}
		}
		if(i < 7){
			int width = maxX - minX;
			int height = maxY - minY;
			splitCharacter[i] = cvCreateImage(cvSize(width,height),graySrc->depth,graySrc->nChannels);
			minXArr[i] = minX;
			//将字符分割出来写入对应的图片数组里面
			cvSetImageROI(graySrc,cvRect(minX,minY,width,height));
			cvCopy(graySrc, splitCharacter[i], NULL);
			cvResetImageROI(src);
		}
	}

	//先对存入的字符轮廓排个序，按minX的大小从小到大排
	for(int i = 0;i < 6;i++){
		for(int j = i + 1;j < 7;j++){
			if(minXArr[i] > minXArr[j]){
				int tempX = minXArr[i];
				minXArr[i] = minXArr[j];
				minXArr[j] = tempX;

				IplImage* temp = splitCharacter[i];
				splitCharacter[i] = splitCharacter[j];
				splitCharacter[j] = temp;
			}
		}
	}

	//将这些图片缩小到模板尺寸
	IplImage* resizeCharacter[7];
	for(int i = 0;i < 7;i++){
		resizeCharacter[i] = cvCreateImage(cvSize(20,40),graySrc->depth,graySrc->nChannels);
		cvResize(splitCharacter[i],resizeCharacter[i],CV_INTER_AREA);
	}

	for(int i = 0;i < 7;i++){
		char name[2];
		//itoa是将数字转换成字符串的函数，但是上面不要用char*，这是常量，不可变，不能被转换后赋值，需要用char[]数组
		_itoa(i,name,10);
		cvNamedWindow(name, CV_WINDOW_AUTOSIZE);
		cvShowImage(name,resizeCharacter[i]);
		printf("%s\n",name);
	}

	
	//开始识别
	//一个汉字要占两个字节，且默认后面有'\0'，所以数组的大小为内容+1。把国字赋值后后面的字母数字直接从下标2第三个字符'\0'处直接覆盖
	
	char results[9] = "国";
	for(int i = 1;i < 7;i++){
		results[i + 1] = recongnize(i,resizeCharacter[i]);
	}
	printf("以下车牌号中的内容为:\n%s\n",results);

	//recongnize(2,resizeCharacter[2]);
	
	cvNamedWindow("src", CV_WINDOW_AUTOSIZE);
	cvShowImage("src",src);
	
	cvWaitKey(0);
}

char recongnize(int i,IplImage* image){
	//先将这幅图进行二值化
	cvThreshold(image,image,150,255,CV_THRESH_BINARY);
	switch(i){
	/*case 0:		//直接返回固定不变的国字
		return "国";
		break;*/
	case 1:		//识别英文字符
		return recongnizeEnglishCharacter(image);
		break;	
	default:	//识别数字
		return recongnizeIntegerCharacter(image);
		break;	
	}
}

//采取逐像素匹配字母
char recongnizeEnglishCharacter(IplImage* image){
	IplImage* templates[24];
	//将所有的字符模板导入进来
	for(int i = 0;i < 24;i++){
		templates[i] = cvLoadImage(EnglishUrl[i],CV_LOAD_IMAGE_ANYCOLOR);
	}

	//逐像素去对比两个幅图像之间的差距
	double result[24];
	for(int i = 0;i < 24;i++){
		int differenceCount = 0;
		for(int j = 0;j < image->height;j++){
			unsigned char* srcData = (unsigned char*)image->imageData + j * image->widthStep;
			unsigned char* tempData = (unsigned char*)templates[i]->imageData + j * templates[i]->widthStep;
			for(int k = 0;k < image->width;k++){
				if(*(srcData + k) != *(tempData + k)){
					differenceCount++;
				}
			}
		}
		result[i] = differenceCount / 800.0; //因为result是double类型的，所以分子分母有一个必须是小数类型的，不然就为0了
	}

	//遍历结果集，找出差值最小的下标即为匹配字母，另外需要处理下下标因为少了两个字母导致的误差
	double min = 100;
	int index = 0;
	for(int i = 0;i < 24;i++){
		if(result[i] < min){
			min = result[i];
			index = i;
		}
	}

	//处理误差
	if((index + 'A') > 'I' && (index + 'A') < 'O'){
		index++;
	}else if((index + 'A') > 'O'){
		index += 2;
	}

	//用完还是要释放这些模板图片
	for(int i = 0;i < 24;i++){
		cvReleaseImage(&templates[i]);
	}
	return 'A' + index;
}

//采取逐像素匹配数字
char recongnizeIntegerCharacter(IplImage* image){
	//将这些模板图片导入进一个数组方便后面进行匹配
	IplImage* templates[10];
	for(int i = 0;i < 10;i++){
		templates[i] = cvLoadImage(IntegerUrl[i],CV_LOAD_IMAGE_GRAYSCALE);
	}	

	//对所有图片进行逐像素匹配
	double result[10] = { 0.0 };
	for(int i = 0;i < 10;i++){
		int differenceCount = 0;
		for(int j = 0;j < templates[i]->height;j++){
			unsigned char* srcData = (unsigned char*)image->imageData + j * image->widthStep;
			unsigned char* templateData = (unsigned char*)templates[i]->imageData + j * templates[i]->widthStep;
			for(int k = 0;k < templates[i]->width;k++){
				if(*(srcData + k) != *(templateData + k)){
					differenceCount++;
				}
			}
		}
		result[i] = differenceCount / 800.0;
	}
	//遍历结果集找出差距最小的那一个模板即为匹配字符
	double min = 100;
	int index = 0;
	for(int i = 0;i < 10;i++){
		if(result[i] < min){
			min = result[i];
			index = i;
		}
	}
	
	//用完还是要释放一下这些图片
	for(int i = 0;i < 10;i++){
		cvReleaseImage(&templates[i]);
	}
	return index + '0';
}


/*HU矩这些模板匹配都是卵的，不好用
char recongnizeIntegerCharacter(IplImage* image){
	CvSeq* srcSeq;
	srcSeq = findContour(image);

	//将这些模板图片导入进一个数组方便后面进行匹配
	IplImage* templates[10];
	for(int i = 0;i < 10;i++){
		templates[i] = cvLoadImage(IntegerUrl[i],CV_LOAD_IMAGE_GRAYSCALE);
	}

	//把这些模板图片的轮廓序列全部弄出来
	CvSeq* seqs[10];
	for(int i = 0;i < 10;i++){
		seqs[i] = findContour(templates[i]);
	}
	//算出所有模板与需要进行匹配的图片的hu矩的差
	double results[10];
	for(int i = 0;i < 10;i++){
		results[i] = cvMatchShapes(srcSeq,seqs[i],2);
	}
	//找出差距最小的那一个就是匹配成功的，下标即为对应的匹配数字
	double min = 10000;
	int index = 0;
	for(int i = 0;i < 10;i++){
		if(results[i] < min){
			min = results[i];
			index = i;
		}
		printf("min:%lf,i:%d\n",results[i],i);
	}
			printf("最相近的是:%d\n",index);
	//将数字转换为字符需要加上字符0即为对应字符
	return index + '0';
}

//寻找轮廓
CvSeq* findContour(IplImage* src){
	IplImage* image = cvCreateImage(cvGetSize(src),8,1);
	cvCopy(src,image);
	
	cvThreshold(image,image,140,255,CV_THRESH_BINARY);

	cvNamedWindow("test");
	cvShowImage("test",image);
	
	cvWaitKey(0);

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* seq;
	cvFindContours(image,storage,&seq,sizeof(CvContour),CV_RETR_CCOMP,CV_CHAIN_APPROX_NONE,cvPoint(0,0));
	cvReleaseImage(&image);
	return seq;
}
*/