/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svRCIndex.h"
#include "svRCLoop.h"
#include "svNNRuleFilter.h"

#include "svImageFunctions.h"
#include "svImageShow.h"

#pragma warning(push)
#pragma warning(disable:4533 )

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

NNRuleFilter::NNRuleFilter()
{
   reset();
}

NNRuleFilter::NNRuleFilter(NNRuleParms* aParms)
{
   mP = aParms;
   reset();
}

void NNRuleFilter::initialize(NNRuleParms* aParms)
{
   mP = aParms;
   reset();
}

void NNRuleFilter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the image, depending on the parms.

void NNRuleFilter::doFilterImage(
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
   SV::RCIndexLoop tLoop(RCIndex(1, 1),mInput.rcSize());
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
// UL UU UR
// LL XX RR
// DL DD DR


void NNRuleFilter::doFilterHighPixel(RCIndex aX)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Local variables.

   // Nearest neighbor variables.
   bool tUL = mInput.at(aX.mRow - 1, aX.mCol - 1) != 0;
   bool tUU = mInput.at(aX.mRow - 1, aX.mCol    ) != 0;
   bool tUR = mInput.at(aX.mRow - 1, aX.mCol + 1) != 0;

   bool tLL = mInput.at(aX.mRow    , aX.mCol - 1) != 0;
   bool tXX = mInput.at(aX.mRow    , aX.mCol    ) != 0;
   bool tRR = mInput.at(aX.mRow    , aX.mCol + 1) != 0;

   bool tDL = mInput.at(aX.mRow + 1, aX.mCol - 1) != 0;
   bool tDD = mInput.at(aX.mRow + 1, aX.mCol    ) != 0;
   bool tDR = mInput.at(aX.mRow + 1, aX.mCol + 1) != 0;

   int tCode = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Nearest neighbor rule testing.

   tCode = 0;

   // Rule 1.
   if (tLL && tRR)
   {
      tCode = 0;
      goto endtest;
   }

   // Rule 2.
   if (tUU && tDD)
   {
      tCode = 0;
      goto endtest;
   }

   // Count the number of nearest neighbors that are occupied.
   int tNNSum = 0;
   SV::RCCircuitLoop tNNLoop(aX, 1);
   while (tNNLoop.loop())
   {
      if (mInput.at(tNNLoop()) != 0) tNNSum++;
   }

   // Rule 3.
   if (tNNSum < 4)
   {
      tCode = 1;
      goto endtest;
   }

   tCode = 2;

endtest:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Set the high pixel, based on the rule tesing results.

   if (tCode == 1)
   {
      mOutput.at(aX) = mP->mHC1;
   }

   if (tCode == 2)
   {
      mOutput.at(aX) = mP->mHC2;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

#pragma warning(pop)
