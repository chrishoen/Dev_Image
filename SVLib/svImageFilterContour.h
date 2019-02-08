#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Contour specific image filter.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "svImageFilterBase.h"
#include "svImageWrapper.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is an image filter that implements a gaussian blur algorithm.
//
// It inherits from the image filter base class, which provides a common 
// interface and a parameters member variable.

class ImageFilterContour : public ImageFilterBase
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Input and output image wrappers.
   ImageWrapper mInputImage;
   ImageWrapper mOutputImage;

   // Number of pixels in the contour that is being filtered.
   int mNumPixels;

   // Current pixel that is being filtered.
   RCIndex mXM1;       // X0 - 1  previous pixel.
   RCIndex mX0;        // X0      current pixel.
   RCIndex mXP1;       // X0 + 1  next pixel.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   typedef ImageFilterBase BaseClass;
   ImageFilterContour();
   ImageFilterContour(ImageFilterParms* aParms);
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Filter an image according to the parms.
   void doFilterImage(
      cv::Mat&       aInput,               // Input
      cv::Mat&       aOutput) override;    // Output

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Filter all of the pixels in a contour.
   void doFilterContour(
      std::vector<cv::Point>& aContour);

   // Filter an image pixel that is contained in a contour.
   void doFilterContourPixel(int aN);
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


