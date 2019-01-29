/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSimImageGenBase.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create an image filled with all zeros.

void SimImageGenBase::doCreateZeroImage(
   cv::Mat&       aImage)             // Output
{
   // Create an image filled with all zeros.
   aImage = cv::Mat::zeros(mP->mImageSize.mRows, mP->mImageSize.mCols, CV_8UC3);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace