/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svRCIndex.h"
#include "svRCLoop.h"
#include "svNN3dRuleFilter.h"

#include "svImageFunctions.h"
#include "svImageShow.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

NN3dRuleFilter::NN3dRuleFilter()
{
   reset();
}

NN3dRuleFilter::NN3dRuleFilter(NN3dRuleParms* aParms)
{
   mP = aParms;
   reset();
}

void NN3dRuleFilter::initialize(NN3dRuleParms* aParms)
{
   mP = aParms;
   reset();
}

void NN3dRuleFilter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the image, depending on the parms.

void NN3dRuleFilter::doFilterImage(
   cv::Mat&       aInputImageD,    // Input
   cv::Mat&       aInputImageC,    // Input
   cv::Mat&       aInputImageU,    // Input
   cv::Mat&       aOutputImage)    // Output
{
   Prn::print(Prn::View11, "doFilterImage %4d %4d", aInputImageC.rows, aInputImageC.cols);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   // Copy the input image to the output image.
   aOutputImage = aInputImageC.clone();

   // Set the image wrappers.
   mInputC.set(aInputImageC);
   mOutput.set(aOutputImage);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop through the image.

   // Loop through the image. Ignore the top and bottom rows and ignore
   // the left and right edge columns.
   SV::RCIndexLoop tLoop(RCIndex(1, 1),aInputImageC.rows - 2, aInputImageC.cols - 2);
   while (tLoop.loop())
   {
      // Filter each pixel that is high.
      if (mInputC.at(tLoop()) != 0)
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
// D           C           U
// NW NN NE    NW NN NE    NW NN NE
// WW XX EE    WW XX EE    WW XX EE
// SW SS SE    SW SS SE    SW SS SE

void NN3dRuleFilter::doFilterHighPixel(RCIndex aX)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Local variables.

   // Nearest neighbor variables.
   bool tNW = mInputC.at(aX.mRow - 1, aX.mCol - 1) != 0;
   bool tNN = mInputC.at(aX.mRow - 1, aX.mCol    ) != 0;
   bool tNE = mInputC.at(aX.mRow - 1, aX.mCol + 1) != 0;

   bool tWW = mInputC.at(aX.mRow    , aX.mCol - 1) != 0;
   bool tXX = mInputC.at(aX.mRow    , aX.mCol    ) != 0;
   bool tEE = mInputC.at(aX.mRow    , aX.mCol + 1) != 0;

   bool tSW = mInputC.at(aX.mRow + 1, aX.mCol - 1) != 0;
   bool tSS = mInputC.at(aX.mRow + 1, aX.mCol    ) != 0;
   bool tSE = mInputC.at(aX.mRow + 1, aX.mCol + 1) != 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Nearest neighbor rule testing.

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
      if (mInputC.at(tNNLoop()) != 0) tNNSum++;
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

