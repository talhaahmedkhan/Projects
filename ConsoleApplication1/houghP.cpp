#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture livecamera(0);     // Fetching the live feed from the webcam

	std::vector < std::vector < cv::Point > >contours;
	vector<Vec4i> hierarchy;

	if (!livecamera.isOpened()) {
		cout << "cannot open camera";      // Webcam not opened 
	}

	while (true)
	{
		Mat cannyImage;	// cannyImage variable that is to be used in the hough transformation 
		Mat frame;		// frame variable from the video camera that is to be processed 
		Mat destination;
		livecamera.read(frame);		// Reading the frame from the video
		imshow("Live Video", frame);	//opening the live video feed

		Canny(frame, destination, 100, 200, 3);		//  Canny edge formula
		cvtColor(destination, cannyImage, CV_GRAY2BGR);    // Converts from one one color space to another
		imshow("Canny Transformation", cannyImage);	// opening Canny transformation 

		vector<Vec4i> lines;
		lines.reserve(1000);

		try{
			HoughLinesP(destination, lines, 1, CV_PI / 180, 80, 80,5);
		}
		catch (...) {

		}
		for (size_t i = 0; i < lines.size(); i++)
		{
			Vec4i l = lines[i];
			line(cannyImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
		}

		
	imshow("Hough Transformation", cannyImage);  //opening the hough transformation

	if (waitKey(120) >= 0)
		break;

}


return 0;
}