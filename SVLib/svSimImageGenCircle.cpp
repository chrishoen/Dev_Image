/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"

#include "svSimImageGenCircle.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

SimImageGenCircle::SimImageGenCircle()
{
   reset();
}

SimImageGenCircle::SimImageGenCircle(SimImageGenParms* aParms)
{
   BaseClass::mP = aParms;
   reset();
}

void SimImageGenCircle::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the image, depending on the parms.

void SimImageGenCircle::doGenerateImage(
   cv::Mat&       aImage)          // Output
{
   Prn::print(0, "SimImageGenCircle::doGenerateImage");
   // Create an image filled with all zeros.
   BaseClass::doCreateZeroImage(aImage);

   // Circle variables. 
   int tCenterRow = mP->mImageSize.mRows / 2;
   int tCenterCol = mP->mImageSize.mCols / 2;
   cv::Point tCenter(tCenterCol,tCenterRow);
   int tRadius = mP->mImageB;
   cv::Scalar tColor(255.0);
   int tThickness = -1;
   int tLineType = 8;
   int tShift = 0;

   // Draw circle.
   cv::circle(
      aImage,
      tCenter,
      tRadius,
      tColor,
      tThickness,
      tLineType,
      tShift);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace