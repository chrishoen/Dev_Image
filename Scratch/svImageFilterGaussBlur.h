#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
GaussBlur specific image filter.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "svImageFilterBase.h"

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

class ImageFilterGaussBlur : public ImageFilterBase
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   typedef ImageFilterBase BaseClass;
   ImageFilterGaussBlur();
   ImageFilterGaussBlur(ImageFilterParms* aParms);
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Filter an image according to the parms.
   void doFilterImage(
      cv::Mat&       aInput,               // Input
      cv::Mat&       aOutput) override;    // Output
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

