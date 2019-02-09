/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risAlphaDir.h"
#include "svSysParms.h"
#include "svImageParms.h"
#include "svImageWrapper.h"

#include "svPixelFunctions.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Convert image to target format.

void convertImageToTarget(
   cv::Mat&      aInput,    // Input
   cv::Mat&      aOutput)   // Output
{
   cv::cvtColor(aInput, aOutput, CV_GRAY2RGB);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write image to file.

void writeImageToFile(
   cv::Mat&      aImage,      // Input
   const char*   aFileName)   // Input
{
   // Guard.
   if (aImage.rows == 0)return;

   // Write the image to a file.
   char tBuffer[100];
   cv::imwrite(Ris::getAlphaFilePath_Image(tBuffer, aFileName), aImage);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read image fro, file.

void readImageFromFile(
   cv::Mat&      aImage,      // Input
   const char*   aFileName)   // Input
{

   // Write the image to a file.
   char tBuffer[100];
   aImage =  cv::imread(Ris::getAlphaFilePath_Image(tBuffer, aFileName), CV_LOAD_IMAGE_GRAYSCALE);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Extract an image region of interest.

void extractImageRoi(
   cv::Mat&      aInput,    // Input
   cv::Mat&      aOutput)   // Output
{
   // Guard.
   if (aInput.rows == 0)return;

   // Roi variables.
   int tUpperLeftRowY = gImageParms.mRoiPixel.mRow - gImageParms.mRoiB;
   int tUpperLeftColX = gImageParms.mRoiPixel.mCol - gImageParms.mRoiB;
   int tWidth = 2 * gImageParms.mRoiB + 1;
   int tHeight = tWidth;
   cv::Rect tRoiRect(tUpperLeftColX, tUpperLeftRowY, tWidth, tHeight);

   // Extract roi.
   aOutput = aInput(tRoiRect);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
