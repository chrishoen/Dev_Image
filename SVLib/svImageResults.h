#pragma once

/*==============================================================================
Image evaluation results.
==============================================================================*/

#include "svRCIndex.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class stores trial results.

class ImageResults
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // If true then first evalualtion.
   bool mFirst;

   // Counts.
   int mTotalCount;
   int mHighCount;

   // Row and column mins and maxs.
   RCIndex mRowMin;
   RCIndex mRowMax;
   RCIndex mColMin;
   RCIndex mColMax;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Constructor.
   ImageResults();
   void reset();

   // Show.
   void show(int aPrintFilter,const char* aLabel);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
