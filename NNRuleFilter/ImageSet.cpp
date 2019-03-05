/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svImageParms.h"
#include "svTestParms.h"
#include "svSimParms.h"
#include "svStackParms.h"

#include "svSimImageGenerator.h"
#include "svTileWriter.h"

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
   mInputS2.release();
   mOutput.release();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This simulates an input image.

void ImageSet::doSimInputTile2d()
{
   // Generate simulated image.
   SV::createZeroImage(mInputS2);
   SV::TileWriter tWriter(&SV::gTestParms.mTileParms);
   tWriter.doWrite(mInputS2);
   SV::showImageInfo(Prn::View01,"InputS2", mInputS2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This simulates an input image.

void ImageSet::doSimInput2d()
{
   // Generate simulated image.
   SV::SimImageGenerator tGenerator(&SV::gSimParms.mImageGenParmsS2);
   tGenerator.doGenerateImage(mInputS2);
   SV::showImageInfo(Prn::View01, "InputS2", mInputS2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This simulates an input image.

void ImageSet::doSimInput3d()
{
   // Generate simulated image.
   SV::SimImageGenerator tGenerator;
   tGenerator.initialize(&SV::gSimParms.mImageGenParmsS1);
   tGenerator.doGenerateImage(mInputS1);
   tGenerator.initialize(&SV::gSimParms.mImageGenParmsS2);
   tGenerator.doGenerateImage(mInputS2);
   tGenerator.initialize(&SV::gSimParms.mImageGenParmsS3);
   tGenerator.doGenerateImage(mInputS3);

   SV::showImageInfo(Prn::View01, "InputS1", mInputS1);
   SV::showImageInfo(Prn::View01, "InputS2", mInputS2);
   SV::showImageInfo(Prn::View01, "InputS3", mInputS3);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read and write images.

void ImageSet::doReadInput()
{
   // Read a test image file to the input image.
   SV::readImageFromFile(mInputS2, SV::gImageParms.mInputImageFileName);
   SV::showImageInfo(Prn::View11, "InputS2", mInputS2);
   SV::showImageInfo(0, SV::gImageParms.mInputImageFileName, mInputS2);
}

void ImageSet::doReadOutput()
{
   // Read a test image file to the Output image.
   SV::readImageFromFile(mOutput, SV::gImageParms.mOutputImageFileName);
   SV::showImageInfo(Prn::View11, "Output", mOutput);
   SV::showImageInfo(0, SV::gImageParms.mOutputImageFileName, mOutput);
}

void ImageSet::doWriteInput()
{
   // Save image.
   SV::showImageInfo(Prn::View11, "Input", mInputS2);
   SV::writeImageToFile(mInputS2, SV::gImageParms.mInputImageFileName);
}

void ImageSet::doWriteOutput()
{
   // Save image.
   SV::showImageInfo(Prn::View11, "Output", mOutput);
   SV::writeImageToFile(mOutput, SV::gImageParms.mOutputImageFileName);
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show images.

void ImageSet::doShow2d(int aCode)
{
   switch (aCode)
   {
   case 1:  SV::showImage2d("Input", mInputS2); break;
   case 2:  SV::showImage2d("Output", mOutput); break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show images.

void ImageSet::doShow3d(int aCode)
{
   switch (aCode)
   {
   case 1:  SV::showImage3d("Input", mInputS1, mInputS2, mInputS3); break;
   case 2:  SV::showImage2d("Output", mOutput); break;
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
   case 11:  Display::showImage(mInputS2); break;
   case 12:  Display::showImage(SV::gImageParms.mInputImageFileName); break;
   case 21:  Display::showImage(mOutput); break;
   case 22:  Display::showImage(SV::gImageParms.mOutputImageFileName); break;
   }
}
