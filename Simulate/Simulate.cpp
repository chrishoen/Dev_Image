/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svDefs.h"
#include "svSimImageGenerator.h"
#include "svContourPixelMiner.h"
#include "svImageParms.h"
#include "svSimParms.h"
#include "svImageFunctions.h"
#include "svImageShow.h"
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

void Simulate::doTest(int aCode)
{
   switch (aCode)
   {
   case 1: doTest1(); break;
   case 2: doTest2(); break;
   }
}

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

void Simulate::doTest1()
{
   // Read a test image file to the input image.
   SV::readImageFromFile(mInputImage, SV::gImageParms.mTestImageFileName);
   SV::showImageInfo("InputImage", mInputImage);

   // Display the input image.
   Display::showImage(mInputImage);
}

void Simulate::doTest2()
{
   // Read a test image file to the input image.
   SV::readImageFromFile(mInputImage, SV::gImageParms.mTestImageFileName);
   SV::showImageInfo("InputImage", mInputImage);

   // Display the input image.
   Display::showImage(SV::gImageParms.mTestImageFileName);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This runs a test.

void Simulate::doRun1()
{
   Prn::print(Prn::View01, "RUN1********************************************************************");
   Prn::print(Prn::View01, "RUN1********************************************************************");
   Prn::print(Prn::View01, "RUN1********************************************************************");

   // Generate simulated image.
   SV::SimImageGenerator tGenerator(&SV::gSimParms.mImageGenParms);
   tGenerator.doGenerateImage(mInputImage);
   SV::showImageInfo("InputImage", mInputImage);

   // Display the input image.
   Display::showImage(mInputImage);

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

   // Mine contour pixels from the simulated image.
   SV::ContourPixelMiner tMiner(&SV::gImageParms.mContourFilterParms);
   tMiner.doMineImage(mInputImage,mRecordList);

   // Show the record list.
   mRecordList.show(0);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This runs a test.

void Simulate::doRun3()
{
#if 0
   Prn::print(Prn::View01, "RUN3********************************************************************");
   Prn::print(Prn::View01, "RUN3********************************************************************");
   Prn::print(Prn::View01, "RUN3********************************************************************");

   // Generate simulated image.
   SV::SimImageGenerator tGenerator(&SV::gSimParms.mImageGenParms);
   tGenerator.doGenerateImage(mInputImage);
   SV::showImageInfo("InputImage", mInputImage);

   // Filter simulated image.
   SV::ContourFilter tFilter(&SV::gImageParms.mContourFilterParms);
   tFilter.doFilterImage(mInputImage, mOutputImage);
   SV::showImageInfo("OutputImage", mOutputImage);
#endif
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
// Convert simulated image to target image and display.
//Display::showImage(mOutputImage);
// Save simulated image.
//SV::writeImageToFile(mOutputImage, SV::gImageParms.mOutputImageFileName);
