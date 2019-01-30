/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svDefs.h"
#include "svPixelFunctions.h"
#include "svImageWrapper.h"

#include "svSimImageGenGaussian.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

SimImageGenGaussian::SimImageGenGaussian()
{
   reset();
}

SimImageGenGaussian::SimImageGenGaussian(SimImageGenParms* aParms)
{
   BaseClass::mP = aParms;
   reset();
}

void SimImageGenGaussian::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the image, depending on the parms.

void SimImageGenGaussian::doGenerateImage(
   cv::Mat&       aImage)          // Output
{
   Prn::print(0, "SimImageGenGaussian::doGenerateImage");
   // Create an image filled with all zeros.
   BaseClass::doCreateZeroImage(aImage);

   // Image wrapper.
   ImageWrapper tImage(aImage);

   // Impulse variables. 
   RCIndex tCenterPixel(mP->mImageSize.mRows / 2, mP->mImageSize.mCols / 2);

   // Set center pixel.
   tImage.setScaled(tCenterPixel, 100.0);


   // Loop through all of the rows and columns of the pulse.
   // Set pulse pixels in the image matrix.
   for (int iRowY = -mP->mImageB; iRowY <= mP->mImageB; iRowY++)
   {
      for (int iColX = -mP->mImageB; iColX <= mP->mImageB; iColX++)
      {
         // Calculate indices of the pixel to set.
         RCIndex tPixel(tCenterPixel.mRow + iRowY, tCenterPixel.mCol + iColX);
         // Calculate the amplitude, based on a gaussian function.
         double tTwoSigmaSq = 2.0*(mP->mGaussianWidth*mP->mGaussianWidth);
         double tTermX = iColX;
         double tTermY = iRowY;
         double tTermG1 = exp(-(tTermX*tTermX + tTermY * tTermY) / tTwoSigmaSq);
         double tTermG2 = mP->mGaussianAmplitude*tTermG1;

         // Set the pixel.
         if (isImagePixelInBounds(tPixel))
         {
            tImage.setScaled(tPixel,tTermG2);
         }
      }
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace