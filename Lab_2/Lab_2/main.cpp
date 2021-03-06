#include <iostream>
#include <windows.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <opencv2/opencv.hpp> 

using namespace std;
using namespace cv;

Mat src, dst;

void printMenu()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << endl; cout << "\t======================= МЕНЮ =======================" << endl;
	cout << "\t\t\t" << "[1]" << " - СВЕРКА ИЗОБРАЖЕНИЯ ЛИНЕЙНЫМ ФИЛЬТРОМ" << endl;
	cout << "\t\t\t" << "[2]" << " - СГЛАЖИВАНИЕ ИЗОБРАЖЕНИЯ (blur, boxFilter, GaussianBlur, medianBlur)" << endl;
	cout << "\t\t\t" << "[3]" << " - ДИЛАТАЦИЯ И ЭРОЗИЯ ИЗОБРАЖЕНИЯ" << endl;
	cout << "\t\t\t" << "[4]" << " - ДЕТЕКТОР РЕБЕР КАННИ " << endl;
	cout << "\t\t\t" << "[5]" << " - ВЫРАВНИВАНИЕ ГИСТОГРАММЫ" << endl;
	cout << "\t\t\t" << "[0]" << " - ВЫХОД" << endl;
}

void filter(Mat *src, Mat *dst)
{
	const float kernelData[] = { -0.1f, 0.2f, -0.1f, 0.2f, 3.0f, 0.2f, -0.1f, 0.2f, -0.1f };
	const Mat kernel(3, 3, CV_32FC1, (float*)kernelData);
	filter2D(*src, *dst, -1, kernel);
}

void showImage(string winName, Mat *src)
{
	namedWindow(winName, CV_WINDOW_NORMAL);
	imshow(winName, *src);
}

int main()
{
	printMenu();
	src = imread("summer.jpg", 1);
	int choose = 0;
	for (;;)
	{
		cout << "\t\t\tВвод: "; cin >> choose;
		switch (choose)
		{
		case 0: return 0;
		case 1:
		{
			filter(&src, &dst);
			showImage("source", &src);
			showImage("filter", &dst);
		} break;
		case 2:
		{
			showImage("source", &src);
			blur(src, dst, Size(5, 5));
			showImage("blur", &dst);
			boxFilter(src, dst, 40, Size(10, 10), Point(-1, -1), true, BORDER_DEFAULT);
			showImage("boxFilter", &dst);
			GaussianBlur(src, dst, Size(5, 5), 4, 0, BORDER_DEFAULT);
			showImage("GaussianBlur", &dst);
			medianBlur(src, dst, 3);
			showImage("medianBlur", &dst);
		} break;
		case 3:
		{
			showImage("source", &src);
			erode(src, dst, Mat());
			showImage("erode", &dst);
			dilate(src, dst, Mat());
			showImage("dilate", &dst);
		} break;
		case 4:
		{
			showImage("source", &src);
			Canny(src, dst, 70, 260);
			showImage("Canny", &dst);
		} break;
		case 5:
		{
			showImage("source", &src);
			Mat grayImg;
			cvtColor(src, grayImg, CV_RGB2GRAY);
			showImage("grayImg", &grayImg);
			equalizeHist(grayImg, dst);
			showImage("equalizeHist", &dst);
		} break;
		default:
			cout << "\t\t\t|| [" << choose << "] - неизвестная команда ||" << endl; break;
		}
		waitKey();
		destroyAllWindows();
	}
	return 0;
}