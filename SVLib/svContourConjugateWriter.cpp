/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svContourConjugateWriter.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ContourConjugateWriter::ContourConjugateWriter()
{
   reset();
}

ContourConjugateWriter::ContourConjugateWriter(ContourFilterParms* aParms)
{
   mP = aParms;
   reset();
}

void ContourConjugateWriter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a pixel record list to a pixel record array.

void ContourConjugateWriter::doWriteArray(
   cv::Mat&                   aInputImage,          // Input
   ContourRecordList&    aRecordList,          // Input
   ContourRecordArray&   aRecordArray)         // Output
{
   Prn::print(0, "ContourConjugateWriter::doMineImage");

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