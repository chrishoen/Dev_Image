/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svRCIndex.h"
#include "svRCLoop.h"
#include "svPixelFunctions.h"
#include "svImageWrapper.h"

#include "svImageFilterClassify.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ImageFilterClassify::ImageFilterClassify()
{
   reset();
}

ImageFilterClassify::ImageFilterClassify(ImageFilterParms* aParms)
{
   BaseClass::mP = aParms;
   reset();
}

void ImageFilterClassify::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the image, depending on the parms.

void ImageFilterClassify::doFilterImage(
   cv::Mat&       aInputImage,     // Input
   cv::Mat&       aOutputImage)    // Output
{
   Prn::print(0, "ImageFilterClassify::doFilterImage");

   // Create an output image filled with all zeros.
   aOutputImage = cv::Mat::zeros(aInputImage.size(), CV_8UC1);

   // Image wrappers.
   ImageWrapper tInputImage(aInputImage);
   ImageWrapper tOutputImage(aOutputImage);

   // Loop through all of the pixels of the input image.
   SV::RCIndexLoop tImageLoop(tInputImage.rcSize());
   while(tImageLoop.loop())
   {
      // Count the number of neighbors that are occupied.
      int tNeighborSum = 0;
      uchar tPixelCode = 0;
      uchar tInputValue = tInputImage.at(tImageLoop());
      // Traverse a neighborhood circuit centered at the image pixel.
      SV::RCCircuitLoop tNeighborLoop(tImageLoop(), 1);
      while(tNeighborLoop.loop())
      {
         // Get the neighbor pixel.
         RCIndex tNeighborPixel = tNeighborLoop();

         // Test if it is in bounds.
         if (isImagePixelInBounds(tNeighborPixel))
         {
            // Get the neighbor pixel value.
            uchar tNeighborValue = tInputImage.at(tNeighborPixel);

            // Test for occupied.
            if (tNeighborValue == 255)
            {
               // Count the number of neighbors that are occupied.
               tNeighborSum++;
            }
         }
      }

      // Set the output pixel value. 
      tOutputImage.at(tImageLoop()) = getOutputValue(tInputValue,tNeighborSum);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the output value.

uchar ImageFilterClassify::getOutputValue(
   uchar  aInputValue,       // Input
   int    aNeighborSum)      // Input
{
   uchar tOutputValue = 0;

   // Set the output pixel value to the sum. 
   if (mP->mClassifyCode == 0)
   {
      if (aInputValue == 0)
      {
         tOutputValue = aNeighborSum;
      }
      else
      {
         tOutputValue = 100 + aNeighborSum;
      }
   }

   // Set the output pixel value to the table value. 
   if (mP->mClassifyCode == 1)
   {
      if (aInputValue == 0)
      {
         tOutputValue = mP->mClassifyTable1[0][aNeighborSum];
      }
      else
      {
         tOutputValue = mP->mClassifyTable1[1][aNeighborSum];
      }
   }

   // Set the output pixel value to the table value. 
   if (mP->mClassifyCode == 2)
   {
      if (aInputValue == 0)
      {
         tOutputValue = mP->mClassifyTable2[0][aNeighborSum];
      }
      else
      {
         tOutputValue = mP->mClassifyTable2[1][aNeighborSum];
      }
   }

   return tOutputValue;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace