/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svDefs.h"
#include "svPixelFunctions.h"
#include "svImageWrapper.h"

#include "svImageFilterCharacter.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ImageFilterCharacter::ImageFilterCharacter()
{
   reset();
}

ImageFilterCharacter::ImageFilterCharacter(ImageFilterParms* aParms)
{
   BaseClass::mP = aParms;
   reset();
}

void ImageFilterCharacter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the image, depending on the parms.

void ImageFilterCharacter::doFilterImage(
   cv::Mat&       aInputImage,     // Input
   cv::Mat&       aOutputImage)    // Output
{
   Prn::print(0, "ImageFilterCharacter::doFilterImage");

   // Create an output image filled with all zeros.
   aOutputImage = cv::Mat::zeros(aInputImage.size(), CV_8UC1);

   // Image wrappers.
   ImageWrapper tInputImage(aInputImage);
   ImageWrapper tOutputImage(aOutputImage);

   // Loop through all of the pixels of the input image.
   for (SV::RCIndexLoop tImageLoop(tInputImage.rcSize()); tImageLoop.test(); tImageLoop.next())
   {
      // Count the number of neighbors that are occupied.
      int tNeighborSum = 0;
      uchar tPixelCode = 0;
      uchar tInputValue = tInputImage.at(tImageLoop());
      // Dither a neighborhood around each image pixel.
      SV::RCDitherLoop1 tNeighborDither(1, 1);
      do
      {
         // Test for not the center of the neighborhood
         if (tNeighborDither() != RCIndex(0, 0))
         {
            // Get the neighbor pixel.
            RCIndex tNeighborPixel = tImageLoop() + tNeighborDither();

            // Test if in bounds.
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
      } while (tNeighborDither.advance());

      // Set the output pixel value. 
      uchar tOutputValue = 0;
      if (mP->mCharacterCode == 0)
      {
         // Set the output pixel value to the sum. 
         tOutputValue = tNeighborSum;
      }
      if (mP->mCharacterCode == 1)
      {
         if (tInputValue == 255 && tNeighborSum != 8)
         {
            // Set the output pixel value to the sum. 
            tOutputValue = 1;
         }
         if (tInputValue == 0 && tNeighborSum != 0)
         {
            // Set the output pixel value to the sum. 
            tOutputValue = 2;
         }
      }
      // Set the output pixel value. 
      tOutputImage.at(tImageLoop()) = tOutputValue;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace