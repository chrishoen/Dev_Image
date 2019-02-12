#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Image wrapper.
==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <opencv2/core/core.hpp>

#include "svRCIndex.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides an adapter for image matrices.

class ImageWrapper
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   // Image scale factor, 100.0 corresponds to max value 255.
   static constexpr double cImageScale = 100.0 / 255.0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Image matrix.
   cv::Mat* mImage;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   ImageWrapper()
   {
      mImage = 0;
   }

   // Constructor.
   ImageWrapper(cv::Mat& aImage)
   {
      mImage = &aImage;
   }

   // Constructor.
   ImageWrapper(cv::Mat* aImage)
   {
      mImage = aImage;
   }

   void set(cv::Mat& aImage)
   {
      mImage = &aImage;
   }

   void set(cv::Mat* aImage)
   {
      mImage = aImage;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods

   // Element access.
   uchar& at(RCIndex aPixel)
   {
      return mImage->at<uchar>(aPixel.mRow, aPixel.mCol);
   }

   // Element access.
   bool getValue(RCIndex aPixel, uchar& aValue)
   {
      aValue = 0;
      if (aPixel.mRow < 0) return false;
      if (aPixel.mRow > mImage->rows - 1) return false;
      if (aPixel.mCol < 0) return false;
      if (aPixel.mCol > mImage->cols - 1) return false;

      aValue = mImage->at<uchar>(aPixel.mRow, aPixel.mCol);
      return true;
   }

   // Element access.
   uchar& at(int aRow,int aCol)
   {
      return mImage->at<uchar>(aRow, aCol);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods

   // Return a scaled value such that 0..100.0 corresponds to 0..255,
   // the minimum to maximum range.
   double getScaled(RCIndex aPixel)
   {
      uchar tValue = mImage->at<uchar>(aPixel.mRow, aPixel.mCol);
      return tValue * cImageScale;
   }

   // Set a scaled value such that 0..100.0 corresponds to 0..255,
   // the minimum to maximum range.
   void setScaled(RCIndex aPixel,double aValue)
   {
      double tDoubleValue = aValue / cImageScale;
      uchar tUCharValue = (uchar)round(tDoubleValue);
      mImage->at<uchar>(aPixel.mRow, aPixel.mCol) = tUCharValue;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Return size.
   RCSize rcSize()
   {
      return RCSize(mImage->rows,mImage->cols);
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
