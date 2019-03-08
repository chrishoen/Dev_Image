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
   mStackIndex = 0;
   mOutputImage.release();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write an image stack, according to the parms.

void StackWriter::doWriteStack()
{
   Prn::print(0, "StackWriter::doWriteStack");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Write the objects.

   // Loop to write all of the object stack images.
   for (int tObjectStackIndex = 0; tObjectStackIndex < mP->mObjectHeight; tObjectStackIndex++)
   {
      // Initialize the output image to all zeros.
      createZeroImage(mOutputImage);

      // Loop for all of the stack objects to write to the output image.
      for (int tObjectIndex = 0; tObjectIndex < StackParms::cMaxObjects; tObjectIndex++)
      {
         // If the object is valid.
         if (mP->mObjectParms[tObjectIndex].mValid)
         {
            // Initialize the object writer with the object parms.
            mObjectWriter.initialize(&mP->mObjectParms[tObjectIndex]);
            // Write the object slice to the output image.
            mObjectWriter.doWriteStackObject(tObjectStackIndex, mOutputImage);
         }
      }

      // Write the stack output image.
      int tReverseIndex = mP->mStackHeight - mStackIndex - 1;
      doWriteOutputImage(tReverseIndex);

      // Update.
      mStackIndex++;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Write the rafts.

   // Loop to write all of the object stack images.
   for (int tRaftStackIndex = 0; tRaftStackIndex < mP->mRaftHeight; tRaftStackIndex++)
   {
      // Initialize the output image to all zeros.
      createZeroImage(mOutputImage);

      // Loop for all of the stack objects to write to the output image.
      for (int tRaftIndex = 0; tRaftIndex < StackParms::cMaxRafts; tRaftIndex++)
      {
         // If the object is valid.
         if (mP->mRaftParms[tRaftIndex].mValid)
         {
            // Initialize the object writer with the object parms.
            mObjectWriter.initialize(&mP->mRaftParms[tRaftIndex]);
            // Write the object slice to the output image.
            mObjectWriter.doWriteStackObject(tRaftStackIndex, mOutputImage);
         }
      }

      // Write the stack output image.
      int tReverseIndex = mP->mStackHeight - mStackIndex - 1;
      doWriteOutputImage(tReverseIndex);

      // Update.
      mStackIndex++;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write the output image to a file.

void StackWriter::doWriteOutputImage(int aReverseIndex)
{
   // Get output file path.
   char tFilePath[200];
   sprintf(tFilePath, ".\\work\\%s%04d.png", mP->mStackName, aReverseIndex);
   Prn::print(Prn::View01, "WriteOutput %s", tFilePath);

   // Write output file.
   cv::imwrite(tFilePath, mOutputImage);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace