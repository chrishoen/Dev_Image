#pragma once

/*==============================================================================
Nearest neighbor rule filter.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <opencv2/core/core.hpp>

#include "svImageWrapper.h"
#include "svNNRuleParms.h"

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

class NNRuleFilter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Parameters. These are read from a parms file.

   NNRuleParms* mP;

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
   NNRuleFilter();
   NNRuleFilter(NNRuleParms* aParms);
   void initialize(NNRuleParms* aParms);
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Filter an image according to the parms.
   void doFilterImage(
      cv::Mat&       aInput,               // Input
      cv::Mat&       aOutput);             // Output
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


