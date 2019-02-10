/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svContourLoListWriter.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ContourLoListWriter::ContourLoListWriter()
{
   reset();
}

ContourLoListWriter::ContourLoListWriter(ContourFilterParms* aParms)
{
   mP = aParms;
   reset();
}

void ContourLoListWriter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a pixel record list to a pixel record array.

void ContourLoListWriter::doWriteArray(
   cv::Mat&                   aInputImage,          // Input
   ContourRecordList&    aRecordList,          // Input
   ContourRecordArray&   aRecordArray)         // Output
{
   Prn::print(0, "ContourLoListWriter::doMineImage");

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