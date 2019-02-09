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
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a pixel record list to a pixel record array.

void ContourArrayWriter::doWriteArray(
   cv::Mat&                   aInputImage,          // Input
   ContourPixelRecordList&    aRecordList,          // Input
   ContourPixelRecordArray&   aRecordArray)         // Output
{
   Prn::print(0, "ContourArrayWriter::doMineImage");

   // Initialize the output array.
   aRecordArray.initialize(aInputImage.rows, aInputImage.cols);

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