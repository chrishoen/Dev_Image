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
   mRuleCount1 = 0;
   mRuleCount2 = 0;
   mRuleCount3 = 0;
   mRuleCount4 = 0;
   mRuleCount5 = 0;
}

void NN3dRuleFilter::show()
{
   Prn::print(0, "RuleCount1 %10d", mRuleCount1);
   Prn::print(0, "RuleCount2 %10d", mRuleCount2);
   Prn::print(0, "RuleCount3 %10d", mRuleCount3);
   Prn::print(0, "RuleCount4 %10d", mRuleCount4);
   Prn::print(0, "RuleCount5 %10d", mRuleCount5);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the image, depending on the parms.

void NN3dRuleFilter::doFilterImage(
   cv::Mat&       aInputS1,    // Input
   cv::Mat&       aInputS2,    // Input
   cv::Mat&       aInputS3,    // Input
   cv::Mat&       aOutput)     // Output
{
   Prn::print(Prn::View14, "doFilterImage %4d %4d", aInputS2.rows, aInputS2.cols);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   // Copy the input image to the output image.
   aOutput = aInputS2.clone();

   // Reset variables.
   reset();

   // Set the image wrappers.
   mInputS1.set(aInputS1);
   mInputS2.set(aInputS2);
   mInputS3.set(aInputS3);
   mOutput.set(aOutput);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop through the image.

   // Loop through the image. Ignore the top and bottom rows and ignore
   // the left and right edge columns.
   SV::RCIndexLoop tLoop(RCIndex(1, 1),aInputS2.rows - 2, aInputS2.cols - 2);
   while (tLoop.loop())
   {
      // Filter each pixel that is high.
      if (mInputS2.at(tLoop()) != 0)
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
// 111 112 113     211 212 213     311 312 313
// 121 122 123     221 222 223     321 322 323
// 131 132 133     231 232 233     331 332 333

void NN3dRuleFilter::doFilterHighPixel(RCIndex aX)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Local variables.

   // Nearest neighbor variables.
   int t211 = mInputS2.at(aX.mRow - 1, aX.mCol - 1) != 0 ? 1 : 0;
   int t212 = mInputS2.at(aX.mRow - 1, aX.mCol    ) != 0 ? 1 : 0;
   int t213 = mInputS2.at(aX.mRow - 1, aX.mCol + 1) != 0 ? 1 : 0;

   int t221 = mInputS2.at(aX.mRow    , aX.mCol - 1) != 0 ? 1 : 0;
   int t222 = mInputS2.at(aX.mRow    , aX.mCol    ) != 0 ? 1 : 0;
   int t223 = mInputS2.at(aX.mRow    , aX.mCol + 1) != 0 ? 1 : 0;

   int t231 = mInputS2.at(aX.mRow + 1, aX.mCol - 1) != 0 ? 1 : 0;
   int t232 = mInputS2.at(aX.mRow + 1, aX.mCol    ) != 0 ? 1 : 0;
   int t233 = mInputS2.at(aX.mRow + 1, aX.mCol + 1) != 0 ? 1 : 0;

   int t322 = mInputS3.at(aX.mRow    , aX.mCol) != 0 ? 1 : 0;
   int t122 = mInputS1.at(aX.mRow    , aX.mCol) != 0 ? 1 : 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Nearest neighbor rule testing.

   // RULE 1.
   // If not on a contour of the current image.
   if (t212 && t232 && t221 && t223)
   {
      mRuleCount1++;
      return;
   }

   // RULE 2.
   // If on a vertical plane parallel to NS or ES.
   if ((t122 && t322) && ((t212 && t232) || (t221 && t223)))
   {
      mRuleCount2++;
      return;
   }

   // Count the number of horizontal nearest neighbors.
   int tNN_sum = t211 + t212 + t213 + t221 + t223 + t231 + t232 + t233;

   // RULE 3.
   // If on a vertical plane not parallel to NS or ES and
   // at a horizontal corner.
   if ((t122 && t322) && (tNN_sum <= 3))
   {
      mRuleCount3++;
      return;
   }
   
   // RULE 4.
   // If on a vertical plane not parallel to NS or ES and
   // not at a horizontal corner.
   if (t122 && t322)
   {
      mOutput.at(aX) = mP->mHC1;
      mRuleCount4++;
      return;
   }

   // RULE 5.
   // Otherwise not on a vertical plane.
   mOutput.at(aX) = mP->mHC2;
   mRuleCount5++;
   return;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

