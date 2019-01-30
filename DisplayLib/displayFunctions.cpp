/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

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
// Show image info.

void showImage(
   cv::Mat&      aImage)   // Input
{
   Display::gGraphicsThread->postDraw1(new cv::Mat(aImage));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
