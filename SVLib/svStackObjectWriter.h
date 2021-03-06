#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Simulator synthetic image generator.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>

#include "svStackObjectParms.h"
#include "svTileWriter.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a simulator synthetic image generator.

class StackObjectWriter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Parameters.
   StackObjectParms* mP;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Image filter.
   SV::TileWriter mTileWriter;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   StackObjectWriter();
  ~StackObjectWriter();
   StackObjectWriter(StackObjectParms* aParms);
   void initialize(StackObjectParms* aParms);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Write a stack object slice to an output image, based on a
   // reverse stack index, according to the parms.
   void doWriteStackObject(
      int            aReverseIndex,   // Control
      cv::Mat&       aOutputImage);   // Output
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


