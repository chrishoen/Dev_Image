/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risAlphaDir.h"
#include "svRCLoop.h"
#include "svImageParms.h"
#include "svImageWrapper.h"

#include "svImageShow.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show image info.

void showImageInfo(
   const char*   aLabel,   // Input
   cv::Mat&      aImage)   // Input
{
   Prn::print(0, "%-12s %4d %4d $ %3d %3d ", aLabel, aImage.rows, aImage.cols, aImage.depth(), aImage.channels());
   Prn::print(0, "");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show image info.

void showImageTableFloat(
   const char*   aLabel,   // Input
   cv::Mat&      aImage)   // Input
{
   // Guard.
   if (aImage.rows == 0)return;

   // Region of interest variables.
   RCIndex tCenterPixel = gImageParms.mRoiPixel;
   int tB = gImageParms.mRoiB;

   printf("\n");
   printf("********************************************* %-12s %4d %4d $ %1d %1d $ %4d %4d\n",
      aLabel, aImage.rows, aImage.cols, aImage.depth(), aImage.channels(),
      tCenterPixel.mRow, tCenterPixel.mRow);
   printf("\n");

   // Image wrapper.
   ImageWrapper tImage(aImage);
   
   // Print header.
   printf("     $ ");
   for (int iColX = -tB; iColX <= tB; iColX++)
   {
      printf(" %8d", tCenterPixel.mCol + iColX);
   }
   printf("\n");
   printf("     $\n");

   // Loop through all of the rows and columns of the pulse.
   for (int iRowY = -tB; iRowY <= tB; iRowY++)
   {
      printf("%4d $ ", tCenterPixel.mRow + iRowY);
      for (int iColX = -tB; iColX <= tB; iColX++)
      {
         RCIndex tPixel(tCenterPixel.mRow + iRowY, tCenterPixel.mCol + iColX);
         printf(" %8.4f", tImage.getScaled(tPixel));
      }
      printf("\n");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show image in tabular form.

void showImageTableByte(
   const char*   aLabel,   // Input
   cv::Mat&      aImage)   // Input
{
   // Guard.
   if (aImage.rows == 0)return;

   // Region of interest variables.
   RCIndex tCenterPixel = gImageParms.mRoiPixel;
   int tB = gImageParms.mRoiB;

   printf("\n");
   printf("********************************************* %-12s %4d %4d $ %1d %1d $ %4d %4d\n",
      aLabel, aImage.rows, aImage.cols, aImage.depth(), aImage.channels(),
      tCenterPixel.mRow, tCenterPixel.mRow);
   printf("\n");

   // Image wrapper.
   ImageWrapper tImage(aImage);

   SV::RCDitherLoop1 tLoop(tCenterPixel, tB, 1);

   // Print header.
   printf("     $ ");
   for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
   {
      printf(" %8d", tLoop.mCol);
   }
   printf("\n");
   printf("     $\n");

   // Loop through all of the rows and columns of the pulse.
   for (tLoop.firstRow(); tLoop.testRow(); tLoop.nextRow())
   {
      printf("%4d $ ", tLoop().mRow);
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         printf(" %8d", (int)tImage.at(tLoop()));
      }
      printf("\n");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace