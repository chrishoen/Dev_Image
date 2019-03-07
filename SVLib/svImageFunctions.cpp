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

#include "svImageFunctions.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create a zero output image based on the system parms.

void createZeroImage(
   cv::Mat&      aOutput)   // Output
{
   // Create an image filled with all zeros.
   aOutput = cv::Mat(gSysParms.mImageSize.mRows, gSysParms.mImageSize.mCols, CV_8UC1, cv::Scalar(0));

}

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
   int tUpperLeftRowY = gImageParms.mRoiCenter.mRow - gImageParms.mRoiB;
   int tUpperLeftColX = gImageParms.mRoiCenter.mCol - gImageParms.mRoiB;
   int tWidth = 2 * gImageParms.mRoiB + 1;
   int tHeight = tWidth;
   cv::Rect tRoiRect(tUpperLeftColX, tUpperLeftRowY, tWidth, tHeight);

   // Extract roi.
   aOutput = aInput(tRoiRect);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create an all zeros or all ones output image based on the size of an
// input image.

void fillImage(
   bool          aOnes,     // Control.
   cv::Mat&      aInput,    // Input
   cv::Mat&      aOutput)   // Output
{
   if (aOnes)
   {
      aOutput = cv::Mat::ones(aInput.rows, aInput.cols, CV_8UC1);
   }
   else
   {
      aOutput = cv::Mat::zeros(aInput.rows, aInput.cols, CV_8UC1);
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
