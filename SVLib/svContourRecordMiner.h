#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Contour specific image filter.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "svImageWrapper.h"
#include "svContourFilterParms.h"
#include "svContourRecord.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is an image filter that filters pixels in the contours of an image.
//

class ContourRecordMiner
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Parameters. These are read from a parms file.

   ContourFilterParms* mP;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Input image wrapper.
   ImageWrapper mInputImage;

   // Number of pixels in the contour that is being filtered.
   int mNumPixels;

   // Current pixel that is being filtered.
   RCIndex mXM1;       // X0 - 1  previous pixel.
   RCIndex mX0;        // X0      current pixel.
   RCIndex mXP1;       // X0 + 1  next pixel.

   // Filter outputs
   RCIndex mXV;        // Velocity, tangent.
   RCIndex mXA;        // Acceleration, normal.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   ContourRecordMiner();
   ContourRecordMiner(ContourFilterParms* aParms);
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Mine the contour pixels from an input image.
   void doMineImage(
      cv::Mat&                   aInputImage,          // Input
      ContourRecordList&    aRecordList);         // Output

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Mine all of the pixels in a contour.
   void doMineContour(
      std::vector<cv::Point>&   aContour,             // Input
      ContourRecordList&   aRecordList);         // Output

   // Filter an image pixel that is contained in a contour.
   void doFilterContourPixel(int aN);
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


