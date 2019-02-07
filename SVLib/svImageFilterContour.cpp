/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svDefs.h"

#include "svImageFilterContour.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ImageFilterContour::ImageFilterContour()
{
   reset();
}

ImageFilterContour::ImageFilterContour(ImageFilterParms* aParms)
{
   BaseClass::mP = aParms;
   reset();
}

void ImageFilterContour::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the image, depending on the parms.

void ImageFilterContour::doFilterImage(
   cv::Mat&       aInputImage,     // Input
   cv::Mat&       aOutputImage)    // Output
{
   Prn::print(0, "ImageFilterContour::doFilterImage");
   // Copy the input to the output.
   aOutputImage = aInputImage.clone();

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

   // Process.
   Prn::print(0, "findContours %d",tContours.size());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace