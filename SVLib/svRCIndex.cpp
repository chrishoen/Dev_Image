/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svRCIndex.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

RCIndex::RCIndex()
{
   mRow = 0;
   mCol = 0;
}

RCIndex::RCIndex(int aRow,int aCol)
{
   mRow = aRow;
   mCol = aCol;
}

void RCIndex::reset()
{
   mRow = 0;
   mCol = 0;
}

void RCIndex::set(int aRow,int aCol)
{
   mRow = aRow;
   mCol = aCol;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods:

// Show.
void RCIndex::show(int aPrintFilter, char* aLabel)
{
   Prn::print(aPrintFilter,"%-10s $$ %3d %3d",
      aLabel,
      mRow,
      mCol);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Operators:

// Equality.
bool RCIndex::operator==(RCIndex& aRight)const
{
   return
      (this->mRow == aRight.mRow) &&
      (this->mCol == aRight.mCol);

}

// Inequality.
bool RCIndex::operator!=(RCIndex& aRight)const
{
   return
      (this->mRow != aRight.mRow) ||
      (this->mCol != aRight.mCol);

}

// Increment.
void RCIndex::operator+=(RCIndex& aRight)
{
   this->mRow += aRight.mRow;
   this->mCol += aRight.mCol;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

// Execute to read variables from a command line command. 
void RCIndex::execute(Ris::CmdLineCmd* aCmd)
{
   mRow = aCmd->argInt(1);
   mCol = aCmd->argInt(2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Sum, difference

// Add two indices.
RCIndex operator+(RCIndex aLeft, RCIndex aRight)
{
   RCIndex tIndex;
   tIndex.mRow = aLeft.mRow + aRight.mRow;
   tIndex.mCol = aLeft.mCol + aRight.mCol;
   return tIndex;
}

// Subtract two indices.
RCIndex operator-(RCIndex aLeft, RCIndex aRight)
{
   RCIndex tIndex;
   tIndex.mRow = aLeft.mRow - aRight.mRow;
   tIndex.mCol = aLeft.mCol - aRight.mCol;
   return tIndex;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates an index loop iterator. It provides the
// functionality to construct for loops with array indices.
//

RCIndexLoop::RCIndexLoop()
{
   mFirst = true;
   mRow  = 0;
   mCol  = 0;
   mRows = 0;
   mCols = 0;
}

RCIndexLoop::RCIndexLoop(int aRows,int aCols)
{
   mFirst = true;
   mRow = 0;
   mCol = 0;
   mRows = aRows;
   mCols = aCols;
}

RCIndexLoop::RCIndexLoop(RCSize aSize)
{
   mFirst = true;
   mRow = 0;
   mCol = 0;
   mRows = aSize.mRows;
   mCols = aSize.mCols;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

RCIndex RCIndexLoop::operator()()
{
   return RCIndex(mRow,mCol);
}

void RCIndexLoop::first()
{
   mRow = 0;
   mCol = 0;
}
void RCIndexLoop::firstRow()
{
   mRow = 0;
}
void RCIndexLoop::firstCol()
{
   mCol = 0;
}

bool RCIndexLoop::test()
{
   return (mRow < mRows && mCol < mCols);
}

bool RCIndexLoop::testRow()
{
   mCol = 0;
   return (mRow < mRows);
}

bool RCIndexLoop::testCol()
{
   return (mCol < mCols);
}

void RCIndexLoop::nextRow()
{
   mRow++;
}

void RCIndexLoop::nextCol()
{
   mCol++;
}

void RCIndexLoop::next()
{
   if (++mCol == mCols)      
   {
      mCol = 0;
      mRow++;
   }
}

bool RCIndexLoop::advance()
{
   if (++mCol == mCols)      
   {
      mCol = 0;
      if (++mRow == mRows)
      {
         return false;
      }
   }
   return true;
}

bool RCIndexLoop::loop()
{
   if (mFirst)
   {
      mFirst = false;
      return true;
   }

   if (++mCol == mCols)
   {
      mCol = 0;
      if (++mRow == mRows)
      {
         return false;
      }
   }
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates an index loop iterator. It provides the
// functionality to construct for loops with array indices.
// It is used for loops that dither a square around a point.

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Infrastrucure.

RCDitherLoop1::RCDitherLoop1(int aLoop,int aDelta)
{
   mRow = -aLoop*aDelta;
   mCol = -aLoop*aDelta;
   mLoop = aLoop;
   mDelta = aDelta;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

bool RCDitherLoop1::advance()
{
   if (mCol != mLoop*mDelta)
   {
      mCol += mDelta;
   }
   else
   {
      mCol = -mLoop*mDelta;
      mRow += mDelta;
   }

   return mRow <= mLoop*mDelta;
}

RCIndex RCDitherLoop1::operator()()
{
   return RCIndex(mRow, mCol);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates an index loop iterator. It provides the
// functionality to construct for loops with array indices.
// It is used for loops that dither a square around a point.

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Infrastrucure.

RCDitherLoop2::RCDitherLoop2(int aLoop,int aDelta)
{
   mRow = -aLoop*aDelta;
   mCol = -aLoop*aDelta;
   mLoop = aLoop;
   mDelta = aDelta;
   mMoveRight = true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

bool RCDitherLoop2::advance()
{
   if (mMoveRight)
   {
      if (mCol != mLoop*mDelta)
      {
         mCol += mDelta;
      }
      else
      {
         mMoveRight = false;
         mRow += mDelta;
      }
   }
   else
   {
      if (mCol != -mLoop*mDelta)
      {
         mCol -= mDelta;
      }
      else
      {
         mMoveRight = true;
         mRow += mDelta;
      }
   }

   return mRow <= mLoop*mDelta;
}

RCIndex RCDitherLoop2::operator()()
{
   return RCIndex(mRow, mCol);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
