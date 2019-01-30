/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "prnPrint.h"
#include "dsp_math.h"

#include "svSysParms.h"
#include "svDefs.h"

#include "svSimImageGenSquare.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

SimImageGenSquare::SimImageGenSquare()
{
   reset();
}

SimImageGenSquare::SimImageGenSquare(SimImageGenParms* aParms)
{
   BaseClass::mP = aParms;
   reset();
}

void SimImageGenSquare::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the image, depending on the parms.

void SimImageGenSquare::doGenerateImage(
   cv::Mat&       aImage)          // Output
{
   Prn::print(0, "SimImageGenSquare::doGenerateImage");
   // Create an image filled with all zeros.
   BaseClass::doCreateZeroImage(aImage);

   // Square variables. 
   int tCenterRow     = mP->mImageSize.mRows / 2;
   int tCenterCol     = mP->mImageSize.mCols / 2;
   int tUpperLeftRow  = tCenterRow - mP->mImageB;
   int tUpperLeftCol  = tCenterCol - mP->mImageB;
   int tLowerRightRow = tCenterRow + mP->mImageB;
   int tLowerRightCol = tCenterCol + mP->mImageB;

   cv::Point tPoint1(tUpperLeftCol,  tUpperLeftRow);
   cv::Point tPoint2(tLowerRightCol, tLowerRightRow);
   int tRadius = mP->mImageB;
   cv::Scalar tColor(255.0);
   int tThickness = -1;
   int tLineType = 8;
   int tShift = 0;

   // Draw circle.
   cv::rectangle(
      aImage,
      tPoint1,
      tPoint2,
      tColor,
      tThickness,
      tLineType,
      tShift);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace