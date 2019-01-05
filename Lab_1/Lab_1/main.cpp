#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img1 = imread("city.jpg");
	Mat img2 = imread("city.jpg", 0);
	namedWindow("image1", WINDOW_NORMAL);
	namedWindow("image2", WINDOW_NORMAL);
	imshow("image1", img1);
	imshow("image2", img2);
	waitKey(0);
	return 0;
}