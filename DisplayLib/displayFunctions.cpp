/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risAlphaDir.h"
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
   cv::Mat&      aImage)   // Input
{
   if (Display::gGraphicsThread == 0) return;
   Display::gGraphicsThread->postDraw2(new cv::Mat(aImage));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
