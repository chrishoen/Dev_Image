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
   // Members:

   // Image matrix.
   cv::Mat& mImage;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infrastrucure:

   // Constructor.
   ImageWrapper(cv::Mat& aImage);
   ImageWrapper(cv::Mat* aImage);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Element access.
   uchar& at(RCIndex aPixel);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Return a scaled value such that 0..100.0 corresponds to 0..255,
   // the minimum to maximum range.
   float getScaled(RCIndex aPixel);

   // Set a scaled value such that 0..100.0 corresponds to 0..255,
   // the minimum to maximum range.
   void setScaled(RCIndex aPixel,float aValue);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Return size.
   RCSize rcSize()
   {
      return RCSize(mImage.rows,mImage.cols);
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
