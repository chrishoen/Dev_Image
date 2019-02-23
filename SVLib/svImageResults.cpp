/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svImageParms.h"
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

   mMinRowInt = 0;
   mMaxRowInt = 0;
   mMinColInt = 0;
   mMaxColInt = 0;
   
   mMinMin.reset();
   mMinMax.reset();
   mMaxMin.reset();
   mMaxMax.reset();

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
   if (SV::gImageParms.mRoiShowMode == 1)
   {
      Prn::print(aPF, "%7d ROW %4d %4d $ %4d %4d COL %4d %4d $ %4d %4d %s",
         mHighCount,
         mMinMin.mRow, mMinMin.mCol,
         mMinMax.mRow, mMinMax.mCol,
         mMaxMax.mRow, mMaxMax.mCol,
         mMaxMin.mRow, mMaxMin.mCol,
         aLabel);
   }

   if (SV::gImageParms.mRoiShowMode == 2)
   {
      Prn::print(aPF, "%7d ROW %4d %4d $ %4d %4d COL %4d %4d $ %4d %4d %s",
         mHighCount,
         mRowMin.mRow, mRowMin.mCol,
         mColMax.mRow, mColMax.mCol,
         mRowMax.mRow, mRowMax.mCol,
         mColMin.mRow, mColMin.mCol,
         aLabel);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

