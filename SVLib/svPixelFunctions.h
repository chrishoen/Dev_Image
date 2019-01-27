#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Miscellaneous support functions
==============================================================================*/
//#include <vector>
#include <opencv2/core/core.hpp>
#include "svDefs.h"
#include "svRCIndex.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Convert between a pixel row column pair and a point coordinate pair in
// millimeters.

// Convert from a pixel row column to a point xy coordinates in millimeters.
void convertImagePixelToPoint(
   RCIndex       aPixel,   // Input
   cv::Point2d&  aPoint);  // Output

// Convert a point xy coordinates in millimeters to a pixel row column.
void convertImagePointToPixel(
   cv::Point2d   aPoint,   // Input
   RCIndex&      aPixel);  // Output

//******************************************************************************
//******************************************************************************
//******************************************************************************

// Convert from a pixel row column to a point xy coordinates in millimeters.
// Here the pixel row and column are doubles.
void convertImagePixelXYToPoint (
   double  aColX,      // Input 
   double  aRowY,      // Input 
   double& aPointX,    // Output 
   double& aPointY);   // Output

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Limit image pixel indices.

// Limit a coordinate so that it doesn't go out of bounds. Use global size
// parameters as the limits.
void limitImagePixel(RCIndex& aIndex);

// Limit a coordinate so that it doesn't go out of bounds. Use global size
// parameters as the limits.
void limitImagePixelXY(int* aCol,int* aRow);

// Return true if a pixel is in bounds.
bool isImagePixelInBounds(int aCol,int aRow);

// Return true if a pixel is in bounds.
bool isImagePixelInBounds(RCIndex aPixel);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Point invalid values.

// Set the x and y to the invalid value.
void setInvalid(double& aValue);
void setInvalid(cv::Point2d& aPoint);
void setInvalid(cv::Point3d& aPoint);

// Return false if any value is the invalid value.
bool isValid(double       aValue);
bool isValid(cv::Point2d& aPoint);
bool isValid(cv::Point3d& aPoint);

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
