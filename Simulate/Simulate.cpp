/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svDefs.h"
#include "svSimImageGenerator.h"
#include "svContourRecordMiner.h"
#include "svContourArrayWriter.h"
#include "svContourShow.h"
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

   // Mine contour pixel records from the simulated image.
   SV::ContourRecordMiner tMiner(&SV::gImageParms.mContourFilterParms);
   tMiner.doMineImage(
      mInputImage,
      mRecordList);

   // Show the record list.
   showRecordList(Prn::View11, "Run2", mRecordList);

   // Copy the record list to the record array.
   SV::ContourArrayWriter tArrayWriter(&SV::gImageParms.mContourFilterParms);
   tArrayWriter.doWriteArray(
      mInputImage,
      mRecordList,
      mRecordArray);
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

   // Mine contour pixel records from the simulated image.
   SV::ContourRecordMiner tMiner(&SV::gImageParms.mContourFilterParms);
   tMiner.doMineImage(
      mInputImage,
      mRecordList);

   // Copy the record list to the record array.
   SV::ContourArrayWriter tArrayWriter(&SV::gImageParms.mContourFilterParms);
   tArrayWriter.doWriteArray(
      mInputImage,
      mRecordList,
      mRecordArray);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This runs a test.

void Simulate::doShow(int aCode)
{
   switch (aCode)
   {
   case 1:  SV::showImageTableByte("InputImage", mInputImage); break;
   case 20: SV::showRecordArray(0, "InputImage", mRecordArray); break;
   case 21: SV::showRecordArray(1, "InputImage", mRecordArray); break;
   case 3:  SV::showImageTableByte("OutputImage", mOutputImage); break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This runs a test.

void Simulate::doTest(int aCode)
{
   switch (aCode)
   {
   case 1: doTest1(); break;
   case 2: doTest2(); break;
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
// Convert simulated image to target image and display.
//Display::showImage(mOutputImage);
// Save simulated image.
//SV::writeImageToFile(mOutputImage, SV::gImageParms.mOutputImageFileName);
