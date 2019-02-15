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
   mInputD.set(aInputImageC);
   mInputC.set(aInputImageC);
   mInputU.set(aInputImageC);
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
   int tCNW = mInputC.at(aX.mRow - 1, aX.mCol - 1) != 0 ? 1 : 0;
   int tCNN = mInputC.at(aX.mRow - 1, aX.mCol    ) != 0 ? 1 : 0;
   int tCNE = mInputC.at(aX.mRow - 1, aX.mCol + 1) != 0 ? 1 : 0;

   int tCWW = mInputC.at(aX.mRow    , aX.mCol - 1) != 0 ? 1 : 0;
   int tCXX = mInputC.at(aX.mRow    , aX.mCol    ) != 0 ? 1 : 0;
   int tCEE = mInputC.at(aX.mRow    , aX.mCol + 1) != 0 ? 1 : 0;

   int tCSW = mInputC.at(aX.mRow + 1, aX.mCol - 1) != 0 ? 1 : 0;
   int tCSS = mInputC.at(aX.mRow + 1, aX.mCol    ) != 0 ? 1 : 0;
   int tCSE = mInputC.at(aX.mRow + 1, aX.mCol + 1) != 0 ? 1 : 0;

   int tDXX = mInputD.at(aX.mRow    , aX.mCol) != 0 ? 1 : 0;
   int tUXX = mInputU.at(aX.mRow    , aX.mCol) != 0 ? 1 : 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Nearest neighbor rule testing.

   // RULE 1.
   // If not on a contour of the current image.
   if (tCNN && tCSS && tCEE && tCWW)
   {
      return;
   }

   // RULE 2.
   // If on a vertical plane parallel to NS or ES.
   if ((tUXX && tDXX) && ((tCNN && tCSS) || (tCEE && tCWW)))
   {
      return;
   }

   // Count the number of horizontal nearest neighbors.
   int tCNN_sum = tCNW + tCNN + tCNE + tCWW + tCEE + tCSW + tCSS + tCSE;

   // RULE 3.
   // If on a vertical plane not parallel to NS or ES and
   // at a horizontal corner.
   if ((tUXX && tDXX) && (tCNN_sum <= 3))
   {
      return;
   }
   
   // RULE 4.
   // If on a vertical plane not parallel to NS or ES and
   // not at a horizontal corner.
   if (tUXX && tDXX)
   {
      mOutput.at(aX) = mP->mHC1;
      return;
   }

   // RULE 5.
   // Otherwise not on a vertical plane.
   mOutput.at(aX) = mP->mHC2;
   return;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

