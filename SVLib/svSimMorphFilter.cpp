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

   // Copy the input image to the output image.
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
         doFilterHighPixel(tLoop());
      }
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter a pixel that is high.
// 
// NW NN NE
// WW XX EE
// SW SS SE


void SimMorphFilter::doFilterHighPixel(RCIndex aX)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Local variables.

   // Nearest neighbor variables.
   bool tNW = mInput.at(aX.mRow - 1, aX.mCol - 1) != 0;
   bool tNN = mInput.at(aX.mRow - 1, aX.mCol    ) != 0;
   bool tNE = mInput.at(aX.mRow - 1, aX.mCol + 1) != 0;

   bool tWW = mInput.at(aX.mRow    , aX.mCol - 1) != 0;
   bool tXX = mInput.at(aX.mRow    , aX.mCol    ) != 0;
   bool tEE = mInput.at(aX.mRow    , aX.mCol + 1) != 0;

   bool tSW = mInput.at(aX.mRow + 1, aX.mCol - 1) != 0;
   bool tSS = mInput.at(aX.mRow + 1, aX.mCol    ) != 0;
   bool tSE = mInput.at(aX.mRow + 1, aX.mCol + 1) != 0;

   int tCode = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Nearest neighbor rule testing.

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

