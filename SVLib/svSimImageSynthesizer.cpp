/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risAlphaDir.h"

#include "svSysParms.h"
#include "svSimParms.h"
#include "svPixelFunctions.h"

#include "svSimImageSynthesizer.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Infrastructure.

SimImageSynthesizer::SimImageSynthesizer()
{
}

SimImageSynthesizer::SimImageSynthesizer(SimParms* aSimParms)
{
   mP = aSimParms;
   reset();
}

void SimImageSynthesizer::initialize(SimParms* aSimParms)
{
   mP = aSimParms;
   reset();
}

void SimImageSynthesizer::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate a simulated image for a filtered image.

void SimImageSynthesizer::doGenerateImage(
   cv::Mat&         aImage)              // Output
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Set the simulated image matrix to all zeroes.

   // Set all zeroes for the noise floor image matrix.
   aImage = cv::Mat::zeros(gSysParms.mImageSize.mRows, gSysParms.mImageSize.mCols, CV_16U);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Write a pulse to the simulated image matrix.

   doGeneratePulse1(mP->mCenterPixel, aImage);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Save the image matrices to files.

   // Write the image to an output file.
   char tBuffer[100];
   cv::imwrite(Ris::getAlphaFilePath_Image(tBuffer, mP->mImageFileName), aImage);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate a simulated pulse at an image point.

void SimImageSynthesizer::doGeneratePulse1(
   SV::RCIndex      aCenterPixel,  // Input
   cv::Mat&         aImage)        // InOut
{
// Prn::print(0,"ImagePoint  %10.6f %10.6f",aImagePoint.x,aImagePoint.y);
// Prn::print(0,"CenterPixel %10d %10d",   tCenterPixel.mRow,tCenterPixel.mCol);

   // Loop through all of the rows and columns of the pulse.
   // Set pulse pixels in the image matrix.
   for (int iRowY = -mP->mPulsePixelWidth/2; iRowY <= mP->mPulsePixelWidth/2; iRowY++)
   {
      for (int iColX = -mP->mPulsePixelWidth/2; iColX <= mP->mPulsePixelWidth/2; iColX++)
      {
         // Calculate indices of the pixel to set.
         int tPixelRowY = aCenterPixel.mRow + iRowY;
         int tPixelColX = aCenterPixel.mCol + iColX;

         // Calculate the amplitude, based on a gaussian function.
         double tTwoSigmaSq = 2.0*(mP->mPulseGaussianWidth*mP->mPulseGaussianWidth);
         double tTermX = iColX;
         double tTermY = iRowY;
         double tTermG = exp(-(tTermX*tTermX + tTermY*tTermY)/tTwoSigmaSq);

         // Set the pixel.
         if (isImagePixelInBounds(tPixelColX, tPixelRowY))
         {
            aImage.at<ushort>(tPixelRowY, tPixelColX) = (ushort)(mP->mPulseAmplitude*256.0*tTermG);
         }
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace