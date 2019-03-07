#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Two dimensional row column sector.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "svRCIndex.h"
#include "svRCRect.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a two dimensional row column sector. It contains
// a center, a corner, and a rectangle.

class RCSector
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   // Center, upper left corner, and rectangle.
   RCIndex mCorner;
   RCIndex mCenter;
   RCRect  mRect;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Constructor.
   RCSector();
   void reset();
   RCSector(RCIndex aCorner, RCIndex aCenter);
   void set(RCIndex aCorner, RCIndex aCenter);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Show.
   void show (int aPrintFilter, char* aLabel);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

#if 0

         mACol                            mBCol
           01234567
mARow P1 0 +------------------------------------+ P2
         1 +Corner                              +
         2 +                                    +
         3 +                Center              +
         4 +                                    +
mBRow P4 5 +------------------------------------+ P3
                                    mBRow,mBCol

   ARow = Center.mRow - B
   BRow = Center.mRow + B
   ACol = Center.mRow - B
   BCol = Center.mCol + B

#endif
