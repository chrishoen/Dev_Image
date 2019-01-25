#pragma once

/*==============================================================================
Some namespace: sixdofs that are measured by a computer vision based system.
Image painter. 
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <opencv2/core/core.hpp>

#include "someImageParms.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a set of funtions that paint a target window image.

class ImagePainter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   // Image reference types.
   static const int cCheckerBoard  = 1;
   static const int cAllZeroes     = 2;
   static const int cAllOnes       = 3;
   static const int cReticle       = 4;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Parameters.
   ImageParms* mP;

   // Color.
   cv::Vec3b mForeColor;
   cv::Vec3b mBackColor;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infrastructure.

   // Constructor.
   ImagePainter();
   ImagePainter(ImageParms* aParms);
   void initialize(ImageParms* aParms);
   void reset();
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Paint the target image with a reference pattern. The input is a code that
   // specifies the pattern. This is used to display checkerboards and gray
   // cards.
   void doPaintImage(
      int      aReferenceCode,    // Input   
      cv::Mat& aImage);          // Output

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.
   // Window painters.

   // Initialize the window image matrix to zeroes.
   void initializeImage(
      cv::Mat& aImage);

   // Draw a checkerboard in the window image matrix target region.
   void drawCheckerBoard(
      cv::Mat& aImage,
      int      aWidthX,
      int      aWidthY);

   // Draw reticle in the window image matrix target region
   void drawReticle(
      cv::Mat& aImage,
      int      aWidthX,
      int      aWidthY);

   // Draw all zeroes in the window image matrix.
   void drawAllZeroes(
      cv::Mat& aImage);

   // Draw all ones in the window image matrix.
   void drawAllOnes(
      cv::Mat& aImage);

   // Draw a border around the window image target region.
   void drawBorder(
      cv::Mat& aImage);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


