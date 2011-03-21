/*
 *  ofxCv2FrameGrabber.h
 *  ofxOpenCv2
 *
 *  Created by Marynel Vazquez on 3/12/11.
 *  Copyright 2011 Robotics Institute. Carnegie Mellon University. All rights reserved.
 *
 */

#ifndef OFXCV2_FRAMEGRABBER
#define OFXCV2_FRAMEGRABBER

#include "ofxCv2Image.h"

/*! OpenCv2 frame grabber 
	\note OpenCv2 was compiled with QuickTime support for
	this task (not sure how this works in platforms different
	than OSX)
 */
class ofxCv2FrameGrabber : public ofxCv2Image
{
public:
	
	VideoCapture cap;			//!< video capture
	
	ofxCv2FrameGrabber(int device = 0);
	ofxCv2FrameGrabber(string filename);
	~ofxCv2FrameGrabber();
	
	bool setUp(int device);
	bool setUp(string filename);
	
	bool isCapturing();
	
	bool getNewFrame();
	
	
};

#endif