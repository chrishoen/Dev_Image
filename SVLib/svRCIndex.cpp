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
   mRowForward = true;
   mColForward = true;
   mRow  = 0;
   mCol  = 0;
   mRows = 0;
   mCols = 0;
}

RCIndexLoop::RCIndexLoop(int aRows,int aCols)
{
   mFirst = true;
   mRowForward = true;
   mColForward = true;
   mRow = 0;
   mCol = 0;
   mRows = aRows;
   mCols = aCols;
}

RCIndexLoop::RCIndexLoop(RCSize aSize)
{
   mFirst = true;
   mRowForward = true;
   mColForward = true;
   mRow = 0;
   mCol = 0;
   mRows = aSize.mRows;
   mCols = aSize.mCols;
}

RCIndex RCIndexLoop::operator()()
{
   return RCIndex(mRow, mCol);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

void RCIndexLoop::first()
{
   firstRow();
   firstCol();
}
void RCIndexLoop::firstRow()
{
   if (mRowForward)
   {
      mRow = 0;
   }
   else
   {
      mRow = mRows - 1;
   }
}
void RCIndexLoop::firstCol()
{
   if (mColForward)
   {
      mCol = 0;
   }
   else
   {
      mCol = mCols - 1;
   }
}

bool RCIndexLoop::test()
{
   return testRow() && testCol();
}

bool RCIndexLoop::testRow()
{
   if (mRowForward)
   {
      return (mRow < mRows);
   }
   else
   {
      return (mRow >= 0);
   }
}

bool RCIndexLoop::testCol()
{
   if (mColForward)
   {
      return (mCol < mCols);
   }
   else
   {
      return (mCol >= 0);
   }
}

void RCIndexLoop::nextRow()
{
   if (mRowForward)
   {
      mRow++;
   }
   else
   {
      mRow--;
   }
}

void RCIndexLoop::nextCol()
{
   if (mColForward)
   {
      mCol++;
   }
   else
   {
      mCol--;
   }
}

void RCIndexLoop::next()
{
   nextCol();
   if (!testCol())
   {
      firstCol();
      nextRow();
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

   return advance();
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
   mFirst = true;
   mRow = -aLoop*aDelta;
   mCol = -aLoop*aDelta;
   mLoop = aLoop;
   mDelta = aDelta;
}

RCIndex RCDitherLoop1::operator()()
{
   return RCIndex(mRow, mCol);
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

bool RCDitherLoop1::loop()
{
   if (mFirst)
   {
      mFirst = false;
      return true;
   }

   return advance();
}

void RCDitherLoop1::first()
{
   mRow = -mLoop * mDelta;
   mCol = -mLoop * mDelta;
}

bool RCDitherLoop1::test()
{
   return mRow <= mLoop * mDelta;
}

void RCDitherLoop1::next()
{
   if (mCol != mLoop * mDelta)
   {
      mCol += mDelta;
   }
   else
   {
      mCol = -mLoop * mDelta;
      mRow += mDelta;
   }
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
   mFirst = true;
   mRow = -aLoop*aDelta;
   mCol = -aLoop*aDelta;
   mLoop = aLoop;
   mDelta = aDelta;
   mMoveRight = true;
}

RCIndex RCDitherLoop2::operator()()
{
   return RCIndex(mRow, mCol);
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

bool RCDitherLoop2::loop()
{
   if (mFirst)
   {
      mFirst = false;
      return true;
   }

   return advance();
}

void RCDitherLoop2::first()
{
   mRow = -mLoop * mDelta;
   mCol = -mLoop * mDelta;
}

bool RCDitherLoop2::test()
{
   return mRow <= mLoop * mDelta;
}

void RCDitherLoop2::next()
{
   if (mMoveRight)
   {
      if (mCol != mLoop * mDelta)
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
      if (mCol != -mLoop * mDelta)
      {
         mCol -= mDelta;
      }
      else
      {
         mMoveRight = true;
         mRow += mDelta;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
