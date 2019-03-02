/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svRCIndex.h"
#include "svRCLoop.h"
#include "svMorphFilter.h"

#include "svImageFunctions.h"
#include "svImageShow.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

MorphFilter::MorphFilter()
{
   reset();
}

MorphFilter::MorphFilter(MorphParms* aParms)
{
   mP = aParms;
   reset();
}

void MorphFilter::initialize(MorphParms* aParms)
{
   mP = aParms;
   reset();
}

void MorphFilter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get nearest neighbors.

inline void MorphFilter::doGetNearestNeighbors(RCIndex aX)
{
   m11 = mInput.at(aX.mRow - 1, aX.mCol - 1) != 0 ? 1 : 0;
   m12 = mInput.at(aX.mRow - 1, aX.mCol    ) != 0 ? 1 : 0;
   m13 = mInput.at(aX.mRow - 1, aX.mCol + 1) != 0 ? 1 : 0;

   m21 = mInput.at(aX.mRow,     aX.mCol - 1) != 0 ? 1 : 0;
   m23 = mInput.at(aX.mRow,     aX.mCol + 1) != 0 ? 1 : 0;

   m31 = mInput.at(aX.mRow + 1, aX.mCol - 1) != 0 ? 1 : 0;
   m32 = mInput.at(aX.mRow + 1, aX.mCol    ) != 0 ? 1 : 0;
   m33 = mInput.at(aX.mRow + 1, aX.mCol + 1) != 0 ? 1 : 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate a first image.

void MorphFilter::doGenerateFirstImage(
   cv::Mat&       aOutput)              // Output
{
   // Create an image filled with all zeros.
   aOutput = cv::Mat(mP->mImageSize.mRows, mP->mImageSize.mCols, CV_8UC1, cv::Scalar(0));

   // Set the image wrappers.
   mOutput.set(aOutput);

   // Set the center pixel.
   mOutput.at(RCIndex(mP->mImageSize.mRows/2, mP->mImageSize.mCols/2)) = 255;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the image, depending on the parms.

void MorphFilter::doFilterImage(
   cv::Mat&       aInputImage,     // Input
   cv::Mat&       aOutputImage)    // Output
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   Prn::print(Prn::View11, "doFilterImage %4d %4d", aInputImage.rows, aInputImage.cols);

   // Clone the input image to the output image.
   aOutputImage = aInputImage.clone();

   // Set the image wrappers.
   mInput.set(aInputImage);
   mOutput.set(aOutputImage);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop through the image for mode a square with addition.

   // Loop through the image. Ignore the top and bottom rows and ignore
   // the left and right edge columns.
   if (mP->isSquare() && mP->mAddFlag)
   {
      SV::RCIndexLoop tLoop(RCIndex(1, 1), aInputImage.rows - 2, aInputImage.cols - 2);
      while (tLoop.loop())
      {
         // Filter each pixel that is high.
         if (mInput.at(tLoop()) != 0)
         {
            doFilterHighPixel_SquareAdd(tLoop());
         }
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop through the image for mode a square with subtraction.

   // Loop through the image. Ignore the top and bottom rows and ignore
   // the left and right edge columns.
   if (mP->isSquare() && !mP->mAddFlag)
   {
      SV::RCIndexLoop tLoop(RCIndex(1, 1), aInputImage.rows - 2, aInputImage.cols - 2);
      while (tLoop.loop())
      {
         // Filter each pixel that is high.
         if (mInput.at(tLoop()) != 0)
         {
            doFilterHighPixel_SquareSub(tLoop());
         }
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop through the image for a diamond with addition.

   // Loop through the image. Ignore the top and bottom rows and ignore
   // the left and right edge columns.
   if (mP->isDiamond() && mP->mAddFlag)
   {
      SV::RCIndexLoop tLoop(RCIndex(1, 1), aInputImage.rows - 2, aInputImage.cols - 2);
      while (tLoop.loop())
      {
         // Filter each pixel that is high.
         if (mInput.at(tLoop()) != 0)
         {
            doFilterHighPixel_DiamondAdd(tLoop());
         }
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop through the image for a diamond with subtraction.

   // Loop through the image. Ignore the top and bottom rows and ignore
   // the left and right edge columns.
   if (mP->isDiamond() && !mP->mAddFlag)
   {
      SV::RCIndexLoop tLoop(RCIndex(1, 1), aInputImage.rows - 2, aInputImage.cols - 2);
      while (tLoop.loop())
      {
         // Filter each pixel that is high.
         if (mInput.at(tLoop()) != 0)
         {
            doFilterHighPixel_DiamondSub(tLoop());
         }
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter a pixel that is high.

void MorphFilter::doFilterHighPixel_SquareAdd(RCIndex aX)
{
   // Locals.
   RCIndex tCursor;

   // Get nearest neighbor variables.
   doGetNearestNeighbors(aX);

   // Nearest neighbor rule testing.
   if (!m21)
   {
      tCursor = aX;
      tCursor.mCol--;
      for (int i = 0; i < mP->mDelta.mCols; i++)
      {
         mOutput.at(tCursor) = 255;
         tCursor.mCol--;
      }
   }

   // Nearest neighbor rule testing.
   if (!m23)
   {
      tCursor = aX;
      tCursor.mCol++;
      for (int i = 0; i < mP->mDelta.mCols; i++)
      {
         mOutput.at(tCursor) = 255;
         tCursor.mCol++;
      }
   }

   // Nearest neighbor rule testing.
   if (!m12)
   {
      tCursor = aX;
      tCursor.mRow--;
      for (int i = 0; i < mP->mDelta.mRows; i++)
      {
         mOutput.at(tCursor) = 255;
         tCursor.mRow--;
      }
   }

   // Nearest neighbor rule testing.
   if (!m32)
   {
      tCursor = aX;
      tCursor.mRow++;
      for (int i = 0; i < mP->mDelta.mRows; i++)
      {
         mOutput.at(tCursor) = 255;
         tCursor.mRow++;
      }
   }

   // Nearest neighbor rule testing.
   if (!m11)
   {
      tCursor = aX;
      tCursor.mRow--;
      tCursor.mCol--;
      for (int i = 0; i < mP->mDelta.mRows; i++)
      {
         for (int j = 0; j < mP->mDelta.mCols; j++)
         {
            mOutput.at(tCursor) = 255;
            tCursor.mCol--;
         }
         tCursor.mRow--;
      }
   }

   // Nearest neighbor rule testing.
   if (!m13)
   {
      tCursor = aX;
      tCursor.mRow--;
      tCursor.mCol++;
      for (int i = 0; i < mP->mDelta.mRows; i++)
      {
         for (int j = 0; j < mP->mDelta.mCols; j++)
         {
            mOutput.at(tCursor) = 255;
            tCursor.mCol++;
         }
         tCursor.mRow--;
      }
   }

   // Nearest neighbor rule testing.
   if (!m31)
   {
      tCursor = aX;
      tCursor.mRow++;
      tCursor.mCol--;
      for (int i = 0; i < mP->mDelta.mRows; i++)
      {
         for (int j = 0; j < mP->mDelta.mCols; j++)
         {
            mOutput.at(tCursor) = 255;
            tCursor.mCol--;
         }
         tCursor.mRow++;
      }
   }

   // Nearest neighbor rule testing.
   if (!m33)
   {
      tCursor = aX;
      tCursor.mRow++;
      tCursor.mCol++;
      for (int i = 0; i < mP->mDelta.mRows; i++)
      {
         for (int j = 0; j < mP->mDelta.mCols; j++)
         {
            mOutput.at(tCursor) = 255;
            tCursor.mCol++;
         }
         tCursor.mRow++;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter a pixel that is high.

void MorphFilter::doFilterHighPixel_DiamondAdd(RCIndex aX)
{
   // Locals.
   RCIndex tCursor;

   // Get nearest neighbor variables.
   doGetNearestNeighbors(aX);

   // Nearest neighbor rule testing.
   if (!m21)
   {
      tCursor = aX;
      tCursor.mCol--;
      for (int i = 0; i < mP->mDelta.mCols; i++)
      {
         mOutput.at(tCursor) = 255;
         tCursor.mCol--;
      }
   }

   // Nearest neighbor rule testing.
   if (!m23)
   {
      tCursor = aX;
      tCursor.mCol++;
      for (int i = 0; i < mP->mDelta.mCols; i++)
      {
         mOutput.at(tCursor) = 255;
         tCursor.mCol++;
      }
   }

   // Nearest neighbor rule testing.
   if (!m12)
   {
      tCursor = aX;
      tCursor.mRow--;
      for (int i = 0; i < mP->mDelta.mRows; i++)
      {
         mOutput.at(tCursor) = 255;
         tCursor.mRow--;
      }
   }

   // Nearest neighbor rule testing.
   if (!m32)
   {
      tCursor = aX;
      tCursor.mRow++;
      for (int i = 0; i < mP->mDelta.mRows; i++)
      {
         mOutput.at(tCursor) = 255;
         tCursor.mRow++;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter a pixel that is high.

void MorphFilter::doFilterHighPixel_SquareSub(RCIndex aX)
{
   // Locals.
   RCIndex tCursor;

   // Get nearest neighbor variables.
   doGetNearestNeighbors(aX);

   // Nearest neighbor rule testing.
   if (!m21)
   {
      tCursor = aX;
      for (int i = 0; i < mP->mDelta.mCols; i++)
      {
         mOutput.at(tCursor) = 0;
         tCursor.mCol++;
      }
   }

   // Nearest neighbor rule testing.
   if (!m23)
   {
      tCursor = aX;
      for (int i = 0; i < mP->mDelta.mCols; i++)
      {
         mOutput.at(tCursor) = 0;
         tCursor.mCol--;
      }
   }

   // Nearest neighbor rule testing.
   if (!m12)
   {
      tCursor = aX;
      for (int i = 0; i < mP->mDelta.mRows; i++)
      {
         mOutput.at(tCursor) = 0;
         tCursor.mRow++;
      }
   }

   // Nearest neighbor rule testing.
   if (!m32)
   {
      tCursor = aX;
      for (int i = 0; i < mP->mDelta.mRows; i++)
      {
         mOutput.at(tCursor) = 0;
         tCursor.mRow--;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter a pixel that is high.

void MorphFilter::doFilterHighPixel_DiamondSub(RCIndex aX)
{
   // Locals.
   RCIndex tCursor;

   // Get nearest neighbor variables.
   doGetNearestNeighbors(aX);

   // Nearest neighbor rule testing.
   if (!m21)
   {
      tCursor = aX;
      for (int i = 0; i < mP->mDelta.mCols; i++)
      {
         mOutput.at(tCursor) = 0;
         tCursor.mCol++;
      }
   }

   // Nearest neighbor rule testing.
   if (!m23)
   {
      tCursor = aX;
      for (int i = 0; i < mP->mDelta.mCols; i++)
      {
         mOutput.at(tCursor) = 0;
         tCursor.mCol--;
      }
   }

   // Nearest neighbor rule testing.
   if (!m12)
   {
      tCursor = aX;
      for (int i = 0; i < mP->mDelta.mRows; i++)
      {
         mOutput.at(tCursor) = 0;
         tCursor.mRow++;
      }
   }

   // Nearest neighbor rule testing.
   if (!m32)
   {
      tCursor = aX;
      for (int i = 0; i < mP->mDelta.mRows; i++)
      {
         mOutput.at(tCursor) = 0;
         tCursor.mRow--;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

