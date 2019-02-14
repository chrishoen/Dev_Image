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
   mInputImageC.release();
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
   tGenerator.doGenerateImage(mInputImageC);
   SV::showImageInfo(Prn::View11,"InputImage", mInputImageC);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read and write images.

void ImageSet::doReadInput()
{
   // Read a test image file to the input image.
   SV::readImageFromFile(mInputImageC, SV::gImageParms.mInputImageCFileName);
   SV::showImageInfo(Prn::View11, "InputImage", mInputImageC);
   SV::showImageInfo(0, SV::gImageParms.mInputImageCFileName, mInputImageC);
}

void ImageSet::doReadOutput()
{
   // Read a test image file to the Output image.
   SV::readImageFromFile(mOutputImage, SV::gImageParms.mOutputImageFileName);
   SV::showImageInfo(Prn::View11, "OutputImage", mOutputImage);
   SV::showImageInfo(0, SV::gImageParms.mOutputImageFileName, mOutputImage);
}

void ImageSet::doWriteInput()
{
   // Save image.
   SV::showImageInfo(Prn::View11, "InputImage", mInputImageC);
   SV::writeImageToFile(mInputImageC, SV::gImageParms.mInputImageCFileName);
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

void ImageSet::doShow2d(int aCode)
{
   switch (aCode)
   {
   case 1:  SV::showImage2d("InputImage", mInputImageC); break;

   case 2:  SV::showImage2d("OutputImage", mOutputImage); break;
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
   case 11:  Display::showImage(mInputImageC); break;
   case 12:  Display::showImage(SV::gImageParms.mInputImageCFileName); break;
   case 21:  Display::showImage(mOutputImage); break;
   case 22:  Display::showImage(SV::gImageParms.mOutputImageFileName); break;
   }
}
