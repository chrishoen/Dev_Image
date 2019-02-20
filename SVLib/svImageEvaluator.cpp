/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svImageWrapper.h"
#include "svRCLoop.h"

#include "svImageEvaluator.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ImageEvaluator::ImageEvaluator()
{
   reset();
}

void ImageEvaluator::reset()
{
   mResults = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Evaluate the input image. Calculate the row and column metrics results.

void ImageEvaluator::doEvaluateImage(
   cv::Mat&       aInputImage,    // Input
   ImageResults&  aResults)       // Output
{
   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Initialize.

   // Variables.
   aResults.reset();
   
   // Inputs and outputs.
   mInput.set(aInputImage);
   mResults = &aResults;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Loop through the image.

   // Loop through the image. Ignore the top and bottom rows and ignore
   // the left and right edge columns.
   SV::RCIndexLoop tLoop(RCIndex(1, 1), aInputImage.rows - 2, aInputImage.cols - 2);
   while (tLoop.loop())
   {
      // Advance.
      mResults->mTotalCount++;

      // Evaluate each pixel that is high.
      if (mInput.at(tLoop()) != 0)
      {
         doEvaluateHighPixel(tLoop());
      }
   }
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Evaluate a high pixel. Calculate the row and column metrics results.

void ImageEvaluator::doEvaluateHighPixel(RCIndex aX)
{
   // Advance.
   mResults->mHighCount++;

   // Store results for first evaluation.
   if (mResults->mFirst)
   {
      mResults->mFirst = false;
      mResults->mRowMin = aX;
      mResults->mRowMax = aX;
      mResults->mColMin = aX;
      mResults->mColMax = aX;
      return;
   }

   // Store results for other evaluations.
   if (aX.mRow <  mResults->mRowMin.mRow) mResults->mRowMin = aX;
   if (aX.mRow >= mResults->mRowMax.mRow) mResults->mRowMax = aX;
   if (aX.mCol <  mResults->mColMin.mCol) mResults->mColMin = aX;
   if (aX.mCol >= mResults->mColMax.mCol) mResults->mColMax = aX;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace