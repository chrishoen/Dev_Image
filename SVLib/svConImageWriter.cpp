/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svConImageWriter.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ConImageWriter::ConImageWriter()
{
   reset();
}

ConImageWriter::ConImageWriter(ConParms* aParms)
{
   mP = aParms;
   reset();
}

void ConImageWriter::initialize(ConParms* aParms)
{
   mP = aParms;
   reset();
}

void ConImageWriter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize an output image.

void ConImageWriter::doInitializeImage(
   cv::Mat&          aInputImage,          // Input
   cv::Mat&          aOutputImage)         // Output
{
   // Copy the input to the output.
   aOutputImage = aInputImage.clone();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a pixel record list to an output image.

void ConImageWriter::doWriteImage(
   ConRecordList&    aRecordList,          // Input
   cv::Mat&          aOutputImage)         // Input
{
   // Guard.
   if (aRecordList.size() == 0) return;

   // Image wrapper.
   mOutputWrapper.set(aOutputImage);


   // Loop through all of the records in the record list.
   for (auto &tRecord : aRecordList)
   {
      int tXVRow = abs(tRecord.mXV.mRow);
      int tXVCol = abs(tRecord.mXV.mCol);
      int tOutputValue = mP->mMapXVTable[tXVRow][tXVCol];
      if (tOutputValue != 0)
      {
         mOutputWrapper.at(tRecord.mXX) = tOutputValue;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace