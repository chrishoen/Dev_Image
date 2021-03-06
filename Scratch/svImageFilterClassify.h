#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Classify specific image filter.
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

class ImageFilterClassify : public ImageFilterBase
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
   ImageFilterClassify();
   ImageFilterClassify(ImageFilterParms* aParms);
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

   // Get the output value.
   uchar getOutputValue(
      uchar  aInputValue,       // Input
      int    aNeighborSum);     // Input
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


