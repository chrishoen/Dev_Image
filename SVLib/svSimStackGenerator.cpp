/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSimStackGenerator.h"

#include "svImageFunctions.h"
#include "svImageShow.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Infastruccture.

SimStackGenerator::SimStackGenerator()
{
}

SimStackGenerator::~SimStackGenerator()
{
   finalize();
}

SimStackGenerator::SimStackGenerator(SimParms* aParms)
{
   initialize(aParms);
}

void SimStackGenerator::finalize()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SimStackGenerator::initialize(SimParms* aParms)
{
   // Deallocate memory, if already allocated.
   finalize();

   // Store parms.
   mP = aParms;

   // Initialize variables.
   mStackSize = 0;
   mImageFilePaths.clear();

   mInputImage.release();
   mOutputImage.release();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate an image stack, depending on the parms.

void SimStackGenerator::doGenerateImageStack()
{
   Prn::print(0, "SimStackGenerator::doGenerateStack");
   // Set the stack size.
   mStackSize = mP->mStackSize;

   // Initialize the file paths.
   doSetImageFilePaths();


   // Initialize the morph filter.
   mMorphFilter.initialize(&SV::gSimParms.mStackMorphParms);

   // Initialize the first output image.
   mMorphFilter.doInitializeImage(mOutputImage);
   SV::showImageInfo(Prn::View01, "OutputImage", mOutputImage);

   // Loop for each generated image, top down.
   for (int tLoopIndex = 0; tLoopIndex < mStackSize; tLoopIndex++)
   {
      // Write the output image to a file.
      doWriteOutputImage(tLoopIndex);

      // Copy the output image to the input image.
      mInputImage = mOutputImage;
      
      // Morph the input into a new output,
      mMorphFilter.doFilterImage(mInputImage, mOutputImage);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set the image file paths.

void SimStackGenerator::doSetImageFilePaths()
{
   // Set the stack size.
   mStackSize = mP->mStackSize;
   mImageFilePaths.clear();

   // Set the image file path.
   for (int i = 0; i < mStackSize; i++)
   {
      char tFilePath[200];
      sprintf(tFilePath, ".\\work\\%s%04d.png", mP->mStackName,i);
      Prn::print(Prn::View11,"FilePath %s", tFilePath);
      mImageFilePaths.push_back(tFilePath);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write the output image to a file.

void SimStackGenerator::doWriteOutputImage(int aIndex)
{
   Prn::print(Prn::View01, "WriteOutput %s", mImageFilePaths[aIndex].c_str());
   cv::imwrite(mImageFilePaths[aIndex].c_str(), mOutputImage);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace