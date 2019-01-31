/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svDefs.h"
#include "svSimImageGenerator.h"
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
// This runs a test on the grid sequencer.

void Simulate::doRun1(int  aCode)
{
   Prn::print(Prn::View01,"RUN1********************************************************************%3d",aCode);
   Prn::print(Prn::View01,"RUN1********************************************************************");
   Prn::print(Prn::View01,"RUN1********************************************************************");

   // Generate simulated image.
   cv::Mat tSimImage;
   SV::SimImageGenerator tGenerator(&SV::gSimParms.mImageGenParms);
   tGenerator.doGenerateImage(tSimImage);
   SV::showImageInfo(0,"SimImage",tSimImage);

   // Convert simulated image to target image.
   cv::Mat tTargetImage;
   SV::convertImageToTarget(tSimImage, tTargetImage);
   SV::showImageInfo(0, "TargetImage", tTargetImage);

   // Display target image.
   Display::showImage(tTargetImage);

   // Save simulated image.
   SV::writeImageToFile(tSimImage, SV::gImageParms.mImageFileName1);

   // Extract region of interest from simulated image.
   cv::Mat tRoiImage;
   SV::extractImageRoi(tSimImage, tRoiImage);
   SV::showImageInfo(0, "RoiImage", tRoiImage);

   // Save roi image.
   SV::writeImageToFile(tRoiImage, SV::gImageParms.mImageFileName2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
