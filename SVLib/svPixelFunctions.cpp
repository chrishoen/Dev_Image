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
void convertObjectPixelToPoint(
   RCIndex       aPixel,   // Input
   cv::Point3d&  aPoint)   // Output
{
   aPoint.x = double(aPixel.mCol - gSysParms.mTargetSize.mCols/2)*gSysParms.mTargetMMPerPixel;
   aPoint.y = double(aPixel.mRow - gSysParms.mTargetSize.mRows/2)*gSysParms.mTargetMMPerPixel;
   aPoint.z = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Convert a point xy coordinates in millimeters to a pixel row column.

// Convert a point xy coordinates in millimeters to a pixel row column.
void convertObjectPointToPixel(
   cv::Point3d   aPoint,   // Input
   RCIndex&      aPixel)   // Output
{
   aPixel.mRow = int(round(aPoint.y*gSysParms.mTargetPixelPerMM)) + gSysParms.mTargetSize.mRows/2;
   aPixel.mCol = int(round(aPoint.x*gSysParms.mTargetPixelPerMM)) + gSysParms.mTargetSize.mCols/2;
}

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
   aPoint.x = double(aPixel.mCol - gSysParms.mSensorSize.mCols/2)*gSysParms.mSensorMMPerPixel;
   aPoint.y = double(aPixel.mRow - gSysParms.mSensorSize.mRows/2)*gSysParms.mSensorMMPerPixel;
}

// Convert a point xy coordinates in millimeters to a pixel row column.
void convertImagePointToPixel(
   cv::Point2d   aPoint,   // Input
   RCIndex&      aPixel)   // Output
{
   aPixel.mRow = int(round(aPoint.y*gSysParms.mSensorPixelPerMM)) + gSysParms.mSensorSize.mRows/2;
   aPixel.mCol = int(round(aPoint.x*gSysParms.mSensorPixelPerMM)) + gSysParms.mSensorSize.mCols/2;
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
   aPointX = double(aColX - gSysParms.mSensorSize.mCols/2)*gSysParms.mSensorMMPerPixel;
   aPointY = double(aRowY - gSysParms.mSensorSize.mRows/2)*gSysParms.mSensorMMPerPixel;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Limit object pixel indices.

void limitImagePixel(RCIndex& aIndex)
{
   if (aIndex.mCol < 0) aIndex.mCol = 0;
   if (aIndex.mCol > gSysParms.mSensorSize.mCols - 1) aIndex.mCol = gSysParms.mSensorSize.mCols - 1;
   if (aIndex.mRow < 0) aIndex.mRow = 0;
   if (aIndex.mRow > gSysParms.mSensorSize.mRows - 1) aIndex.mRow = gSysParms.mSensorSize.mRows - 1;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Limit object pixel indices.

void limitObjectPixel(RCIndex& aIndex)
{
   if (aIndex.mCol < 0) aIndex.mCol = 0;
   if (aIndex.mCol > gSysParms.mTargetSize.mCols - 1) aIndex.mCol = gSysParms.mTargetSize.mCols - 1;
   if (aIndex.mRow < 0) aIndex.mRow = 0;
   if (aIndex.mRow > gSysParms.mTargetSize.mRows - 1) aIndex.mRow = gSysParms.mTargetSize.mRows - 1;
}

// Return true if a pixel is in bounds.
bool isObjectPixelInBounds(RCIndex& aIndex)
{
   if (aIndex.mCol < 0) return false;
   if (aIndex.mCol > gSysParms.mTargetSize.mCols - 1) return false;
   if (aIndex.mRow < 0) return false;
   if (aIndex.mRow > gSysParms.mTargetSize.mRows - 1) return false;
   return true;

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Limit image pixel indices.

void limitImagePixelXY(int* aCol,int* aRow)
{
   if (*aCol < gSysParms.mSensorColLimit) *aCol = gSysParms.mSensorColLimit;
   if (*aCol > gSysParms.mSensorSize.mCols - gSysParms.mSensorColLimit - 1) *aCol = gSysParms.mSensorSize.mCols - gSysParms.mSensorColLimit - 1;
   if (*aRow < gSysParms.mSensorRowLimit) *aRow = gSysParms.mSensorRowLimit;
   if (*aRow > gSysParms.mSensorSize.mRows - gSysParms.mSensorRowLimit - 1) *aRow = gSysParms.mSensorSize.mRows - gSysParms.mSensorRowLimit - 1;
}

bool isImagePixelInBounds(int aCol, int aRow)
{
   if (aCol < gSysParms.mSensorColLimit) return false;
   if (aCol > gSysParms.mSensorSize.mCols - gSysParms.mSensorColLimit - 1) return false;
   if (aRow < gSysParms.mSensorRowLimit) return false;
   if (aRow > gSysParms.mSensorSize.mRows - gSysParms.mSensorRowLimit - 1) return false;
   return true;
}

bool isImagePixelInBounds(RCIndex aPixel)
{
   if (aPixel.mCol < gSysParms.mSensorColLimit) return false;
   if (aPixel.mCol > gSysParms.mSensorSize.mCols - gSysParms.mSensorColLimit - 1) return false;
   if (aPixel.mRow < gSysParms.mSensorRowLimit) return false;
   if (aPixel.mRow > gSysParms.mSensorSize.mRows - gSysParms.mSensorRowLimit - 1) return false;
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
