/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risAlphaDir.h"
#include "svSysParms.h"
#include "svImageParms.h"
#include "svImageWrapper.h"

#include "svPixelFunctions.h"

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
// Show image info.

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
         printf(" %8d", (int)tImage.at(tPixel));
      }
      printf("\n");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
