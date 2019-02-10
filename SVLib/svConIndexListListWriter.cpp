/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svConIndexListListWriter.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ConIndexListListWriter::ConIndexListListWriter()
{
   reset();
}

ConIndexListListWriter::ConIndexListListWriter(ConParms* aParms)
{
   mP = aParms;
   reset();
}

void ConIndexListListWriter::initialize(ConParms* aParms)
{
   mP = aParms;
   reset();
}

void ConIndexListListWriter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read from an image, extract a list of all contours, and convert the 
// contours to a list of row column index lists.

void ConIndexListListWriter::doWriteIndexListList(
   cv::Mat&              aInputImage,          // Input
   RCIndexListList&      aIndexListList)       // Output
{
   Prn::print(0, "doWriteIndexListList");

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

   // Convert the list of lists of contour points to a list of lists
   // of corresponding row column indices.
   convert(
      tContours,          // Input
      aIndexListList);    // Output

   Prn::print(0, "findContours %d %d", tContours.size(), aIndexListList.size());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace