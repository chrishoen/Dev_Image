/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svRCIndexList.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Convert a contour to an index list.

void convert(
   std::vector<cv::Point2i>              aContour,         // Input
   RCIndexList                           aIndexList)       // Output
{
   // Allocate memory for the output.
   aIndexList.reserve(aContour.size());

   // Loop for each point in the contour.
   for (int i = 0; i < aContour.size(); i++)
   {
      // Convert the point to an index .
      aIndexList[i] = RCIndex(aContour[i].y, aContour[i].x);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Convert a list of contours to a list of index lists.

void convert(
   std::vector<std::vector<cv::Point2i>> aContours,        // Input
   RCIndexListList                       aIndexListList)   // Output
{
   // Allocate memory for the output.
   aIndexListList.reserve(aContours.size());

   // Loop for each contour.
   for (int i = 0; i < aContours.size(); i++)
   {
      // Convert the contour to an index list.
      convert(
         aContours[i],             // Input
         aIndexListList[i]);       // Output
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace