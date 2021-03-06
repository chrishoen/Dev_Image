/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svImageWrapper.h"

#include "svSimImageGenImpulse.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

SimImageGenImpulse::SimImageGenImpulse()
{
   reset();
}

SimImageGenImpulse::SimImageGenImpulse(SimImageGenParms* aParms)
{
   BaseClass::mP = aParms;
   reset();
}

void SimImageGenImpulse::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the image, depending on the parms.

void SimImageGenImpulse::doGenerateImage(
   cv::Mat&       aImage)          // Output
{
   Prn::print(0, "SimImageGenImpulse::doGenerateImage");
   // Create an image filled with all zeros.
   BaseClass::doCreateZeroImage(aImage);

   // Image wrapper.
   ImageWrapper tImage(aImage);

   // Impulse variables. 
   RCIndex tCenter(mP->mImageSize.mRows / 2, mP->mImageSize.mCols / 2);

   // Set center pixel.
   tImage.setScaled(tCenter, 100.0);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace