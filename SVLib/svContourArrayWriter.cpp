/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svContourArrayWriter.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ContourArrayWriter::ContourArrayWriter()
{
   reset();
}

ContourArrayWriter::ContourArrayWriter(ContourFilterParms* aParms)
{
   mP = aParms;
   reset();
}

void ContourArrayWriter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a pixel record list to a pixel record array.

void ContourArrayWriter::doInitializeArray(
   cv::Mat&              aInputImage,          // Input
   ContourRecordArray&   aRecordArray)         // Output
{
   Prn::print(0, "ContourArrayWriter::doInitializeArray");

   // Initialize the output array to empty.
   aRecordArray.initialize(aInputImage.rows, aInputImage.cols);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a pixel record list to a pixel record array.

void ContourArrayWriter::doWriteArray(
   ContourRecordList&    aRecordList,          // Input
   ContourRecordArray&   aRecordArray)         // Output
{
   Prn::print(0, "ContourArrayWriter::doWriteArray");

   // Copy each record in the input list to the corresponding position
   // in the output array.
   for (int i = 0; i < aRecordList.size(); i++)
   {
      RCIndex tIndex = aRecordList[i].mXX;
      aRecordArray.at(tIndex) = aRecordList[i];
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace