#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Miscellaneous support functions
==============================================================================*/
#include <opencv2/core/core.hpp>
#include "svRCIndex.h"
#include "svContourRecord.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show functions.

// Show record list.
void showRecordList(
   int                  aPF,           // Input
   const char*          aLabel,        // Input
   ContourRecordList&   aRecordList);  // Input

// Show record array.
void showRecordArray(
   int                  aCode,         // Input
   const char*          aLabel,        // Input
   ContourRecordArray&  aRecordArray); // Input

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
