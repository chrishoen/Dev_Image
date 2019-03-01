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
// Classify a plane according to nearest neighbors.

inline int NN3dRuleFilter::doClassifyPlane(
   int a11, int a12, int a13,
   int a21, int a23,
   int a31, int a32, int a33)
{
   // Return a classification code.
   if ((a12 && a32) || (a21 && a23)) return 0x01;
   if (a12 && a32) return 0x02;
   if (a21 && a23) return 0x03;

   // Count the number of nearest neighbors.
   int tNeighborCount = a11 + a12 + a13 + a21 + a23 + a31 + a32 + a33;

   // Count the number of corners.
   int tCornerCount = a11 + a13 + a31 + a33;

   // Count the number of changes.
   int tChangeCount = 0;
   if (a11 != a21) tChangeCount++;
   if (a12 != a11) tChangeCount++;
   if (a13 != a12) tChangeCount++;
   if (a23 != a13) tChangeCount++;
   if (a33 != a23) tChangeCount++;
   if (a32 != a33) tChangeCount++;
   if (a31 != a32) tChangeCount++;
   if (a21 != a31) tChangeCount++;

   // Return a classification code.
   if ((tNeighborCount == 1) && (tCornerCount == 1)) return 0x10;
   if ((tNeighborCount == 2) && (tChangeCount == 2)) return 0x20;
   if ((tNeighborCount == 3) && (tChangeCount == 2) && (tChangeCount == 1)) return 0x31;
   if ((tNeighborCount == 3) && (tChangeCount == 2) && (tCornerCount == 2)) return 0x32;
   if ((tNeighborCount == 4) && (tChangeCount == 2)) return 0x40;
   if ((tNeighborCount == 5) && (tChangeCount == 2)) return 0x50;
   return -1;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Classify the S,R,C planes.

inline void NN3dRuleFilter::doClassifyPlaneS(RCIndex aX)
{
   // Get matrix variables from input image plane.
   m211 = mInputS2.at(aX.mRow - 1, aX.mCol - 1) != 0 ? 1 : 0;
   m212 = mInputS2.at(aX.mRow - 1, aX.mCol    ) != 0 ? 1 : 0;
   m213 = mInputS2.at(aX.mRow - 1, aX.mCol + 1) != 0 ? 1 : 0;

   m221 = mInputS2.at(aX.mRow,     aX.mCol - 1) != 0 ? 1 : 0;
   m222 = mInputS2.at(aX.mRow,     aX.mCol    ) != 0 ? 1 : 0;
   m223 = mInputS2.at(aX.mRow,     aX.mCol + 1) != 0 ? 1 : 0;

   m231 = mInputS2.at(aX.mRow + 1, aX.mCol - 1) != 0 ? 1 : 0;
   m232 = mInputS2.at(aX.mRow + 1, aX.mCol    ) != 0 ? 1 : 0;
   m233 = mInputS2.at(aX.mRow + 1, aX.mCol + 1) != 0 ? 1 : 0;

   // Classify according to the matrix variables.
   mClassS = doClassifyPlane(
      m211, m212, m213,
      m221,       m223,
      m231, m232, m233);
}

inline void NN3dRuleFilter::doClassifyPlaneRC(RCIndex aX)
{
   // Get matrix variables from input image plane.
   m111 = mInputS1.at(aX.mRow - 1, aX.mCol - 1) != 0 ? 1 : 0;
   m112 = mInputS1.at(aX.mRow - 1, aX.mCol    ) != 0 ? 1 : 0;
   m113 = mInputS1.at(aX.mRow - 1, aX.mCol + 1) != 0 ? 1 : 0;

   m121 = mInputS1.at(aX.mRow,     aX.mCol - 1) != 0 ? 1 : 0;
   m122 = mInputS1.at(aX.mRow,     aX.mCol    ) != 0 ? 1 : 0;
   m123 = mInputS1.at(aX.mRow,     aX.mCol + 1) != 0 ? 1 : 0;

   m131 = mInputS1.at(aX.mRow + 1, aX.mCol - 1) != 0 ? 1 : 0;
   m132 = mInputS1.at(aX.mRow + 1, aX.mCol    ) != 0 ? 1 : 0;
   m133 = mInputS1.at(aX.mRow + 1, aX.mCol + 1) != 0 ? 1 : 0;

   // Get matrix variables from input image plane.
   m311 = mInputS3.at(aX.mRow - 1, aX.mCol - 1) != 0 ? 1 : 0;
   m312 = mInputS3.at(aX.mRow - 1, aX.mCol    ) != 0 ? 1 : 0;
   m313 = mInputS3.at(aX.mRow - 1, aX.mCol + 1) != 0 ? 1 : 0;

   m321 = mInputS3.at(aX.mRow,     aX.mCol - 1) != 0 ? 1 : 0;
   m322 = mInputS3.at(aX.mRow,     aX.mCol    ) != 0 ? 1 : 0;
   m323 = mInputS3.at(aX.mRow,     aX.mCol + 1) != 0 ? 1 : 0;

   m331 = mInputS3.at(aX.mRow + 1, aX.mCol - 1) != 0 ? 1 : 0;
   m332 = mInputS3.at(aX.mRow + 1, aX.mCol    ) != 0 ? 1 : 0;
   m333 = mInputS3.at(aX.mRow + 1, aX.mCol + 1) != 0 ? 1 : 0;

   // Classify according to the matrix variables.
   mClassR = doClassifyPlane(
      m121, m122, m123,
      m221,       m223,
      m321, m322, m323);

   // Classify according to the matrix variables.
   mClassC = doClassifyPlane(
      m112, m122, m132,
      m212,       m232,
      m312, m322, m332);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter a pixel that is high.
// 

void NN3dRuleFilter::doFilterHighPixel(RCIndex aX)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Nearest neighbor rule testing.

   // Classify the slice plane.
   doClassifyPlaneS(aX);

   // RULE 1.
   // If not on a horizontal edge.
   if (mClassS == 0x01)
   {
      mRuleCount1++;
      return;
   }

   // Classify the row and column planes.
   doClassifyPlaneRC(aX);

   // RULE 2.
   // If on a vertical plane and slice class is 4 or 5.
   if ((mClassR == 0x02) && (mClassS >= 0x40))
   {
      mRuleCount2++;
      mOutput.at(aX) = mP->mHC1;
      return;
   }

   // RULE 3.
   // If on a vertical plane and any other.
   if (mClassR == 0x02)
   {
      mRuleCount3++;
      return;
   }

   // RULE 4.
   // If not on a vertical plane and row or column class is 4 or 5.
   if (my_imax(mClassR,mClassC) >= 0x40)
   {
      mRuleCount4++;
      mOutput.at(aX) = mP->mHC2;
      return;
   }

   // RULE 5.
   // Any other.
   mRuleCount5++;
   return;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

