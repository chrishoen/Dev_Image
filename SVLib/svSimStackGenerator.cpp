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

   // Calculate the stack size from the parms.
   doCalculateStackSize();

   // Apply the morph filters.
   doApplyMorphFilter(&mP->mStackMorphParmsA);
   doApplyMorphFilter(&mP->mStackMorphParmsB);
   doApplyMorphFilter(&mP->mStackMorphParmsC);
   doApplyMorphFilter(&mP->mStackMorphParmsD);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the stack size from the parms.

void SimStackGenerator::doCalculateStackSize()
{
   mStackSize = 0;

   // ParmsA
   if (mP->mStackMorphParmsA.mValid)
   {
      mStackSize += mP->mStackMorphParmsA.mRepeatNum * mP->mStackMorphParmsA.mWriteNum;
      if (mP->mStackMorphParmsA.mWriteFirst) mStackSize++;
   }

   // ParmsB
   if (mP->mStackMorphParmsB.mValid)
   {
      mStackSize += mP->mStackMorphParmsB.mRepeatNum * mP->mStackMorphParmsB.mWriteNum;
      if (mP->mStackMorphParmsB.mWriteFirst) mStackSize++;
   }

   // ParmsC
   if (mP->mStackMorphParmsC.mValid)
   {
      mStackSize += mP->mStackMorphParmsC.mRepeatNum * mP->mStackMorphParmsC.mWriteNum;
      if (mP->mStackMorphParmsC.mWriteFirst) mStackSize++;
   }

   // ParmsD
   if (mP->mStackMorphParmsD.mValid)
   {
      mStackSize += mP->mStackMorphParmsD.mRepeatNum * mP->mStackMorphParmsD.mWriteNum;
      if (mP->mStackMorphParmsD.mWriteFirst) mStackSize++;
   }

   Prn::print(Prn::View01, "doCalculateStackSize %d", mStackSize);
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

   // Generate the first output image.
   if (aParms->mGenerateFirst)
   {
      mMorphFilter.doGenerateFirstImage(mOutputImage);
      SV::showImageInfo(Prn::View01, "FirstOutputImage", mOutputImage);

      // Write the first image.
      if (aParms->mWriteFirst)
      {
         doWriteOutputImage();
      }
   }

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
   int tFileNum = mStackSize - mWriteCount - 1;
   sprintf(tFilePath, ".\\work\\%s%04d.png", mP->mStackName, tFileNum);
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