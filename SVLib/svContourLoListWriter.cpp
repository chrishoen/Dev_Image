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
// Write a pixel low record list.

void ContourLoListWriter::doWriteLoList(
   cv::Mat&              aInputImage,          // Input
   ContourRecordList&    aHiList,              // Input
   ContourRecordArray&   aLoList)              // Output
{
   Prn::print(0, "ContourLoListWriter::doMineImage");

   // Set the image wrapper.
   mInputImage.set(aInputImage);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace