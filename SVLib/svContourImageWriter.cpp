/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svContourImageWriter.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ContourImageWriter::ContourImageWriter()
{
   reset();
}

ContourImageWriter::ContourImageWriter(ContourFilterParms* aParms)
{
   mP = aParms;
   reset();
}

void ContourImageWriter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize an output image.

void ContourImageWriter::doInitializeImage(
   cv::Mat&              aInputImage,          // Input
   cv::Mat&              aOutputImage)         // Output
{
   // Copy the input to the output.
   aOutputImage = aInputImage.clone();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a pixel record list to an output image.

void ContourImageWriter::doWriteImage(
   ContourRecordList&    aRecordList,          // Input
   cv::Mat&              aOutputImage)         // Input
{

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace