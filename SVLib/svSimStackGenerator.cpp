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
   mWriteCount = 0;

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

   // Initialize the morph filter.
   mMorphFilter.initialize(&mP->mStackMorphParmsA);

   // Initialize the first output image.
   mMorphFilter.doInitializeImage(mOutputImage);
   SV::showImageInfo(Prn::View01, "OutputImage", mOutputImage);

   // Write the first image.
   if (mP->mStackWriteFirst)
   {
      doWriteOutputImage();
   }

   // Apply the morph filters.
   doApplyMorphFilter(&mP->mStackMorphParmsA);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Apply a morph filter to generate output images.

void SimStackGenerator::doApplyMorphFilter(SimMorphParms* aParms)
{
   // Guard.
   if (!aParms->mValid) return;

   Prn::print(Prn::View01, "doApplyMorphFilter %s",aParms->mName);

   // Initialize the morph filter.
   mMorphFilter.initialize(aParms);

   // Loop for the number of repeats.
   for (int tRepeatCount = 0; tRepeatCount < aParms->mRepeatNum; tRepeatCount++)
   {
      // Loop for the number of morphs.
      for (int tMorphCount = 0; tMorphCount < aParms->mMorphNum; tMorphCount++)
      {
         // Copy the output image to the input image.
         mInputImage = mOutputImage;

         // Morph the input image into a new output image.
         mMorphFilter.doFilterImage(mInputImage, mOutputImage);
      }

      // Loop for the number of writes.
      for (int tWriteCount = 0; tWriteCount < aParms->mWriteNum; tWriteCount++)
      {
         // Write the output image to a file.
         doWriteOutputImage();
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write the output image to a file.

void SimStackGenerator::doWriteOutputImage()
{
   // Get output file path.
   char tFilePath[200];
   sprintf(tFilePath, ".\\work\\%s%04d.png", mP->mStackName, mWriteCount);
   Prn::print(Prn::View01, "WriteOutput %s", tFilePath);

   // Write output file.
   cv::imwrite(tFilePath, mOutputImage);

   // Advance.
   mWriteCount++;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace