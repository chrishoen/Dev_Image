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
   cv::Mat&      aInput)   // Input
{
   Prn::print(aPF, "%-12s %4d %4d $ %3d %3d ", aLabel, aInput.rows, aInput.cols, aInput.depth(), aInput.channels());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show image in tabular form.

void showImage2d(
   const char*   aLabel,   // Input
   cv::Mat&      aInput)   // Input
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   // Guard.
   if (aInput.rows == 0)return;

   // Region of interest variables.
   RCIndex tCenterPixel = gImageParms.mRoiPixel;
   int tB = gImageParms.mRoiB;
   int tHeaderCode = gImageParms.mRoiHeaderCode;

   printf("\n");
   printf("********************************************* %-12s %4d %4d $ %1d %1d $ %4d %4d\n",
      aLabel, aInput.rows, aInput.cols, aInput.depth(), aInput.channels(),
      tCenterPixel.mRow, tCenterPixel.mCol);
   printf("\n");

   // Image wrapper.
   ImageWrapper tImage(aInput);

   // Dither loop.
   SV::RCDitherLoop1 tLoop(tCenterPixel, tB, 1);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Print header.

   if (tHeaderCode == 0)
   {
      // Print header 1.
      printf("     $ ");
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         printf(" %1d", (tLoop.mCol / 100) % 10);
      }
      printf("\n");

      // Print header 2.
      printf("     $ ");
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         printf(" %1d", (tLoop.mCol / 10) % 10);
      }
      printf("\n");

      // Print header 3.
      printf("     $ ");
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         printf(" %1d", tLoop.mCol % 10);
      }
      printf("\n");

      printf("     $\n");
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Print roi.

   // Loop through all of the rows and columns of the roi.
   for (tLoop.firstRow(); tLoop.testRow(); tLoop.nextRow())
   {
      printf("%4d $ ", tLoop().mRow);
      if (tHeaderCode != 0)
      {
         for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
         {
            printf("  ");
         }
         printf("     ");
      }
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         int tValue = (int)tImage.at(tLoop());
         if (tValue == 0)           printf(" .");
         else if (tValue == 255)    printf(" x");
         else                       printf(" %1x", tValue / 16);
      }
      printf("\n");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show image in tabular form.

void showImage3d(
   const char*   aLabel,    // Input
   cv::Mat&      aInputS1,  // Input
   cv::Mat&      aInputS2,  // Input
   cv::Mat&      aInputS3)  // Input
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   // Guard.
   if (aInputS1.rows == 0)return;
   if (aInputS2.rows == 0)return;
   if (aInputS3.rows == 0)return;

   // Region of interest variables.
   RCIndex tCenterPixel = gImageParms.mRoiPixel;
   int tB = gImageParms.mRoiB;
   int tHeaderCode = gImageParms.mRoiHeaderCode;

   printf("\n");
   printf("********************************************* %-12s %4d %4d $ %1d %1d $ %4d %4d\n",
      aLabel, aInputS2.rows, aInputS2.cols, aInputS2.depth(), aInputS2.channels(),
      tCenterPixel.mRow, tCenterPixel.mCol);
   printf("\n");

   // Image wrapper.
   ImageWrapper tInputS1(aInputS1);
   ImageWrapper tInputS2(aInputS2);
   ImageWrapper tInputS3(aInputS3);

   // Dither loop.
   SV::RCDitherLoop1 tLoop(tCenterPixel, tB, 1);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Print header.

   if (tHeaderCode == 0)
   {
      // Print header 1.
      printf("     $ ");
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         printf(" %1d", (tLoop.mCol / 100) % 10);
      }
      printf("     ");
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         printf(" %1d", (tLoop.mCol / 100) % 10);
      }
      printf("     ");
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         printf(" %1d", (tLoop.mCol / 100) % 10);
      }
      printf("\n");

      // Print header 2.
      printf("     $ ");
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         printf(" %1d", (tLoop.mCol / 10) % 10);
      }
      printf("     ");
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         printf(" %1d", (tLoop.mCol / 10) % 10);
      }
      printf("     ");
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         printf(" %1d", (tLoop.mCol / 10) % 10);
      }
      printf("\n");

      // Print header 3.
      printf("     $ ");
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         printf(" %1d", tLoop.mCol % 10);
      }
      printf("     ");
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         printf(" %1d", tLoop.mCol % 10);
      }
      printf("     ");
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         printf(" %1d", tLoop.mCol % 10);
      }
      printf("\n");

      printf("     $\n");
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Print roi.

   // Loop through all of the rows and columns of the roi.
   for (tLoop.firstRow(); tLoop.testRow(); tLoop.nextRow())
   {
      printf("%4d $ ", tLoop().mRow);
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         int tValue = (int)tInputS1.at(tLoop());
         if (tValue == 0)           printf(" .");
         else if (tValue == 255)    printf(" x");
         else                       printf(" %1x", tValue / 16);
      }
      printf("     ");
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         int tValue = (int)tInputS2.at(tLoop());
         if (tValue == 0)           printf(" .");
         else if (tValue == 255)    printf(" x");
         else                       printf(" %1x", tValue / 16);
      }
      printf("     ");
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         int tValue = (int)tInputS3.at(tLoop());
         if (tValue == 0)           printf(" .");
         else if (tValue == 255)    printf(" x");
         else                       printf(" %1x", tValue / 16);
      }
      printf("\n");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
