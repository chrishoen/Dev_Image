#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Miscellaneous support functions
==============================================================================*/
#include <opencv2/core/core.hpp>

#include "svRCIndex.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show functions.

// Show image info.
void showImageInfo(
   int           aPF,      // Input
   const char*   aLabel,   // Input
   cv::Mat&      aImage);  // Input

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show functions.

// Show image in tabular form.
void showImageTableFloat(
   const char*   aLabel,   // Input
   cv::Mat&      aImage);  // Input

// Show image in tabular form.
void showImageTableByte(
   const char*   aLabel,   // Input
   cv::Mat&      aImage);  // Input

// Show image in tabular form.
void showImageTable1(
   const char*   aLabel,   // Input
   cv::Mat&      aImage);  // Input

// Show image in tabular form.
void showImageTable2(
   const char*   aLabel,   // Input
   cv::Mat&      aImage);  // Input

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
