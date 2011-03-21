/*
 *  ofxCv2Image.h
 *  ofxOpenCv2
 *
 *  Created by Marynel Vazquez on 3/12/11.
 *  Copyright 2011 Robotics Institute. Carnegie Mellon University. All rights reserved.
 *
 */

#ifndef OFXCV2_IMAGE
#define OFXCV2_IMAGE

#include "ofxCv2Constants.h"

/*! OpenCV2 image container. There's no more need 
	for tons of allocations as in OpenCV1...
	
	OpenCV Mat image is public. 
 
	\note ROI is not supported for the time being.
 */
class ofxCv2Image
{
public:
	
	Mat cvImage;				//!< opencv image
	ofTexture tex;				//!< internal texture
	bool textureIsDirty;		//!< texture needs to be reloaded
	
	ofxCv2Image();
	ofxCv2Image(Mat& image);
	virtual ~ofxCv2Image();
	
	virtual void clear();
	virtual float getWidth();
	virtual float getHeight();
	virtual bool isUnset();
	
	virtual void setFromPixels( unsigned char* pixels, int w, int h, int t );
	void setFromPixels( unsigned char* pixels, int w, int h, int d, int c);
	virtual void setFromMat( const Mat& mat ); 
	
	// operators
	ofxCv2Image& operator=(const ofxCv2Image& image);
	
	// draw
	virtual void draw( float x, float y, float w, float h);
	virtual void draw( float x, float y );
	void updateTexture();
	
	/*! OpenGL representation of image depth
		\return depth
	 */
	inline int glDepth()
	{
		int gldepth = 0;
		
		switch (cvImage.depth()) {
			case CV_8U:
				gldepth = GL_UNSIGNED_BYTE;
				break;
			case CV_32F:
				gldepth = GL_FLOAT;
				break;
			case CV_64F:
				gldepth = GL_DOUBLE;
				break;
			default:
				ofLog(OF_LOG_ERROR, "in glDepth, non-standard depth");
				break;
		}
		
		return gldepth;
	}
	
	/*! OpenGL representation of the number of image channels
		\return number of channels
	 */
	inline int glChannels()
	{
		int glchannels = 0;
		switch (cvImage.channels()) {
			case 3:
				glchannels = GL_RGB;
				break;
			case 1:
				glchannels = GL_LUMINANCE;
				break;
			default:
				ofLog(OF_LOG_ERROR, "in glChannels, non-standard number of channels");
				break;
		}
		return glchannels;
	}
	
};

#endif