#include <iostream>
#include <windows.h>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int filterCode = -1;

void showImage(string winName, Mat *src)
{
	namedWindow(winName, CV_WINDOW_NORMAL);
	imshow(winName, *src);
}

void checkPressedButton()
{
	char c = waitKey(30);
	if (c == 13) { // Enter
		filterCode++;
		if (filterCode > 3)
		{
			filterCode = -1;
		}
	}
}

int main(int, char**)
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		return -1;
	}

	Mat frame, resultFrame;
	while (true)
	{
		cap >> frame;
		checkPressedButton();
		switch (filterCode)
		{
		case 0:
		{
			showImage("Web cam", &frame);
		}
		case 1: {
			Sobel(frame, resultFrame, CV_16S, 1, 0); // по Ox
			convertScaleAbs(resultFrame, resultFrame);
			showImage("Web cam", &resultFrame);
		} break;
		case 2: {
			Laplacian(frame, resultFrame, CV_16S);
			convertScaleAbs(resultFrame, resultFrame);
			showImage("Web cam", &resultFrame);
		} break;
		case 3: {
			Canny(frame, resultFrame, 70, 260);
			showImage("Web cam", &resultFrame);
		} break;
		default:
		{
			showImage("Web cam", &frame);
		}		
		}
	}
	return 0;
}