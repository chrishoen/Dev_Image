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
   int           aPF,      // Input
   const char*   aLabel,   // Input
   cv::Mat&      aImage)   // Input
{
   Prn::print(aPF, "%-12s %4d %4d $ %3d %3d ", aLabel, aImage.rows, aImage.cols, aImage.depth(), aImage.channels());
   Prn::print(aPF, "");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show image in tabular form.

void showImageTable1(
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
      printf(" %1d", (tLoop.mCol / 100) % 10);
   }
   printf("\n");

   printf("     $ ");
   for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
   {
      printf(" %1d", (tLoop.mCol / 10) % 10);
   }
   printf("\n");

   printf("     $ ");
   for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
   {
      printf(" %1d", tLoop.mCol % 10);
   }
   printf("\n");


   printf("     $\n");

   // Loop through all of the rows and columns of the pulse.
   for (tLoop.firstRow(); tLoop.testRow(); tLoop.nextRow())
   {
      printf("%4d $ ", tLoop().mRow);
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         int tValue = (int)tImage.at(tLoop());
         printf(" %2x",tValue);
      }
      printf("\n");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show image in tabular form.

void showImageTable2(
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
      printf(" %1d", (tLoop.mCol / 100) % 10);
   }
   printf("\n");

   printf("     $ ");
   for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
   {
      printf(" %1d", (tLoop.mCol / 10) % 10);
   }
   printf("\n");

   printf("     $ ");
   for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
   {
      printf(" %1d", tLoop.mCol % 10);
   }
   printf("\n");


   printf("     $\n");

   // Loop through all of the rows and columns of the pulse.
   for (tLoop.firstRow(); tLoop.testRow(); tLoop.nextRow())
   {
      printf("%4d $ ", tLoop().mRow);
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         int tValue = (int)tImage.at(tLoop());
         if (tValue == 0)
         {
            printf(" .");
         }
         else if (tValue == 255)
         {
            printf(" x");
         }
         else
         {
            printf(" %1x",tValue/16);
         }
      }
      printf("\n");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show image in tabular form.

void showImageTable3(
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
      printf("  %1d", (tLoop.mCol / 100) % 10);
   }
   printf("\n");

   printf("     $ ");
   for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
   {
      printf("  %1d", (tLoop.mCol / 10) % 10);
   }
   printf("\n");

   printf("     $ ");
   for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
   {
      printf("  %1d", tLoop.mCol % 10);
   }
   printf("\n");


   printf("     $\n");

   // Loop through all of the rows and columns of the pulse.
   for (tLoop.firstRow(); tLoop.testRow(); tLoop.nextRow())
   {
      printf("%4d $ ", tLoop().mRow);
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         int tValue = (int)tImage.at(tLoop());
         if (tValue == 0)
         {
            printf("  .");
         }
         else if (tValue == 255)
         {
            printf("  x");
         }
         else
         {
            printf("  %1x",tValue/16);
         }
      }
      printf("\n");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
