#pragma once

/*==============================================================================
Simulation calculations test one
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <opencv2/core/core.hpp>

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This provides a framework for running simulation tests.
//

class Simulate
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   cv::Mat mInputImage;
   cv::Mat mOutputImage;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Constructor.
   Simulate();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // These run sequences of operations.
   void doRun1();
   void doRun2();
   void doRun3();

   // Show.
   void doShow(int aCode);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
