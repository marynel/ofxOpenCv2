/*
 *  ofxCv2ImageUtil.cpp
 *  ofxOpenCv2
 *
 *  Created by Marynel Vazquez on 3/13/11.
 *  Copyright 2011 Robotics Institute. Carnegie Mellon University. All rights reserved.
 *
 */

#include "ofxCv2ImageUtil.h"

/*! Check if two Mat variables share the same properties
	\param mat1 one mat
	\param mat2 another mat
	\return <a>true</a> if <a>mat1</a> and <a>mat2</a> have the same size and type
 */
bool sameProperties(const Mat& mat1, const Mat& mat2)
{
	return 
	mat1.cols == mat2.cols &&
	mat1.rows == mat2.rows &&
	mat1.type() == mat2.type();
}

/*! Find Canny edges
	\param input input (mat) image (must be color or gray 8-bit image)
	\param output edges (mat) image (single channel)
	\param threshold1 minimum threshold 
	\param threshold2 maximum threshold
	\param apertureSize aperture size for Sobel operator
	\return <a>true</a> if edges were computed successfully
 
	The maximum threshold is set to three times the value of
	<a>threshold1</a>, unless <a>threshold2</a> is greater than 0.
	 
	\note See OpenCV reference for an explanation on the thresholds
	and aperture size.
 */
bool findCannyEdges(const Mat& input, Mat& output, 
					double threshold1, double threshold2, int apertureSize)
{
	// check input type
	if (input.type() != CV_8UC1 &&
		input.type() != CV_8UC3)
	{
		ofLog(OF_LOG_WARNING, "in findCannyEdges, input image format is invalid");
		return false;
	}
	
	// set threshold2 if necessary
	if (threshold2 <= 0.0) threshold2 = threshold1*3;
	
	// create output image
	if (output.empty() || 
		!sameProperties(input, output))
	{
		output.create(input.rows, 
					  input.cols, 
					  CV_MAKETYPE(CV_MAT_DEPTH(input.depth()),1));
	}
	
	// convert input image to single channel if necessary
	Mat gray;
	if (input.channels() == 3)
	{
		gray.create(input.rows, 
					input.cols, 
					CV_MAKETYPE(CV_MAT_DEPTH(input.depth()),1));
		cvtColor(input, gray, CV_RGB2GRAY);
	}
	else {
		gray = input;
	}
		
	// find edges
	Canny(gray, output, threshold1, threshold2, apertureSize);
	return true;
}

/*! Find Canny edges
	\param input input ofxcv2 image (must be color or gray 8-bit image)
	\param output edges ofxcv2 image (single channel)
	\param threshold1 minimum threshold 
	\param threshold2 maximum threshold
	\param apertureSize aperture size for Sobel operator
 
	The maximum threshold is set to three times the value of
	<a>threshold1</a>, unless <a>threshold2</a> is greater than 0.
	
	\note See OpenCV reference for an explanation on the thresholds
	and aperture size.
 */
void 
findCannyEdges(const ofxCv2Image& input, ofxCv2Image& output, 
			   double threshold1, double threshold2, int apertureSize)
{
	Mat edges;
	if (findCannyEdges(input.cvImage, edges, 
					   threshold1, threshold2, apertureSize))
		output.setFromMat(edges);
}
