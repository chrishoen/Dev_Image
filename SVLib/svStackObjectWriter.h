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

#include "svSimParms.h"
#include "svMorphFilter.h"

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
   SimParms* mP;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Generated stack size.
   int mStackSize;

   // Number of images that were generated.
   int mWriteCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Images.
   cv::Mat mInputImage;
   cv::Mat mOutputImage;

   // Image filter.
   SV::MorphFilter mMorphFilter;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   StackObjectWriter();
  ~StackObjectWriter();
   StackObjectWriter(SimParms* aParms);
   void initialize(SimParms* aParms);
   void finalize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Generate an image stack, according to the parms.
   void doWriteStackObject();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Calculate the stack size from the parms.
   void doCalculateStackSize();

   // Apply a morph filter to generate output images.
   void doApplyMorphFilter(MorphParms* aParms);

   // Write the output image to a file.
   void doWriteOutputImage();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

