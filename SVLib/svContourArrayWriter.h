#pragma once

/*==============================================================================
Contour pixel record array writer.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "svContourFilterParms.h"
#include "svContourPixelRecord.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a parameterized function that writes to a pixel record array.
//

class ContourArrayWriter
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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   ContourArrayWriter();
   ContourArrayWriter(ContourFilterParms* aParms);
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Write a pixel record list to a pixel record array.
   void doWriteArray(
      cv::Mat&                   aInputImage,          // Input
      ContourPixelRecordList&    aRecordList,          // Input
      ContourPixelRecordArray&   aRecordArray);        // Output
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


