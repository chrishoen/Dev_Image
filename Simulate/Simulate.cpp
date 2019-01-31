/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svDefs.h"
#include "svSimImageGenerator.h"
#include "svImageFilter.h"
#include "svImageParms.h"
#include "svSimParms.h"
#include "svImageFunctions.h"
#include "displayFunctions.h"
#include "Simulate.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

Simulate::Simulate()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This runs a test.

void Simulate::doRun1()
{
   Prn::print(Prn::View01,"RUN1********************************************************************");
   Prn::print(Prn::View01,"RUN1********************************************************************");
   Prn::print(Prn::View01,"RUN1********************************************************************");

   // Generate simulated image.
   SV::SimImageGenerator tGenerator(&SV::gSimParms.mImageGenParms);
   tGenerator.doGenerateImage(mInputImage);
   SV::showImageInfo(0,"InputImage", mInputImage);

   // Convert simulated image to target image and display.
   cv::Mat tTargetImage;
   SV::convertImageToTarget(mInputImage, tTargetImage);
   SV::showImageInfo(0, "TargetImage", tTargetImage);
   Display::showImage(tTargetImage);

   // Save simulated image.
   SV::writeImageToFile(mInputImage, SV::gImageParms.mInputImageFileName);

   // Extract region of interest from simulated image.
   SV::extractImageRoi(mInputImage, mInputRoi);
   SV::showImageInfo(0, "InputRoi", mInputRoi);

   // Save roi image.
   SV::writeImageToFile(mInputRoi, SV::gImageParms.mInputRoiFileName);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This runs a test.

void Simulate::doRun2()
{
   Prn::print(Prn::View01, "RUN2********************************************************************");
   Prn::print(Prn::View01, "RUN2********************************************************************");
   Prn::print(Prn::View01, "RUN2********************************************************************");

   // Filter simulated image.
   SV::ImageFilter tFilter(&SV::gImageParms.mFilterParms);
   tFilter.doFilterImage(mInputImage,mOutputImage);
   SV::showImageInfo(0, "OutputImage", mOutputImage);

   // Convert simulated image to target image and display.
   cv::Mat tTargetImage;
   SV::convertImageToTarget(mOutputImage, tTargetImage);
   SV::showImageInfo(0, "TargetImage", tTargetImage);
   Display::showImage(tTargetImage);

   // Save simulated image.
   SV::writeImageToFile(mOutputImage, SV::gImageParms.mOutputImageFileName);

   // Extract region of interest from simulated image.
   SV::extractImageRoi(mOutputImage, mOutputRoi);
   SV::showImageInfo(0, "OutputRoi", mOutputRoi);

   // Save roi image.
   SV::writeImageToFile(mOutputRoi, SV::gImageParms.mOutputRoiFileName);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
