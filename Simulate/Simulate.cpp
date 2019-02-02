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
// This selects a test.

void Simulate::doRun(int aCode)
{
   switch (aCode)
   {
   case 1: doRun1(); break;
   case 2: doRun2(); break;
   case 3: doRun3(); break;
   }
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
   SV::showImageInfo("InputImage", mInputImage);

   // Convert simulated image to target image and display.
   cv::Mat tTargetImage;
   SV::convertImageToTarget(mInputImage, tTargetImage);
   SV::showImageInfo("TargetImage", tTargetImage);
   Display::showImage(tTargetImage);

   // Save simulated image.
   SV::writeImageToFile(mInputImage, SV::gImageParms.mInputImageFileName);
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
   SV::showImageInfo("OutputImage", mOutputImage);

   // Convert simulated image to target image and display.
   cv::Mat tTargetImage;
   SV::convertImageToTarget(mOutputImage, tTargetImage);
   SV::showImageInfo("TargetImage", tTargetImage);
   Display::showImage(tTargetImage);

   // Save simulated image.
   SV::writeImageToFile(mOutputImage, SV::gImageParms.mOutputImageFileName);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This runs a test.

void Simulate::doRun3()
{
   Prn::print(Prn::View01, "RUN3********************************************************************");
   Prn::print(Prn::View01, "RUN3********************************************************************");
   Prn::print(Prn::View01, "RUN3********************************************************************");

   // Generate simulated image.
   SV::SimImageGenerator tGenerator(&SV::gSimParms.mImageGenParms);
   tGenerator.doGenerateImage(mInputImage);
   SV::showImageInfo("InputImage", mInputImage);

   // Filter simulated image.
   SV::ImageFilter tFilter(&SV::gImageParms.mFilterParms);
   tFilter.doFilterImage(mInputImage, mOutputImage);
   SV::showImageInfo("OutputImage", mOutputImage);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This runs a test.

void Simulate::doShow(int aCode)
{
   switch (aCode)
   {
   case 1: SV::showImageTableFloat("InputImage", mInputImage); break;
   case 2: SV::showImageTableFloat("OutputImage", mOutputImage); break;
   case 3: SV::showImageTableByte("InputImage", mInputImage); break;
   case 4: SV::showImageTableByte("OutputImage", mOutputImage); break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
