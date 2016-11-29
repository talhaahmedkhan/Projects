#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"

using namespace cv;
using namespace std;

int main()
{
	Mat myimage;                       //myimage object
	myimage = imread("image.jpg");  // load image using imread
	namedWindow("Original image"); 
	imshow("Original image", myimage);     // open a window to show original image

	Mat gray, edge, convertedimage;
	cvtColor(myimage, gray, CV_BGR2GRAY);  //Converts from one color space to another

	Canny(gray, edge, 50, 150, 3);  // Canny edge formula

	edge.convertTo(convertedimage, CV_8U);
	namedWindow("converted_image", CV_WINDOW_AUTOSIZE);
	imshow("converted_image", convertedimage);  // opens a new canny edge image

	waitKey(0);
	return 0;
}