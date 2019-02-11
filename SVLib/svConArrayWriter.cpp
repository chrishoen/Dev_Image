/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svConArrayWriter.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ConArrayWriter::ConArrayWriter()
{
   reset();
}

ConArrayWriter::ConArrayWriter(ConParms* aParms)
{
   mP = aParms;
   reset();
}

void ConArrayWriter::initialize(ConParms* aParms)
{
   mP = aParms;
   reset();
}

void ConArrayWriter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a pixel record list to a pixel record array.

void ConArrayWriter::doInitializeArray(
   cv::Mat&          aInputImage,          // Input
   ConRecordArray&   aRecordArray)         // Output
{
   Prn::print(Prn::View11, "ConArrayWriter::doInitializeArray");

   // Initialize the output array to empty.
   aRecordArray.initialize(aInputImage.rows, aInputImage.cols);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a pixel record list to a pixel record array.

void ConArrayWriter::doWriteArray(
   ConRecordList&    aRecordList,          // Input
   ConRecordArray&   aRecordArray)         // Output
{
   Prn::print(Prn::View11, "ConArrayWriter::doWriteArray");

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