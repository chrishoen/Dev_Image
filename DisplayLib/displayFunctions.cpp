/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risAlphaDir.h"
#include "displayParms.h"
#include "displayGraphicsThread.h"

#include "displayFunctions.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Display
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show image.

void showImage(
   const char*   aFileName)   // Input
{
   if (Display::gGraphicsThread == 0) return;

   char tBuffer[100];
   std::string* tFilePath = new std::string(Ris::getAlphaFilePath_Image(tBuffer, aFileName));

   Display::gGraphicsThread->postDraw1(tFilePath);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show image.

void showImage(
   cv::Mat&      aInputImage)   // Input
{
   if (Display::gGraphicsThread == 0) return;

   printf("Display::showImage1 %4d %4d $ %1d %1d $\n",
      aInputImage.rows, aInputImage.cols, aInputImage.depth(), aInputImage.channels());

   // Convert to color.
   cv::Mat tColorImage;
   if (aInputImage.channels() == 3)
   {
      tColorImage = aInputImage;
   }
   else
   {
      cv::cvtColor(aInputImage, tColorImage, CV_GRAY2RGB);
   }

   // Convert to display size.
   int tDisplayRows = gParms.mWindowHeight;
   int tDisplayCols = gParms.mWindowWidth;
   cv::Mat tDisplayImage;

   if (tColorImage.rows == tDisplayRows || tColorImage.cols == tDisplayCols)
   {
      tDisplayImage = tColorImage;
   }
   else
   {
      cv::resize(tColorImage, tDisplayImage, cv::Size(tDisplayRows,tDisplayCols), 0, 0, CV_INTER_LINEAR);
   }

   printf("Display::showImage2 %4d %4d $ %1d %1d $\n",
      tDisplayImage.rows, tDisplayImage.cols, tDisplayImage.depth(), tDisplayImage.channels());

   // Display the converted image.
   Display::gGraphicsThread->postDraw2(new cv::Mat(tDisplayImage));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
