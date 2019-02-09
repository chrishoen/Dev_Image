#pragma once

/*==============================================================================
Contour pixel record array writer.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

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

   // Initialize a pixel record array.
   void doInitializeArray(
      cv::Mat&              aInputImage,          // Input
      ContourRecordArray&   aRecordArray);        // Output

   // Write a pixel record list to a pixel record array.
   void doWriteArray(
      ContourRecordList&    aRecordList,          // Input
      ContourRecordArray&   aRecordArray);        // Output
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


