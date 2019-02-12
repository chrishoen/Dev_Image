/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svImageParms.h"
#include "svSimParms.h"

#include "svSimImageGenerator.h"

#include "svImageFunctions.h"
#include "svImageShow.h"

#include "displayFunctions.h"

#include "ImageSet.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

ImageSet::ImageSet()
{
}

void ImageSet::reset()
{
   mInputImage.release();
   mOutputImage.release();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This runs a test.

void ImageSet::doSimInput()
{
   Prn::print(Prn::View11, "RUN1********************************************************************");
   Prn::print(Prn::View11, "RUN1********************************************************************");
   Prn::print(Prn::View11, "RUN1********************************************************************");

   // Generate simulated image.
   SV::SimImageGenerator tGenerator(&SV::gSimParms.mImageGenParms);
   tGenerator.doGenerateImage(mInputImage);
   SV::showImageInfo(Prn::View11,"InputImage", mInputImage);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read and write images.

void ImageSet::doReadInput()
{
   // Read a test image file to the input image.
   SV::readImageFromFile(mInputImage, SV::gImageParms.mTestImageFileName);
   SV::showImageInfo(Prn::View11, "InputImage", mInputImage);
}

void ImageSet::doWriteInput()
{
   // Save image.
   SV::showImageInfo(Prn::View11, "InputImage", mInputImage);
   SV::writeImageToFile(mInputImage, SV::gImageParms.mInputImageFileName);
}

void ImageSet::doWriteOutput()
{
   // Save image.
   SV::showImageInfo(Prn::View11, "OutputImage", mOutputImage);
   SV::writeImageToFile(mOutputImage, SV::gImageParms.mOutputImageFileName);
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show images.

void ImageSet::doShow(int aCode)
{
   switch (aCode)
   {
   case 11: SV::showImageTable1("InputImage", mInputImage); break;
   case 12: SV::showImageTable2("InputImage", mInputImage); break;
   case 13: SV::showImageTable3("InputImage", mInputImage); break;
   case 1:  SV::showImageTable2("InputImage", mInputImage); break;

   case 21: SV::showImageTable1("OutputImage", mOutputImage); break;
   case 22: SV::showImageTable2("OutputImage", mOutputImage); break;
   case 23: SV::showImageTable3("OutputImage", mOutputImage); break;
   case 2:  SV::showImageTable2("OutputImage", mOutputImage); break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// 

void ImageSet::doDraw(int aCode)
{
   switch (aCode)
   {
   case 11:  Display::showImage(mInputImage); break;
   case 12:  Display::showImage(SV::gImageParms.mInputImageFileName); break;
   case 21:  Display::showImage(mOutputImage); break;
   case 22:  Display::showImage(SV::gImageParms.mOutputImageFileName); break;
   case 9:   Display::showImage(SV::gImageParms.mTestImageFileName); break;
   }
}
