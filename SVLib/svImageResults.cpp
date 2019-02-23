/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svImageResults.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

ImageResults::ImageResults()
{
   reset();
}

void ImageResults::reset()
{
   mFirst = true;
   mTotalCount = 0;
   mHighCount = 0;
   mRowMin.reset();
   mRowMax.reset();
   mColMin.reset();
   mColMax.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void ImageResults::show(int aPF, const char* aLabel)
{
   Prn::print(aPF, "%7d ROW %4d %4d $ %4d %4d COL %4d %4d $ %4d %4d %s",
      mHighCount,
      mRowMin.mRow, mRowMin.mCol,
      mColMax.mRow, mColMax.mCol,
      mRowMax.mRow, mRowMax.mCol,
      mColMin.mRow, mColMin.mCol,
      aLabel);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

