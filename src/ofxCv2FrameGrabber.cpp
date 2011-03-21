/*
 *  ofxCv2FrameGrabber.cpp
 *  ofxOpenCv2
 *
 *  Created by Marynel Vazquez on 3/12/11.
 *  Copyright 2011 Robotics Institute. Carnegie Mellon University. All rights reserved.
 *
 */

#include "ofxCv2FrameGrabber.h"

/*! Constructor for capturing from device
	\param device device to capture from (0 is default camera)
 */
ofxCv2FrameGrabber::ofxCv2FrameGrabber(int device)
{
	if (!setUp(device))
		ofLog(OF_LOG_WARNING, "in ofxCv2FrameGrabber(int), could not initialize capturing device");

}

/*! Constructor for capturing from movie
	\param filename movie to capture from 
 */
ofxCv2FrameGrabber::ofxCv2FrameGrabber(string filename)
{
	if (!setUp(filename))
		ofLog(OF_LOG_WARNING, "in ofxCv2FrameGrabber(string), could not initialize capturing device");
}


/*! Destructor
 */
ofxCv2FrameGrabber::~ofxCv2FrameGrabber()
{}

/*! Set up capturing from device
	\param device device
	\return <a>true</a> if capturing was set up properly
 */
bool 
ofxCv2FrameGrabber::setUp(int device)
{
	cap.open(device);
	return cap.isOpened();
}

/*! Set up capturing from movie
	\param filename movie to capture from 
	\return <a>true</a> if capturing was set up properly
 */
bool 
ofxCv2FrameGrabber::setUp(string filename)
{
	cap.open(filename);
	return cap.isOpened();
}


/*! Capturing going on? 
	\return video capture object open?
 */
bool 
ofxCv2FrameGrabber::isCapturing()
{
	return cap.isOpened();
}

/*! Get new frame
	\return <true> if video capture object is opened
 */
bool 
ofxCv2FrameGrabber::getNewFrame()
{
	if (!cap.isOpened()) { return false; }
	
	Mat frame;
	cap >> frame;
	
	if (frame.cols != cvImage.cols || 
		frame.rows != cvImage.rows ||
		frame.channels() != cvImage.channels() ||
		frame.depth() != cvImage.depth())
	{
		cvImage.create(frame.rows, frame.cols, CV_MAKETYPE(CV_MAT_DEPTH(frame.depth()),frame.channels()));
	}
	cvtColor(frame, cvImage, CV_BGR2RGB);
	
	textureIsDirty = true;
	
	return true;
}
