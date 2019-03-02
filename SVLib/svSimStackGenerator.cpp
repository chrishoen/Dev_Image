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
   doApplyMorphFilter(&mP->mMorphParmsA);
   doApplyMorphFilter(&mP->mMorphParmsB);
   doApplyMorphFilter(&mP->mMorphParmsC);
   doApplyMorphFilter(&mP->mMorphParmsD);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the stack size from the parms.

void SimStackGenerator::doCalculateStackSize()
{
   mStackSize = 0;

   // ParmsA
   if (mP->mMorphParmsA.mValid)
   {
      mStackSize += mP->mMorphParmsA.mRepeatNum * mP->mMorphParmsA.mWriteNum;
      if (mP->mMorphParmsA.mWriteFirst) mStackSize++;
   }

   // ParmsB
   if (mP->mMorphParmsB.mValid)
   {
      mStackSize += mP->mMorphParmsB.mRepeatNum * mP->mMorphParmsB.mWriteNum;
      if (mP->mMorphParmsB.mWriteFirst) mStackSize++;
   }

   // ParmsC
   if (mP->mMorphParmsC.mValid)
   {
      mStackSize += mP->mMorphParmsC.mRepeatNum * mP->mMorphParmsC.mWriteNum;
      if (mP->mMorphParmsC.mWriteFirst) mStackSize++;
   }

   // ParmsD
   if (mP->mMorphParmsD.mValid)
   {
      mStackSize += mP->mMorphParmsD.mRepeatNum * mP->mMorphParmsD.mWriteNum;
      if (mP->mMorphParmsD.mWriteFirst) mStackSize++;
   }

   Prn::print(Prn::View01, "doCalculateStackSize %d", mStackSize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Apply a morph filter to generate output images.

void SimStackGenerator::doApplyMorphFilter(MorphParms* aParms)
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