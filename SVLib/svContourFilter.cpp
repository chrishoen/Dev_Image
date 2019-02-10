/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svContourFilter.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ContourFilter::ContourFilter()
{
   reset();
}

ContourFilter::ContourFilter(ContourFilterParms* aParms)
{
   mP = aParms;
   reset();
}

void ContourFilter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the image, depending on the parms.

void ContourFilter::doFilterImage(
   cv::Mat&       aInputImage,     // Input
   cv::Mat&       aOutputImage)    // Output
{
   Prn::print(0, "ContourFilter::doFilterImage");

   // Copy the input to the output.
   aOutputImage = aInputImage.clone();

   // Set the image wrappers.
   mInputImage.set(aInputImage);
   mOutputImage.set(aOutputImage);

   // Contour variables.
   std::vector<std::vector<cv::Point>> tContours;
// std::vector<std::vector<int>> tHierarchy;
   int tMode = cv::RetrievalModes::RETR_EXTERNAL;
   int tMethod = cv::ContourApproximationModes::CHAIN_APPROX_NONE;
   cv::Point tOffset(0, 0);

   // Find a list of lists of contour points.
   cv::findContours(
      aInputImage,
      tContours,
//    tHierarchy,
      tMode,
      tMethod,
      tOffset);
   Prn::print(0, "findContours %d", tContours.size());

   // Loop for each contour.
   for (int i = 0; i < tContours.size(); i++)
   {
      // Filter each contour.
      doFilterContour(tContours[i]);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter all of the pixels in a contour.

void ContourFilter::doFilterContour(
   std::vector<cv::Point>& aContour)
{
   Prn::print(Prn::View11, "**************************************Contour %d", aContour.size());

   // Loop for each pixel in the contour.
   mNumPixels = (int)aContour.size();
   int jM1 = 0;  // Previous pixel array index.
   int jP1 = 0;  // Next pixel array index.
   for (int j = 0; j < aContour.size(); j++)
   {
      // First pixel indices.
      if (j == 0)
      {
         jM1 = mNumPixels - 1;       // Previous pixel array index.
         jP1 = j + 1;                // Next pixel array index. 
      }
      // Last pixel indices.
      else if (j == mNumPixels - 1)
      {
         jM1 = j - 1;                // Previous pixel array index. 
         jP1 = 0;                    // Next pixel array index.
      }
      // Otherwise pixel indices.
      else
      {
         jM1 = j - 1;                // Previous pixel array index.
         jP1 = j + 1;                // Next pixel array index.
      }
      // Extract the previous, current, and next pixels.
      mXM1 = RCIndex(aContour[jM1].y, aContour[jM1].x);   // Previous pixel.
      mX0  = RCIndex(aContour[j].y,   aContour[j].x);     // Current pixel.  
      mXP1 = RCIndex(aContour[jP1].y, aContour[jP1].x);   // Nexy pixel.
      // Filter the current pixel.
      doFilterContourPixel(j);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter an image pixel that is contained in a contour.

void ContourFilter::doFilterContourPixel(int aN)
{
   Prn::print(Prn::View11, "Contour Pixel %4d $ %4d %4d", aN, mX0.mRow, mX0.mCol);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace