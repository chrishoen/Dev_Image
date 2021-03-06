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

class ImageSet
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   cv::Mat mInputS1;
   cv::Mat mInputS2;
   cv::Mat mInputS3;
   cv::Mat mOutput;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Constructor.
   ImageSet();
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Input images.
   void doSimInputTile2d();
   void doSimInput2d();
   void doSimInput3d();

   void doReadInput();
   void doReadOutput();

   // Outut images.
   void doWriteInput();
   void doWriteOutput();

   // Show.
   void doShow2d(int aCode);
   void doShow3d(int aCode);

   // Draw.
   void doDraw(int aCode);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
