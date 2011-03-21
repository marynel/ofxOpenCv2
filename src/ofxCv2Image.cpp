/*
 *  ofxCv2Image.cpp
 *  ofxOpenCv2
 *
 *  Created by Marynel Vazquez on 3/12/11.
 *  Copyright 2011 Robotics Institute. Carnegie Mellon University. All rights reserved.
 *
 */

#include "ofxCv2Image.h"

/*! Constructor
 */
ofxCv2Image::ofxCv2Image()
{
	clear();
}

/*! Constructor
	\param image input mat
 */
ofxCv2Image::ofxCv2Image(Mat& image)
{
	image.copyTo(cvImage);
	textureIsDirty = true;
}

/*! Destructor
 */
ofxCv2Image::~ofxCv2Image()
{}

/*! Clear image
 */
void 
ofxCv2Image::clear()
{
	cvImage = Mat::zeros(cvImage.rows,cvImage.cols,cvImage.type());
	textureIsDirty = true;
}

/*! Image width
	\return width
 */
float 
ofxCv2Image::getWidth()
{
	if (cvImage.empty())
		ofLog(OF_LOG_WARNING, "in getWidth, requesting width of unset image");
	
	return cvImage.cols;
}

/*! Image height
	\return height
 */
float 
ofxCv2Image::getHeight()
{
	if (cvImage.empty())
		ofLog(OF_LOG_WARNING, "in getHeight, requesting height of unset image");

	return cvImage.rows;
}

/*! Is image unset? (is there data?)
	\return <a>true</a> if no data has been stored
 */
bool 
ofxCv2Image::isUnset()
{
	return cvImage.empty();
}

/*! Set image from pixels data (dense unsigned char array)
	\param pixels pixel data
	\param w width
	\param h height
	\param t type in opencv format (e.g., CV_8UC1)
 */
void 
ofxCv2Image::setFromPixels( unsigned char* pixels, int w, int h, int t )
{
	cvImage = Mat::zeros(h, w, t);
	int channels = CV_MAT_CN(t);
	memcpy( cvImage.data, pixels, w*h*channels );
	textureIsDirty = true;
}

/*! Set image from pixels data (dense unsigned char array)
	\param pixels pixel data
	\param w width
	\param h height
	\param d depth (e.g., CV_8U)
	\param c channels (e.g., 3 for color image)
*/
void 
ofxCv2Image::setFromPixels( unsigned char* pixels, int w, int h, int d, int c)
{
	setFromPixels(pixels, w, h, CV_MAKETYPE(CV_MAT_DEPTH(d),c));
}

/*! Set image from Mat image
	\param mat image to copy data from
 */
void 
ofxCv2Image::setFromMat( const Mat& mat )
{
	if (mat.empty()) return;
	mat.copyTo(cvImage);
	textureIsDirty = true;
}

/*! Assignment operator
	\param image image to copy
 */
ofxCv2Image& 
ofxCv2Image::operator=(const ofxCv2Image& image)
{
	if (this != &image)
	{
		image.cvImage.copyTo(cvImage);
		tex = image.tex;
		textureIsDirty = image.textureIsDirty;
	}
	
	return *this;
}

/*! Draw image
	\param x horizontal displacement
	\param y vertical displacement
	\param w width
	\param h height
 */
void 
ofxCv2Image::draw( float x, float y, float w, float h )
{
	if (cvImage.empty()) return;
	
	if (textureIsDirty) updateTexture();
	tex.draw(x, y, w, h);
	
//	int gldepth = glDepth();
//	int glchannels = glChannels();
//	
//	glDrawPixels(cvImage.cols, cvImage.rows, 
//				 glchannels, gldepth, cvImage.data);
}

/*! Draw full-size image
	\param x horizontal displacement
	\param y vertical displacement
 */
void 
ofxCv2Image::draw( float x, float y )
{
	draw(x, y, cvImage.cols, cvImage.rows);
}

/*! Update texture used for drawing
	\note This method comes from ofxOpenCv
 */
void 
ofxCv2Image::updateTexture()
{
	if (cvImage.empty() || !textureIsDirty) return;
	
	int glchannels = glChannels();

	if (tex.getWidth() != cvImage.cols ||
		tex.getHeight() != cvImage.rows)
	{
		tex.clear();
		tex.allocate( cvImage.cols, cvImage.rows, glchannels);
	}
	
	tex.loadData( cvImage.data, cvImage.cols, cvImage.rows, glchannels);
	textureIsDirty = false;
}
