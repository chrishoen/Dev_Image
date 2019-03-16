/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "CPrintDir.h"

#include "svImageFunctions.h"
#include "svImageShow.h"

#include "svStackWriter.h"

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
   mReverseIndex = 0;
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

   // Loop to write all of the object stack images from top to bottom.
   for (int tObjectReverseIndex = 0; tObjectReverseIndex < mP->mObjectHeight; tObjectReverseIndex++)
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
            mObjectWriter.doWriteStackObject(tObjectReverseIndex, mOutputImage);
         }
      }

      // Write the stack output image. The reverse index goes from top to 
      // bottom and the stack index goes from bottom to top.
      int tStackIndex = mP->mStackHeight - mReverseIndex - 1;
      doWriteOutputImage(tStackIndex);

      // Update.
      mReverseIndex++;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Write the rafts.

   // Loop to write all of the raft stack images from top to bottom.
   for (int tRaftReverseIndex = 0; tRaftReverseIndex < mP->mRaftHeight; tRaftReverseIndex++)
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
            mObjectWriter.doWriteStackObject(tRaftReverseIndex, mOutputImage);
         }
      }

      // Write the stack output image. The reverse index goes from top to 
      // bottom and the stack index goes from bottom to top.
      int tStackIndex = mP->mStackHeight - mReverseIndex - 1;
      doWriteOutputImage(tStackIndex);

      // Update.
      mReverseIndex++;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write the output image to a file based on the stack index.

void StackWriter::doWriteOutputImage(int aStackIndex)
{
   // Get output file path.
   char tFilePath[200];
   sprintf(tFilePath, "%s%s%04d.png", CPrint::getWorkDirPath().c_str(),mP->mStackName, aStackIndex);
   Prn::print(Prn::View01, "WriteOutput %s", tFilePath);

   // Write output file.
   cv::imwrite(tFilePath, mOutputImage);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace