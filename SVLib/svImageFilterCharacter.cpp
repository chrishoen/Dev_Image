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


   // Loop through all of the rows and columns of the input image.
   for (SV::RCIndexLoop tIndex(tInputImage.rcSize()); tIndex.test(); tIndex.next())
   {
      // Get the pixel value of the input image at the index.
      uchar tValue = tInputImage.at(tIndex());

      if (tValue == 255)
      {
         tOutputImage.at(tIndex()) = 7;
      }
      else
      {
         tOutputImage.at(tIndex()) = 2;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace