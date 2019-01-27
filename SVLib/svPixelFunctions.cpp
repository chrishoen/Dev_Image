/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"

#include "svPixelFunctions.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

// Invalid value.
static constexpr double cInvalidValue = NAN;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Convert from a pixel row column to a point xy coordinates in millimeters.

// Convert from a pixel row column to a point xy coordinates in millimeters.
void convertImagePixelToPoint(
   RCIndex       aPixel,   // Input
   cv::Point2d&  aPoint)   // Output
{
   aPoint.x = double(aPixel.mCol - gSysParms.mImageSize.mCols/2)*gSysParms.mImageMMPerPixel;
   aPoint.y = double(aPixel.mRow - gSysParms.mImageSize.mRows/2)*gSysParms.mImageMMPerPixel;
}

// Convert a point xy coordinates in millimeters to a pixel row column.
void convertImagePointToPixel(
   cv::Point2d   aPoint,   // Input
   RCIndex&      aPixel)   // Output
{
   aPixel.mRow = int(round(aPoint.y*gSysParms.mImagePixelPerMM)) + gSysParms.mImageSize.mRows/2;
   aPixel.mCol = int(round(aPoint.x*gSysParms.mImagePixelPerMM)) + gSysParms.mImageSize.mCols/2;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Convert between a pixel row column and a point coordinates in millimeters.

void convertImagePixelXYToPoint (
   double  aColX,      // Input 
   double  aRowY,      // Input 
   double& aPointX,    // Output 
   double& aPointY)    // Output
{
   aPointX = double(aColX - gSysParms.mImageSize.mCols/2)*gSysParms.mImageMMPerPixel;
   aPointY = double(aRowY - gSysParms.mImageSize.mRows/2)*gSysParms.mImageMMPerPixel;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Limit object pixel indices.

void limitImagePixel(RCIndex& aIndex)
{
   if (aIndex.mCol < 0) aIndex.mCol = 0;
   if (aIndex.mCol > gSysParms.mImageSize.mCols - 1) aIndex.mCol = gSysParms.mImageSize.mCols - 1;
   if (aIndex.mRow < 0) aIndex.mRow = 0;
   if (aIndex.mRow > gSysParms.mImageSize.mRows - 1) aIndex.mRow = gSysParms.mImageSize.mRows - 1;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Limit image pixel indices.

void limitImagePixelXY(int* aCol,int* aRow)
{
   if (*aCol < gSysParms.mImageColLimit) *aCol = gSysParms.mImageColLimit;
   if (*aCol > gSysParms.mImageSize.mCols - gSysParms.mImageColLimit - 1) *aCol = gSysParms.mImageSize.mCols - gSysParms.mImageColLimit - 1;
   if (*aRow < gSysParms.mImageRowLimit) *aRow = gSysParms.mImageRowLimit;
   if (*aRow > gSysParms.mImageSize.mRows - gSysParms.mImageRowLimit - 1) *aRow = gSysParms.mImageSize.mRows - gSysParms.mImageRowLimit - 1;
}

bool isImagePixelInBounds(int aCol, int aRow)
{
   if (aCol < gSysParms.mImageColLimit) return false;
   if (aCol > gSysParms.mImageSize.mCols - gSysParms.mImageColLimit - 1) return false;
   if (aRow < gSysParms.mImageRowLimit) return false;
   if (aRow > gSysParms.mImageSize.mRows - gSysParms.mImageRowLimit - 1) return false;
   return true;
}

bool isImagePixelInBounds(RCIndex aPixel)
{
   if (aPixel.mCol < gSysParms.mImageColLimit) return false;
   if (aPixel.mCol > gSysParms.mImageSize.mCols - gSysParms.mImageColLimit - 1) return false;
   if (aPixel.mRow < gSysParms.mImageRowLimit) return false;
   if (aPixel.mRow > gSysParms.mImageSize.mRows - gSysParms.mImageRowLimit - 1) return false;
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void setInvalid(double& aValue)
{
   aValue = cInvalidValue;
}

// Set the x and y to the invalid value.
void setInvalid(cv::Point2d& aPoint)
{
   aPoint.x = cInvalidValue;
   aPoint.y = cInvalidValue;
}

void setInvalid(cv::Point3d& aPoint)
{
   aPoint.x = cInvalidValue;
   aPoint.y = cInvalidValue;
   aPoint.z = cInvalidValue;
}

// Return false if any value is the invalid value.
bool isValid(double aValue)
{
   return !isnan(aValue);
}

bool isValid(cv::Point2d& aPoint)
{
   if (isnan(aPoint.x)) return false;
   if (isnan(aPoint.y)) return false;
   return true;
}

bool isValid(cv::Point3d& aPoint)
{
   if (isnan(aPoint.x)) return false;
   if (isnan(aPoint.y)) return false;
   if (isnan(aPoint.z)) return false;
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
