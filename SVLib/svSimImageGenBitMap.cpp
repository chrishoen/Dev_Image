/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svDefs.h"

#include "svSimImageGenBitMap.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

SimImageGenBitMap::SimImageGenBitMap()
{
   reset();
}

SimImageGenBitMap::SimImageGenBitMap(SimImageGenParms* aParms)
{
   BaseClass::mP = aParms;
   reset();
}

void SimImageGenBitMap::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the image, depending on the parms.

void SimImageGenBitMap::doGenerateImage(
   cv::Mat&       aImage)          // Output
{
   Prn::print(0, "SimImageGenBitMap::doGenerateImage");
   // Create an image filled with all zeros.
   BaseClass::doCreateZeroImage(aImage);

   // BitMap variables. 
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