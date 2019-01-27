/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svPointParms.h"
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
// Generate a simulated image that contains a noise floor image.

void SimImageSynthesizer::doGenerateNoiseFloor(
   cv::Mat&         aNoiseFloor)   // Output
{
   // Set all zeroes for the noise floor image matrix.
   aNoiseFloor = cv::Mat::zeros(gSysParms.mSensorSize.mRows, gSysParms.mSensorSize.mCols, CV_16U);

   // Write the image to an output file.
   cv::imwrite(gPointParms.mNoiseFloorFileName, aNoiseFloor);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate a simulated image for a filtered image.

void SimImageSynthesizer::doGenerateFilteredImage(
   cv::Point2d&     aImagePoint,         // Input
   cv::Mat&         aImage)              // Output
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Set the simulated image matrix to all zeroes.

   // Set all zeroes for the noise floor image matrix.
   aImage = cv::Mat::zeros(gSysParms.mSensorSize.mRows, gSysParms.mSensorSize.mCols, CV_16U);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Write a pulse to the simulated image matrix.

   doGeneratePulse1(aImagePoint, aImage);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Save the image matrices to files.

   // Write the image to an output file.
   cv::imwrite(gPointParms.mFilteredImageFileName,   aImage);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate a simulated pulse at an image point.

void SimImageSynthesizer::doGeneratePulse1(
   cv::Point2d&     aImagePoint,  // Input
   cv::Mat&         aImage)       // InOut
{
   // Store image point as center point.
   cv::Point2d& tCenterPoint = aImagePoint;

   // Convert image point to center pixel.
   RCIndex tCenterPixel;
   convertImagePointToPixel(aImagePoint,tCenterPixel);

// Prn::print(0,"ImagePoint  %10.6f %10.6f",aImagePoint.x,aImagePoint.y);
// Prn::print(0,"CenterPixel %10d %10d",   tCenterPixel.mRow,tCenterPixel.mCol);

   // Loop through all of the rows and columns of the pulse.
   // Set pulse pixels in the image matrix.
   for (int iRowY = -mP->mPulsePixelWidth/2; iRowY <= mP->mPulsePixelWidth/2; iRowY++)
   {
      for (int iColX = -mP->mPulsePixelWidth/2; iColX <= mP->mPulsePixelWidth/2; iColX++)
      {
         // Calculate indices of the pixel to set.
         int tPixelRowY = tCenterPixel.mRow + iRowY;
         int tPixelColX = tCenterPixel.mCol + iColX;

         // Convert the pixel to a point.
         double tPointRowY;
         double tPointColX;
         convertImagePixelXYToPoint (tPixelColX,tPixelRowY,tPointColX,tPointRowY);

         // Calculate the amplitude, based on a gaussian function.
         double tTwoSigmaSq = 2.0*(mP->mPulseGaussianWidth*mP->mPulseGaussianWidth);
         double tTermX = tPointColX - tCenterPoint.x;
         double tTermY = tPointRowY - tCenterPoint.y;
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
// Generate a simulated pulse at an image point.

void SimImageSynthesizer::doGeneratePulse2(
   cv::Point2d&     aImagePoint,  // Input
   cv::Mat&         aImage)       // InOut
{
   // Store image point as center point.
   cv::Point2d& tCenterPoint = aImagePoint;

   // Convert image point to center pixel.
   RCIndex tCenterPixel;
   convertImagePointToPixel(aImagePoint,tCenterPixel);

   Prn::print(0,"CenterPixel %d %d",tCenterPixel.mRow,tCenterPixel.mCol);

   // Loop through all of the rows and columns of the pulse.
   // Set pulse pixels in the image matrix.
   for (int iRowY = -mP->mPulsePixelWidth/2; iRowY <= mP->mPulsePixelWidth/2; iRowY++)
   {
      for (int iColX = -mP->mPulsePixelWidth/2; iColX <= mP->mPulsePixelWidth/2; iColX++)
      {
         // Calculate indices of the pixel to set.
         int tPixelRowY = tCenterPixel.mRow + iRowY;
         int tPixelColX = tCenterPixel.mCol + iColX;

         // Calculate the amplitude, based on a gaussian function.
         double tTwoSigmaSq = 2.0*(mP->mPulseGaussianWidth*mP->mPulseGaussianWidth);
         double tTermX = iColX*gSysParms.mSensorMMPerPixel;
         double tTermY = iRowY*gSysParms.mSensorMMPerPixel;
         double tTermG = exp(-(tTermX*tTermX + tTermY*tTermY)/tTwoSigmaSq);

         // Set the pixel.
         aImage.at<ushort>(tPixelRowY, tPixelColX) = (ushort)(mP->mPulseAmplitude*256.0*tTermG);
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace