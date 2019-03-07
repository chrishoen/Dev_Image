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

      mResults->mMinRow = aX.mRow;
      mResults->mMaxRow = aX.mRow;
      mResults->mMinCol = aX.mCol;
      mResults->mMaxCol = aX.mCol;
      return;
   }

   // Store results for other evaluations.
   if (aX.mRow <  mResults->mMinRow) mResults->mMinRow = aX.mRow;
   if (aX.mRow >= mResults->mMaxRow) mResults->mMaxRow = aX.mRow;
   if (aX.mCol <  mResults->mMinCol) mResults->mMinCol = aX.mCol;
   if (aX.mCol >= mResults->mMaxCol) mResults->mMaxCol = aX.mCol;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace