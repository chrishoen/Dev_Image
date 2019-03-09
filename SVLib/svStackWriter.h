#pragma once

/*==============================================================================
Synthetic image stack writer.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <opencv2/core/core.hpp>

#include "svStackParms.h"
#include "svStackObjectWriter.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a synthetic image stack writer.

class StackWriter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Parameters.
   StackParms* mP;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Reverse stack index, goes from top to bottom.
   int mReverseIndex;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Images.
   cv::Mat mOutputImage;

   // Image filter.
   SV::StackObjectWriter mObjectWriter;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   StackWriter();
  ~StackWriter();
   StackWriter(StackParms* aParms);
   void initialize(StackParms* aParms);
   void finalize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Write an image stack, according to the parms.
   void doWriteStack();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Write the output image to a file based on the stack index.
   void doWriteOutputImage(int aStackIndex);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


