/*
 *  ofxCv2ImageUtil.h
 *  ofxOpenCv2
 *
 *  Created by Marynel Vazquez on 3/13/11.
 *  Copyright 2011 Robotics Institute. Carnegie Mellon University. All rights reserved.
 *
 */

#ifndef OFXCV2_IMAGEUTIL
#define OFXCV2_IMAGEUTIL

#include "ofxCv2Image.h"

bool sameProperties(const Mat& mat1, const Mat& mat2); 
bool findCannyEdges(const Mat& input, Mat& output, double threshold1 = 1.0, double threshold2 = 0.0, int apertureSize = 3);
void findCannyEdges(const ofxCv2Image& input, ofxCv2Image& output, double threshold1 = 1.0, double threshold2 = 0.0, int apertureSize = 3);

#endif