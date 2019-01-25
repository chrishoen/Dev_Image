/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "someImagePainter.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

ImagePainter::ImagePainter()
{
   reset();
}

ImagePainter::ImagePainter(ImageParms* aParms)
{
   mP = aParms;
   reset();
}

void ImagePainter::initialize(ImageParms* aParms)
{
   mP = aParms;
   reset();
}

void ImagePainter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize the window image matrix to zeroes.

void ImagePainter::initializeImage(
   cv::Mat& aImage)
{
   // Set color from parms.
   mForeColor = cv::Vec3b(mP->mForeColor[2], mP->mForeColor[1], mP->mForeColor[0]);
   mBackColor = cv::Vec3b(mP->mBackColor[2], mP->mBackColor[1], mP->mBackColor[0]);

   // Create new image.
   aImage = cv::Mat(mP->mImageHeight, mP->mImageWidth, CV_8UC3, mBackColor);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Paint the target image with a reference pattern. The input is a code that
// specifies the pattern. This is used to display checkerboards and gray
// cards.

void ImagePainter::doPaintImage(
   int      aReferenceCode,   // Input
   cv::Mat& aImage)          // Output
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Paint into window image.

   initializeImage(aImage);

   switch (aReferenceCode)
   {
   case cCheckerBoard:
   {
      // Show checkerboard.
      drawCheckerBoard(aImage, mP->mSideX, mP->mSideY);
      drawBorder(aImage);     
   }
   break;
   case cAllZeroes:
   {
      // Show all ones.
      drawAllZeroes(aImage);
   }
   break;
   case cAllOnes:
   {
      // Show all ones.
      drawAllOnes(aImage);
   }
   break;
   case cReticle:
   {
      // Show reticle.
      drawReticle(aImage, mP->mSideX, mP->mSideY);
      drawBorder(aImage);
   }
   break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw a checkerboard in the window image matrix target region.

void ImagePainter::drawCheckerBoard(
   cv::Mat& aImage,
   int      aWidthX,
   int      aWidthY)
{
   // Draw the points.
   int tX = aWidthX*2;
   int tY = aWidthY*2;

   for (int iY = 0; iY < aImage.rows; iY++)
   {
      for (int jX = 0; jX < aImage.cols; jX++)
      {
         int tN1 = (2 * iY) / tY;
         int tM1 = (2 * jX) / tX;
         int tI = (3 * tN1 + tM1 + 1) % 2;

         if (tI)
         {
            aImage.at<cv::Vec3b>(iY,jX) = mForeColor;
         }
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw a reticle in the window image matrix target region.

void ImagePainter::drawReticle(
   cv::Mat& aImage,
   int      aWidthX,
   int      aWidthY)
{
   // Draw the points.
   int tX = aWidthX * 2;
   int tY = aWidthY * 2;

   // Guard.
   if (!mP->mImageBorder) return;

   for (int iY = 0; iY < aImage.rows; iY++)
   {
      aImage.at<cv::Vec3b>(iY, aWidthY) = mForeColor;
      aImage.at<cv::Vec3b>(iY, aImage.cols - aWidthY) = mForeColor;

      aImage.at<cv::Vec3b>(iY, 288) = mForeColor;
   }

   for (int iX = 0; iX < aImage.cols; iX++)
   {
      aImage.at<cv::Vec3b>(aWidthX, iX) = mForeColor;
      aImage.at<cv::Vec3b>(aImage.rows - aWidthX, iX) = mForeColor;
      
      aImage.at<cv::Vec3b>(240, iX) = mForeColor;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw all zeroes in the target window matrix.

void ImagePainter::drawAllZeroes(
   cv::Mat& aImage)
{
   for (int iY = 0; iY < aImage.rows; iY++)
   {
      for (int jX = 0; jX < aImage.cols; jX++)
      {
         aImage.at<cv::Vec3b>(iY, jX) = mBackColor;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw all ones in the target window matrix.

void ImagePainter::drawAllOnes(
   cv::Mat& aImage)
{
   for (int iY = 0; iY < aImage.rows; iY++)
   {
      for (int jX = 0; jX < aImage.cols; jX++)
      {
         aImage.at<cv::Vec3b>(iY, jX) = cv::Vec3b(mForeColor);
      }
   }
   return;

   aImage.setTo(mForeColor);
   return;

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw a border around the window image target region.

void ImagePainter::drawBorder(
   cv::Mat& aImage)
{
   // Guard.
   if (!mP->mImageBorder) return;

   for (int iY = 0; iY < aImage.rows; iY++)
   {
      aImage.at<cv::Vec3b>(iY,             0) = mForeColor;
      aImage.at<cv::Vec3b>(iY, aImage.cols-1) = mForeColor;
   }

   for (int iX = 0;  iX < aImage.cols; iX++)
   {
      aImage.at<cv::Vec3b>(0,             iX) = mForeColor;
      aImage.at<cv::Vec3b>(aImage.rows-1, iX) = mForeColor;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace