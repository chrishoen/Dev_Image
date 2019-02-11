/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svImageWrapper.h"
#include "svPixelFunctions.h"
#include "svRCLoop.h"
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
   bool                  aHiFlag,              // Control
   cv::Mat&              aInputImage,          // Input
   RCIndexListList&      aIndexListList)       // Output
{
   Prn::print(Prn::View11, "doWriteIndexListList");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Input image.

   // Contours will be found on this image.
   cv::Mat tContourImage;

   // If high image then use the input image.
   if (aHiFlag)
   {
      tContourImage = aInputImage;
   }
   // If low image then use the input image with pixels added around
   // the high contour edges.
   else
   {
      // Clone the input image.
      tContourImage = aInputImage.clone();

      // Image wrapper.
      ImageWrapper tInputWrapper(aInputImage);
      ImageWrapper tContourWrapper(tContourImage);

      // Loop through all of the pixels of the input image.
      SV::RCIndexLoop tImageLoop(tInputWrapper.rcSize());
      while (tImageLoop.loop())
      {
         // If the pixel is low.
         if (tInputWrapper.at(tImageLoop()) == 0)
         {
            // Count the number of neighbors that are occupied.
            int tNeighborSum = 0;
            // Traverse a neighborhood circuit centered at the image pixel.
            SV::RCCircuitLoop tNeighborLoop(tImageLoop(), 1);
            while (tNeighborLoop.loop())
            {
               // If the neighbor pixel is in bounds then test its value.
               uchar tNeighborValue = 0;
               if (tInputWrapper.getValue(tNeighborLoop(),tNeighborValue))
               {
                  // Test for occupied.
                  if (tNeighborValue == 255)
                  {
                     // Count the number of neighbors that are occupied.
                     tNeighborSum++;
                  }
               }
            }
            // If any neighbors are occupied then set the pixel high. 
            if (tNeighborSum != 0)
            {
               tContourWrapper.at(tImageLoop()) = 255;
            }
         }
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Find contours.

   // Contour variables.
   std::vector<std::vector<cv::Point>> tContours;
   int tMode = cv::RetrievalModes::RETR_EXTERNAL;
   int tMethod = cv::ContourApproximationModes::CHAIN_APPROX_NONE;
   cv::Point tOffset(0, 0);

   // Find a list of lists of contour points.
   cv::findContours(
      tContourImage,
      tContours,
      tMode,
      tMethod,
      tOffset);

   // Convert the list of lists of contour points to a list of lists
   // of corresponding row column indices.
   convert(
      tContours,          // Input
      aIndexListList);    // Output

   Prn::print(Prn::View11, "findContours %d %d", tContours.size(), aIndexListList.size());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace