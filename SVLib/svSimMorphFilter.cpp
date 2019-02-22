/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svRCIndex.h"
#include "svRCLoop.h"
#include "svSimMorphFilter.h"

#include "svImageFunctions.h"
#include "svImageShow.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

SimMorphFilter::SimMorphFilter()
{
   reset();
}

SimMorphFilter::SimMorphFilter(SimMorphParms* aParms)
{
   mP = aParms;
   reset();
}

void SimMorphFilter::initialize(SimMorphParms* aParms)
{
   mP = aParms;
   reset();
}

void SimMorphFilter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize a first image.

void SimMorphFilter::doInitializeImage(
   cv::Mat&       aOutput)              // Output
{
   // Create an image filled with all zeros.
   aOutput = cv::Mat::zeros(mP->mImageSize.mRows, mP->mImageSize.mCols, CV_8UC1);

   // Set the image wrappers.
   mOutput.set(aOutput);

   // Set the center pixel.
   mOutput.at(RCIndex(mP->mImageSize.mRows/2, mP->mImageSize.mCols/2)) = 255;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the image, depending on the parms.

void SimMorphFilter::doFilterImage(
   cv::Mat&       aInputImage,     // Input
   cv::Mat&       aOutputImage)    // Output
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   Prn::print(Prn::View11, "doFilterImage %4d %4d", aInputImage.rows, aInputImage.cols);

   // Clone the input image to the output image.
   aOutputImage = aInputImage.clone();

   // Set the image wrappers.
   mInput.set(aInputImage);
   mOutput.set(aOutputImage);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop through the image.

   // Loop through the image. Ignore the top and bottom rows and ignore
   // the left and right edge columns.
   SV::RCIndexLoop tLoop(RCIndex(1, 1),aInputImage.rows - 2, aInputImage.cols - 2);
   while (tLoop.loop())
   {
      // Filter each pixel that is high.
      if (mInput.at(tLoop()) != 0)
      {
         doFilterHighPixel2(tLoop());
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter a pixel that is high.
// 

void SimMorphFilter::doFilterHighPixel2(RCIndex aX)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Nearest neighbor rule testing.

   // Loop index,
   SV::RCDitherLoop1 tLoop;

   // Set adjacent column pixels.
   tLoop.set(aX, mP->mDelta.mCols, 1);
   tLoop.centerRow();
   for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
   {
      mOutput.at(tLoop()) = 255;
   }

   // Set adjacent row pixels.
   tLoop.set(aX, mP->mDelta.mRows, 1);
   tLoop.centerCol();
   for (tLoop.firstRow(); tLoop.testRow(); tLoop.nextRow())
   {
      mOutput.at(tLoop()) = 255;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

