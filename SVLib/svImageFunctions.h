#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Miscellaneous support functions
==============================================================================*/
#include <opencv2/core/core.hpp>
#include "svDefs.h"
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
// Conversion functions.

// Convert image to target format.
void convertImageToTarget(
   cv::Mat&      aInput,    // Input
   cv::Mat&      aOutput);  // Output

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Conversion functions.

// Write image to file.
void writeImageToFile(
   cv::Mat&      aImage,      // Input
   const char*   aFileName);  // Input

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
