#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Common definitions
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

namespace Defs
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants

// Filtered image types.
static const int cNone             = 0;
static const int cFilteredImage    = 1;
static const int cDynamicRangeHigh = 2;
static const int cNoiseFloor       = 3;

// Log files.
static const int cLogGrid          = 0;
static const int cLogPointCenter   = 1;
static const int cLogCoefficeints  = 2;
static const int cLogRowColCount   = 3;
static const int cLogMaxValue      = 4;
static const int cLogResults       = 5;
static const int cLogImagePoints   = 6;

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

// Grid types.
static const int cPGrid1 = 1;
static const int cPGrid2 = 2;
static const int cUGrid1 = 3;
static const int cUGrid2 = 4;

// Error codes.
static const int cTargetError1 = -101;
static const int cCameraError1 = -102;
static const int cTargetError2 = -201;
static const int cCameraError2 = -202;
static const int cPnPCheckArgumentsError1 = -103;
static const int cStage4NotReachedError1 = -104;

// Image scale factor, 100.0 corresponds to max value 65535.
static const double cImageScale    = 100.0/65536.0;

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

