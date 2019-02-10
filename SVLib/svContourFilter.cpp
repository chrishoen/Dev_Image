/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svContourFilter.h"

#include "svImageFunctions.h"
#include "svImageShow.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ContourFilter::ContourFilter()
{
   reset();
}

ContourFilter::ContourFilter(ConParms* aParms)
{
   mP = aParms;
   reset();
}

void ContourFilter::initialize(ConParms* aParms)
{
   mP = aParms;
   mIndexListListWriter.initialize(aParms);
   mLoIndexListWriter.initialize(aParms);
   mRecordListWriter.initialize(aParms);
   mArrayWriter.initialize(aParms);
   mImageWriter.initialize(aParms);
   reset();
}

void ContourFilter::reset()
{
   mIndexListListWriter.reset();
   mLoIndexListWriter.reset();
   mRecordListWriter.reset();
   mArrayWriter.reset();
   mImageWriter.reset();

   mInputImage.deallocate();
   mOutputImage.deallocate();

   mIndexListList.clear();
   mHiIndexList.clear();
   mLoIndexList.clear();
   mHiRecordList.clear();
   mLoRecordList.clear();
   mRecordArray.finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the image, depending on the parms.

void ContourFilter::doFilterImage(
   int            aCode,           // Control
   cv::Mat&       aInputImage,     // Input
   cv::Mat&       aOutputImage)    // Output
{
   // Copy the input image.
   mInputImage = aInputImage;

   // Initialize the output image.
   mImageWriter.doInitializeImage(
      mInputImage,
      mOutputImage);

   // Initialize the output array. 
   mArrayWriter.doInitializeArray(
      mOutputImage,
      mRecordArray);

   // Read from an image, extract a list of all contours, and convert the 
   // contours to a list of row column index lists.
   mIndexListListWriter.doWriteIndexListList(
      aCode == 1,             // Control
      mInputImage,            // Input
      mIndexListList);        // Output

   // Extract the first index list.
   mHiIndexList = mIndexListList[0];

   // Write to a pixel record list.
   mRecordListWriter.doWriteRecordList(
      mHiIndexList,           // Input
      mHiRecordList);         // Output

   // Copy the record list to the record array.
   mArrayWriter.doWriteArray(
      mHiRecordList,          // Input
      mRecordArray);          // Output
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// This runs a test.

void ContourFilter::doShow(int aCode)
{
   switch (aCode)
   {
   case 1:  SV::showImageTableByte("InputImage", mInputImage); break;
   case 20: SV::showRecordArray(0, "InputImage", mRecordArray); break;
   case 21: SV::showRecordArray(1, "InputImage", mRecordArray); break;
   case 3:  SV::showImageTableByte("OutputImage", mOutputImage); break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace