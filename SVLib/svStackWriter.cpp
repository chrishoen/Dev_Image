/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svStackWriter.h"

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

StackWriter::StackWriter()
{
}

StackWriter::~StackWriter()
{
   finalize();
}

StackWriter::StackWriter(StackParms* aParms)
{
   initialize(aParms);
}

void StackWriter::finalize()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void StackWriter::initialize(StackParms* aParms)
{
   // Deallocate memory, if already allocated.
   finalize();

   // Store parms.
   mP = aParms;

   // Initialize variables.
   mWriteCount = 0;

   mOutputImage.release();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write an image stack, according to the parms.

void StackWriter::doWriteStack()
{
   Prn::print(0, "StackWriter::doWriteStack");

   // Loop to write all of the stack images.
   for (int tStackIndex = 0; tStackIndex < mP->mStackSize; tStackIndex++)
   {
      // Initialize the output image to all zeros.
      createZeroImage(mOutputImage);

      // Loop for all of the stack objects to write to the output image.
      for (int tObjectIndex = 0; tObjectIndex < StackParms::cMaxObjects; tObjectIndex++)
      {
         // If the object is valid.
         if (mP->mObjectParms->mValid)
         {
            // Initialize the object writer with the object parms.
            mObjectWriter.initialize(&mP->mObjectParms[tObjectIndex]);
            // Write the object slice to the output image.
            mObjectWriter.doWriteStackObject(tStackIndex, mOutputImage);
         }
      }

      // Write the stack output image.
      doWriteOutputImage();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write the output image to a file.

void StackWriter::doWriteOutputImage()
{
   // Get output file path.
   char tFilePath[200];
   int tFileNum = mP->mStackSize - mWriteCount - 1;
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