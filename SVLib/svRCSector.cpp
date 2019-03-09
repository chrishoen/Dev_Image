/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svRCSector.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

RCSector::RCSector()
{
   reset();
}

void RCSector::reset()
{
   mCorner.reset();
   mCenter.reset();
   mRect.reset();
}

RCSector::RCSector(RCIndex aCorner, RCIndex aCenter)
{
   set(aCorner, aCenter);
}

void RCSector::set(RCIndex aCorner, RCIndex aCenter)
{
   mCenter = aCenter;
   mCorner = aCorner;

   int tRowD = 2 * (mCenter.mRow - mCorner.mRow);
   int tColD = 2 * (mCenter.mCol - mCorner.mCol);

   mRect.mARow = mCorner.mRow;
   mRect.mBRow = mCorner.mRow + tRowD;

   mRect.mACol = mCorner.mCol;
   mRect.mBCol = mCorner.mCol + tColD;

}

// Execute to read variables from a command line command. 
void RCSector::execute(Ris::CmdLineCmd* aCmd)
{
   RCIndex tCorner, tCenter;
   tCorner.mRow = aCmd->argInt(1);
   tCorner.mCol = aCmd->argInt(2);
   tCenter.mRow = aCmd->argInt(1);
   tCenter.mCol = aCmd->argInt(2);
   set(tCorner, tCenter);
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void RCSector::show1(int aPF,char* aLabel)
{
   Prn::print(aPF, "%-10s                   %4d %4d   %4d %4d",
      aLabel,
      mCorner.mRow,
      mCorner.mCol,
      mCenter.mRow,
      mCenter.mCol);
}

void RCSector::show2(int aPF, char* aLabel)
{
   Prn::print(aPF, "%-10s $$ %4d %4d",
      aLabel,
      mCorner.mRow,
      mCorner.mCol);

   Prn::print(aPF, "%-10s $$ %4d %4d",
      aLabel,
      mCenter.mRow,
      mCenter.mCol);

   Prn::print(aPF, "%-10s $$ %4d %4d %4d %4d",
      aLabel,
      mRect.mARow,
      mRect.mBRow,
      mRect.mACol,
      mRect.mBCol);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
