/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svRCIndex.h"
#include "svRCLoop.h"
#include "svNNRuleFilter3d.h"

#include "svImageFunctions.h"
#include "svImageShow.h"

#pragma warning(push)
#pragma warning(disable:4533 )

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

NNRuleFilter3d::NNRuleFilter3d()
{
   reset();
}

NNRuleFilter3d::NNRuleFilter3d(NNRuleParms* aParms)
{
   mP = aParms;
   reset();
}

void NNRuleFilter3d::initialize(NNRuleParms* aParms)
{
   mP = aParms;
   reset();
}

void NNRuleFilter3d::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the image, depending on the parms.

void NNRuleFilter3d::doFilterImage(
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


void NNRuleFilter3d::doFilterHighPixel(RCIndex aX)
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

   tCode = 0;

   // Rule 1.
   if (tWW && tEE)
   {
      return;
   }

   // Rule 2.
   if (tNN && tSS)
   {
      return;
   }

   // Count the number of nearest neighbors that are occupied.
   int tNNSum = 0;
   SV::RCCircuitLoop tNNLoop(aX, 1);
   while (tNNLoop.loop())
   {
      if (mInput.at(tNNLoop()) != 0) tNNSum++;
   }

   // Rule 3.
   if (tNNSum <= 3)
   {
      mOutput.at(aX) = mP->mHC1;
      return;
   }

   // Rule 4.
   mOutput.at(aX) = mP->mHC2;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

#pragma warning(pop)
