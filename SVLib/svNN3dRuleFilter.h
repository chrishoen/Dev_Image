#pragma once

/*==============================================================================
Nearest neighbor rule filter.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <opencv2/core/core.hpp>

#include "svImageWrapper.h"
#include "svNN3dRuleParms.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is an image filter that filters pixels according to a set of rules
// that pertain to the nearest neighbors of the pixel.
//

class NN3dRuleFilter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Parameters. These are read from a parms file.

   NN3dRuleParms* mP;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. Variables, according to the main diagram.

   // Images.
   ImageWrapper mInput;
   ImageWrapper mOutput;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   NN3dRuleFilter();
   NN3dRuleFilter(NN3dRuleParms* aParms);
   void initialize(NN3dRuleParms* aParms);
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Filter an image according to the parms.
   void doFilterImage(
      cv::Mat&       aInput,               // Input
      cv::Mat&       aOutput);             // Output

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Filter a pixel.
   void doFilterHighPixel(RCIndex aX);
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

