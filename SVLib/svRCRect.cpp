/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svRCRect.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

RCRect::RCRect()
{
   reset();
}

void RCRect::reset()
{
   mARow = 0;
   mBRow = 0;
   mACol = 0;
   mBCol = 0;
}

RCRect::RCRect(int aARow, int aBRow, int aACol, int aBCol)
{
   initialize(aARow,aBRow,aACol,aBCol);
}

void RCRect::initialize(int aARow, int aBRow, int aACol, int aBCol)
{
   mARow = aARow;
   mBRow = aBRow;
   mACol = aACol;
   mBCol = aBCol;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Split this rectangle into two halfs, one left and one left.
// Return true if the split actually ocurred, that the input 
// width was not equal to one.

bool RCRect::splitLeftRight(
   RCRect& aLeft,       // Output
   RCRect& aRight)      // Output
{
   // Guard.
   if (width() <= 1)
   {
      aLeft  = *this;
      aRight = *this;
      return false;
   } 

   // Calculate left side.
   aLeft.reset();
   aLeft.mACol = mACol;
   aLeft.mBCol = mACol + (width()+1)/2;
   aLeft.mARow = mARow;
   aLeft.mBRow = mBRow;

   // Calculate right side.
   aRight.reset();
   aRight.mACol = aLeft.mBCol;
   aRight.mBCol = mBCol;
   aRight.mARow = mARow;
   aRight.mBRow = mBRow;

   // Done.
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Split this rectangle into two halfs, one upper and one lower.
// Return true if the split actually ocurred, that the input 
// height was not equal to one.

bool RCRect::splitUpperLower(
   RCRect& aUpper,      // Output
   RCRect& aLower)      // Output
{
   // Guard.
   if (height() <= 1)
   {
      aUpper  = *this;
      aLower = *this;
      return false;
   }

   // Calculate upper side.
   aUpper.reset();
   aUpper.mARow = mARow;
   aUpper.mBRow = mARow + (height()+1)/2;
   aUpper.mACol = mACol;
   aUpper.mBCol = mBCol;

   // Calculate lower side.
   aLower.reset();
   aLower.mARow = aUpper.mBRow;
   aLower.mBRow = mBRow;
   aLower.mACol = mACol;
   aLower.mBCol = mBCol;

   // Done.
   return true;

}
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void RCRect::show(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s $$ %3d %3d %3d %3d",
      aLabel,
      mARow,
      mBRow,
      mACol,
      mBCol);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Operators.

// Return the intersection of two rectangles.
RCRect RCRect::operator&(RCRect aRight)
{
   RCRect tRect;
   tRect.mARow = my_imax(this->mARow,aRight.mARow);
   tRect.mBRow = my_imin(this->mBRow,aRight.mBRow);

   tRect.mACol = my_imax(this->mACol,aRight.mACol);
   tRect.mBCol = my_imin(this->mBCol,aRight.mBCol);

   return tRect;
}

// Set this rectangle to the intersection of itself and another rectangle.
RCRect RCRect::operator&=(RCRect aRight)
{
   this->mARow = my_imax(this->mARow,aRight.mARow);
   this->mBRow = my_imin(this->mBRow,aRight.mBRow);

   this->mACol = my_imax(this->mACol,aRight.mACol);
   this->mBCol = my_imin(this->mBCol,aRight.mBCol);

   return *this;
}

// Return this rectangle plus an offset.
RCRect RCRect::operator+(RCIndex aRight)
{
   RCRect tRect;
   tRect.mARow = this->mARow + aRight.mRow;
   tRect.mBRow = this->mBRow + aRight.mRow;

   tRect.mACol = this->mACol + aRight.mCol;
   tRect.mBCol = this->mBCol + aRight.mCol;

   return tRect;
}

// Add an offset to this rectangle.
RCRect RCRect::operator+=(RCIndex aRight)
{
   this->mARow += aRight.mRow;
   this->mBRow += aRight.mRow;

   this->mACol += aRight.mCol;
   this->mBCol += aRight.mCol;

   return *this;
}

// Equality.
bool RCRect::operator==(RCRect& aRight)const
{
   return
      (this->mARow == aRight.mARow) &&
      (this->mBRow == aRight.mBRow) &&
      (this->mACol == aRight.mACol) &&
      (this->mBCol == aRight.mBCol);
}

// Inequality.
bool RCRect::operator!=(RCRect& aRight)const
{
   return
      (this->mARow != aRight.mARow) ||
      (this->mBRow != aRight.mBRow) ||
      (this->mACol != aRight.mACol) ||
      (this->mBCol != aRight.mBCol);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return true if the rectangle contains the index,

bool RCRect::contains(RCIndex aIndex)
{
   if (aIndex.mRow < mARow) return false;
   if (aIndex.mRow > mBRow) return false;
   if (aIndex.mCol < mACol) return false;
   if (aIndex.mCol > mBCol) return false;
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute to read variables from a command line command. 

void RCRect::execute(Ris::CmdLineCmd* aCmd)
{
   initialize(
      aCmd->argInt(1),
      aCmd->argInt(2),
      aCmd->argInt(3),
      aCmd->argInt(4));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
