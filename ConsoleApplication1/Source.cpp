#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()

{
	Mat myimage = imread("image.png", 0);      // Reading the original image
	
	if (myimage.empty()) {						// If there is no image it will return nothing
		cout << "can't open file" << endl;
		return -1;
		}

	Mat cannyimage; 
	Canny(myimage, cannyimage, 50, 200, 3);     // Canny edge formula

	Mat cannyconverted,edge; 
	cvtColor(cannyimage, cannyconverted, CV_GRAY2BGR);   // Converts from one one color space to another
	
	imshow("converted_image using Canny", cannyconverted);  // Displays the canny image

	vector<Vec2f> lines;
	HoughLines(cannyimage, lines, 1, CV_PI / 180, 100, 0, 0);       // Hough transformation to draw lines on the images

	for (size_t i = 0; i < lines.size(); i++) {
		double rho = lines[i][0], theta = lines[i][1];              // rho variable is the distance resolution in pixels	
																	// theta variable is angle resolution in radians
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cannyconverted, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
	}
	
	imshow("Original Image", myimage);       // Shows original image
	imshow("Transformation using Hough technique", cannyconverted);    // Displays images with the boundaries made by lines

	waitKey();

	return 0;
}