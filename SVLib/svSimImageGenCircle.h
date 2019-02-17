#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Circle class for object point grid generators.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "svSimImageGenBase.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is an object point grid generator, which is used to generate
// geometrical grids of object points that are displayed as target display
// pixels. It generates a grids for the Circle algorithm.
//
// It inherits from the grid generator base class, which provides a common 
// interface and a parameters member variable.

class SimImageGenCircle : public SimImageGenBase
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   typedef SimImageGenBase BaseClass;
   SimImageGenCircle();
   SimImageGenCircle(SimImageGenParms* aParms);
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Generate an image according to the parms.
   void doGenerateImage(
      cv::Mat&       aImage) override;          // Output
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


