
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

		livecamera.read(frame);		// Reading the frame from the video
		imshow("Live Video", frame);	//opening the live video feed

		cvtColor(frame, cannyImage, CV_BGR2GRAY);    // Converts from one one color space to another
		Canny(frame, cannyImage, 100, 200, 3);		//  Canny edge formula
		imshow("Canny Transformation", cannyImage);	// opening Canny transformation 

		vector<Vec2f> lines;
		HoughLines(cannyImage, lines, 1, CV_PI / 180, 100, 0, 0);       // Hough transformation formula to draw lines on the images

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
			line(frame, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
			Point2f point1 = (pt2.x + pt1.x)*0.5;
			Point2f point2 = (pt2.y + pt1.y)*0.5;

			line(frame, point1, point2, Scalar(1, 3, 2), 6, CV_AA);


		}


		imshow("Hough Transformation", frame);  //opening the hough transformation 


		findContours(cannyImage, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
		RNG rng(12345);
		cv::blur(cannyImage, cannyImage, cv::Size(5, 5), cv::Point(-1, -1));
		cv::threshold(cannyImage, cannyImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);



		/// Get the moments
		vector<Moments> mu(contours.size());
		for (int i = 0; i < contours.size(); i++)
		{
			mu[i] = moments(contours[i], false);
		}

		///  Get the mass centers:
		vector<Point2f> mc(contours.size());
		for (int i = 0; i < contours.size(); i++)
		{
			mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		}

		/// Draw contours
		Mat drawing = Mat::zeros(cannyImage.size(), CV_8UC3);
		for (int i = 0; i< contours.size(); i++)
		{
			Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
			drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
			circle(drawing, mc[i], 4, color, -1, 8, 0);
		}

		/// Show in a window
		namedWindow("Contours", CV_WINDOW_AUTOSIZE);
		imshow("Contours", drawing);


		if (waitKey(120) >= 0)
			break;

	}


	return 0;
}