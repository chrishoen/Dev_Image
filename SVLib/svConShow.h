#pragma once

/*==============================================================================
Contour filter - show functions.
==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <opencv2/core/core.hpp>
#include "svRCIndex.h"
#include "svConRecordArray.h"
#include "svConRecordList.h"

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
   ConRecordList&   aRecordList);  // Input

// Show record array.
void showRecordArray(
   int                  aCode,         // Input
   const char*          aLabel,        // Input
   ConRecordArray&  aRecordArray); // Input

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
