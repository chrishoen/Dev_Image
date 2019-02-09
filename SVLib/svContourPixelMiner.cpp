/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svDefs.h"

#include "svContourPixelMiner.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ContourPixelMiner::ContourPixelMiner()
{
   reset();
}

ContourPixelMiner::ContourPixelMiner(ContourFilterParms* aParms)
{
   mP = aParms;
   reset();
}

void ContourPixelMiner::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the image, depending on the parms.

   // Mine the contour pixels from an input image.
void ContourPixelMiner::doMineImage(
   cv::Mat&                   aInputImage,          // Input
   ContourPixelRecordList&    aRecordList)          // Output
{
   Prn::print(0, "ContourPixelMiner::doMineImage");

   // Set the image wrapper.
   mInputImage.set(aInputImage);

   // Contour variables.
   std::vector<std::vector<cv::Point>> tContours;
   int tMode = cv::RetrievalModes::RETR_EXTERNAL;
   int tMethod = cv::ContourApproximationModes::CHAIN_APPROX_NONE;
   cv::Point tOffset(0, 0);

   // Find a list of lists of contour points.
   cv::findContours(
      aInputImage,
      tContours,
      tMode,
      tMethod,
      tOffset);
   Prn::print(0, "findContours %d", tContours.size());

   // Loop for each contour.
   for (int i = 0; i < tContours.size(); i++)
   {
      // Filter each contour.
      doMineContour(tContours[i],aRecordList);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Mine all of the pixels in a contour.

void ContourPixelMiner::doMineContour(
   std::vector<cv::Point>&   aContour,             // Input
   ContourPixelRecordList&   aRecordList)          // Output
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

      // Transfer the results to the record list.
      ContourPixelRecord tRecord;
      tRecord.mXX = mX0;
      aRecordList.push_back(tRecord);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter an image pixel that is contained in a contour.

void ContourPixelMiner::doFilterContourPixel(int aN)
{
   Prn::print(Prn::View11, "Contour Pixel %4d $ %4d %4d", aN, mX0.mRow, mX0.mCol);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace