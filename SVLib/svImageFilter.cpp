/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svImageFilterGaussBlur.h"
#include "svImageFilterClassify.h"

#include "svImageFilter.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Infastruccture.

ImageFilter::ImageFilter()
{
   mImageFilter = 0;
}

ImageFilter::~ImageFilter()
{
   finalize();
}

ImageFilter::ImageFilter(ImageFilterParms* aParms)
{
   mImageFilter = 0;
   initialize(aParms);
}

void ImageFilter::finalize()
{
   if (mImageFilter)
   {
      delete mImageFilter;
      mImageFilter = 0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ImageFilter::initialize(ImageFilterParms* aParms)
{
   // Deallocate memory, if already allocated.
   finalize();

   // Store parms.
   mP = aParms;

   // Create specific image generator.
   mImageFilter = 0;
   switch (mP->mFilterType)
   {
   case ImageFilterParms::cFilterGaussBlur:   mImageFilter = new ImageFilterGaussBlur(mP); return;
   case ImageFilterParms::cFilterClassify:    mImageFilter = new ImageFilterClassify(mP); return;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the image, depending on the parms.

void ImageFilter::doFilterImage(
   cv::Mat&       aInput,      // Input
   cv::Mat&       aOutput)     // Output
{
   // Guard.
   if (mImageFilter == 0)
   {
      Prn::print(0, "ImageFilter::doFilterImage ERROR 101");
      return;
   }

   // Filter an image using the specific image filter.
   mImageFilter->doFilterImage(
      aInput,                  // Input
      aOutput);                // Output
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace