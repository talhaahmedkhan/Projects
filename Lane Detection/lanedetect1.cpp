#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"

using namespace cv;
using namespace std;

int main()
{
	Mat myimage;                       //myimage object
	myimage = imread("image.png");  // load image using imread
	namedWindow("Original image");
	imshow("Original image", myimage);     // open a window to show original image


	Mat destination, houghdestination;
	Canny(myimage, destination, 50, 200, 3);  // Converts the original image to the canny image and puts it in destination object

	vector<Vec2f> lines;
	HoughLines(destination, lines, 1, CV_PI / 180, 100, 0, 0);

	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(houghdestination, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
	}

	namedWindow("Canny_image", CV_WINDOW_AUTOSIZE);
	imshow("Canny_image", destination);

	namedWindow("Hough_Transformation", CV_WINDOW_AUTOSIZE);
	imshow("Hough_Transformation", houghdestination);


	waitKey(0);
	return 0;

}
