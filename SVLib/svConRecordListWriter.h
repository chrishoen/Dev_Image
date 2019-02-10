#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Contour specific image filter.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "svImageWrapper.h"
#include "svConParms.h"
#include "svConRecord.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a parameterized function that writes to a high pixel record list.
//

class ConRecordListWriter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Parameters. These are read from a parms file.

   ConParms* mP;

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
   ConRecordListWriter();
   ConRecordListWriter(ConParms* aParms);
   void initialize(ConParms* aParms);
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Write to a high pixel record list.
   void doWriteHiList(
      cv::Mat&                  aInputImage,          // Input
      ConRecordList&            aRecordList);         // Output

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Write to a high pixel record list.
   void doWriteHiList(
      std::vector<cv::Point>&   aContour,             // Input
      ConRecordList&            aRecordList);         // Output

   // Filter an image pixel that is contained in a contour.
   void doFilterContourPixel(int aN);
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


