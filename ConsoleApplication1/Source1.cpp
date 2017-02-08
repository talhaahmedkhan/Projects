
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

	if (!livecamera.isOpened()) {
		cout << "cannot open camera" ;      // Webcam not opened 
	}

	while (true) 
	{
		Mat cannyImage;	// cannyImage variable that is to be used in the hough transformation 
		Mat frame;		// frame variable from the video camera that is to be processed 

		livecamera.read(frame);		// Reading the frame from the video
		imshow("Live Video",frame);	//opening the live video feed

		cvtColor(frame, cannyImage, CV_BGR2GRAY);    // Converts from one one color space to another
		Canny(frame, cannyImage, 100, 200, 3);		//  Canny edge formula
		imshow("Canny Transformation", cannyImage);	// opening Canny transformation 
			
		vector<Vec2f> lines;
		HoughLines(cannyImage, lines, 1, CV_PI / 180, 80, 5, 0);       // Hough transformation formula to draw lines on the images

		vector<Vec2f> cart_lines; //slope, b param, y = [0] * x + [1]

		if (lines.size() != 2) {
			continue;
		}

		for (size_t i = 0; i < lines.size(); i++) {
			double rho = lines[i][0],theta = lines[i][1];				       // rho variable is the distance resolution in pixels	
																	   // theta variable is angle resolution in radians
			Point pt1, pt2;
			
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			pt1.x = cvRound(x0 + 1000 * (-b));
			pt1.y = cvRound(y0 + 1000 * (a));
			pt2.x = cvRound(x0 - 1000 * (-b));
			pt2.y = cvRound(y0 - 1000 * (a));
			line(frame, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);

			
			Vec2f cart_line;
			cart_line[0] = (-cos(theta) / sin(theta));
			cart_line[1] = rho / sin(theta);

			cart_lines.push_back(cart_line);
		}

		Vec2f frame_center; frame_center[0] = livecamera.get(3)/2 ; frame_center[1] = livecamera.get(4) / 2;

		Vec2f right_lane;
		Vec2f left_lane;

		if (cart_lines[0][0] < cart_lines[1][0]) {
			right_lane = cart_lines[0];
			left_lane = cart_lines[1];
		}
		else {
			right_lane = cart_lines[1];
			left_lane = cart_lines[0];
		}


		Point intercept_right; 
		intercept_right.y = frame_center[1];
		intercept_right.x = (frame_center[1] - right_lane[1]) / right_lane[0];

		Point intercept_left;
		intercept_left.y = frame_center[1];
		intercept_left.x = (frame_center[1] - left_lane[1]) / left_lane[0];

		std::cout << "intercept_right: " << intercept_right.x << ", " << intercept_right.y << "\n";
		std::cout << "intercept_left: " << intercept_left.x << ", " << intercept_left.y << "\n";
		imshow("Hough Transformation", frame);  //opening the hough transformation 

		
		if (waitKey(120) >= 0)
			break;

	}


	return 0;
}