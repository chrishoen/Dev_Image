#pragma once

/*==============================================================================
Row and column loop index.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineCmd.h"
#include "prnPrint.h"

#include "svRCIndex.h"
#include "svRCSize.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates an index loop iterator. It provides the
// functionality to construct for loops with array indices.

class RCIndexLoop
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   bool mFirst;
   bool mRowForward;
   bool mColForward;
   short int mRow;
   short int mCol;
   short int mRows;
   short int mCols;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   RCIndexLoop()
   {
      mFirst = true;
      mRowForward = true;
      mColForward = true;
      mRow = 0;
      mCol = 0;
      mRows = 0;
      mCols = 0;
   }

   // Constructor.
   RCIndexLoop(int aRows, int aCols)
   {
      mFirst = true;
      mRowForward = true;
      mColForward = true;
      mRow = 0;
      mCol = 0;
      mRows = aRows;
      mCols = aCols;
   }

   // Constructor.
   RCIndexLoop(RCSize aSize)
   {
      mFirst = true;
      mRowForward = true;
      mColForward = true;
      mRow = 0;
      mCol = 0;
      mRows = aSize.mRows;
      mCols = aSize.mCols;
   }

   // Return the current row and column.
   RCIndex  operator()()
   {
      return RCIndex(mRow, mCol);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   void firstRow()
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

   void firstCol()
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

   void first()
   {
      firstRow();
      firstCol();
   }

   bool testRow()
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

   bool testCol()
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

   bool test()
   {
      return testRow() && testCol();
   }

   void nextRow()
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

   void nextCol()
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

   void next()
   {
      nextCol();
      if (!testCol())
      {
         firstCol();
         nextRow();
      }
   }

   bool advance()
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

   bool loop()
   {
      if (mFirst)
      {
         mFirst = false;
         return true;
      }

      return advance();
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates an index loop iterator. It provides the
// functionality to construct for loops with array indices.
// It is used for loops that dither a square around a point.
//
// For each row, it moves left to right, see text at the end of this file.
// >>>>>
// >>>>>
// >>>>>
// >>>>>
// >>>>>

class RCDitherLoop1
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   bool mFirst;
   short int mRow;
   short int mCol;
   short int mLoop;
   short int mDelta;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   RCDitherLoop1(int aLoop, int aDelta)
   {
      mFirst = true;
      mRow = -aLoop * aDelta;
      mCol = -aLoop * aDelta;
      mLoop = aLoop;
      mDelta = aDelta;
   }

   // Return the current row and column.
   RCIndex operator()()
   {
      return RCIndex(mRow, mCol);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Advance the loop. Return true if the loop is not finished.
   bool advance()
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

      return mRow <= mLoop * mDelta;
   }

   bool loop()
   {
      if (mFirst)
      {
         mFirst = false;
         return true;
      }

      return advance();
   }

   void first()
   {
      mRow = -mLoop * mDelta;
      mCol = -mLoop * mDelta;
   }

   bool test()
   {
      return mRow <= mLoop * mDelta;
   }

   void next()
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
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates an index loop iterator. It provides the
// functionality to construct for loops with array indices.
// It is used for loops that dither a square around a point.
//
// For odd rows, it moves left to right and then for even rows it moves right
// to left, see text at the end of this file.
// >>>>>
// <<<<<
// >>>>>
// <<<<<
// >>>>>

class RCDitherLoop2
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   bool mFirst;
   short int mRow;
   short int mCol;
   short int mLoop;
   short int mDelta;
   bool mMoveRight;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   RCDitherLoop2(int aLoop, int aDelta)
   {
      mFirst = true;
      mRow = -aLoop * aDelta;
      mCol = -aLoop * aDelta;
      mLoop = aLoop;
      mDelta = aDelta;
      mMoveRight = true;
   }

   // Return the current row and column.
   RCIndex operator()()
   {
      return RCIndex(mRow, mCol);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Advance the loop. Return true if the loop is not finished.
   bool advance()
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

      return mRow <= mLoop * mDelta;
   }

   bool loop()
   {
      if (mFirst)
      {
         mFirst = false;
         return true;
      }

      return advance();
   }

   void first()
   {
      mRow = -mLoop * mDelta;
      mCol = -mLoop * mDelta;
   }

   bool test()
   {
      return mRow <= mLoop * mDelta;
   }

   void next()
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
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates an index loop iterator. It provides the
// functionality to construct for loops with array indices.
// It is used for loops that travel square circuit around a point.
//
// a a a
// a X a 
// a a a
//
// a a a a a
// a       a 
// a   X   a 
// a       a 
// a a a a a

class RCCircuitLoop
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   bool mFirst;
   short int mSide;
   short int mDelta;
   short int mRow;
   short int mCol;
   short int mRowA;
   short int mColA;
   short int mRowC;
   short int mColC;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   RCCircuitLoop::RCCircuitLoop(int aDelta)
   {
      mFirst = true;
      mSide = 0;
      mDelta = aDelta;
      mRowA = -aDelta;
      mColA = -aDelta;
      mRowC = 0;
      mColC = 0;
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;
   }

   // Constructor.
   RCCircuitLoop::RCCircuitLoop(RCIndex aCenter, int aDelta)
   {
      mFirst = true;
      mSide = 0;
      mDelta = aDelta;
      mRowA = -aDelta;
      mColA = -aDelta;
      mRowC = aCenter.mRow;
      mColC = aCenter.mCol;
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;
   }

   // Return the current row and column.
   RCIndex RCCircuitLoop::operator()()
   {
      return RCIndex(mRow, mCol);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Advance the loop. Return true if the loop is not finished.
   bool advance()
   {
      if (mSide == 0)
      {
         if (mColA < mDelta)
         {
            mColA++;
         }
         else
         {
            mSide = 1;
            mRowA++;
         }
         mRow = mRowA + mRowC;
         mCol = mColA + mColC;
         return true;
      }

      if (mSide == 1)
      {
         if (mRowA < mDelta)
         {
            mRowA++;
         }
         else
         {
            mSide = 2;
            mColA--;
         }
         mRow = mRowA + mRowC;
         mCol = mColA + mColC;
         return true;
      }

      if (mSide == 2)
      {
         if (mColA > -mDelta)
         {
            mColA--;
         }
         else
         {
            mSide = 3;
            mRowA--;
         }
         mRow = mRowA + mRowC;
         mCol = mColA + mColC;
         return true;
      }

      if (mSide == 3)
      {
         if (mRowA > -mDelta + 1)
         {
            mRowA--;
         }
         else
         {
            mSide = 4;
            return false;
         }
         mRow = mRowA + mRowC;
         mCol = mColA + mColC;
         return true;
      }
      return false;
   }

   bool loop()
   {
      if (mFirst)
      {
         mFirst = false;
         return true;
      }

      return advance();
   }

   void first()
   {
      mRowA = -mDelta;
      mColA = -mDelta;
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;
   }

   bool test()
   {
      return mSide != 4;
   }

   void next()
   {
      advance();
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



#if 0

SV::RCIndexLoop tLoop(4, 4);
for (; tLoop.testRow(); tLoop.nextRow())
{
   Prn::print(0, "");
   Prn::print(0, "LoopRow %3d %3d", tLoop.mRow, tLoop.mCol);
   for (; tLoop.testCol(); tLoop.nextCol())
   {
      Prn::print(0, "Loop    %3d %3d", tLoop.mRow, tLoop.mCol);
   }
}

Numbers**********************************************BEGIN
go6

LoopRow   0   0
Loop      0   0
Loop      0   1
Loop      0   2
Loop      0   3

LoopRow   1   0
Loop      1   0
Loop      1   1
Loop      1   2
Loop      1   3

LoopRow   2   0
Loop      2   0
Loop      2   1
Loop      2   2
Loop      2   3

LoopRow   3   0
Loop      3   0
Loop      3   1
Loop      3   2
Loop      3   3


SV::RCIndexLoop tLoop(4, 4);
for (; tLoop.test(); tLoop.next())
{
   Prn::print(0, "Loop %3d %3d", tLoop.mRow, tLoop.mCol);
}

Numbers**********************************************BEGIN
go7
Loop   0   0
Loop   0   1
Loop   0   2
Loop   0   3
Loop   1   0
Loop   1   1
Loop   1   2
Loop   1   3
Loop   2   0
Loop   2   1
Loop   2   2
Loop   2   3
Loop   3   0
Loop   3   1
Loop   3   2
Loop   3   3

Test**********************************************BEGIN
go4 2 1
DitherLoop1  -2  -2
DitherLoop1  -2  -1
DitherLoop1  -2   0
DitherLoop1  -2   1
DitherLoop1  -2   2
DitherLoop1  -1  -2
DitherLoop1  -1  -1
DitherLoop1  -1   0
DitherLoop1  -1   1
DitherLoop1  -1   2
DitherLoop1   0  -2
DitherLoop1   0  -1
DitherLoop1   0   0
DitherLoop1   0   1
DitherLoop1   0   2
DitherLoop1   1  -2
DitherLoop1   1  -1
DitherLoop1   1   0
DitherLoop1   1   1
DitherLoop1   1   2
DitherLoop1   2  -2
DitherLoop1   2  -1
DitherLoop1   2   0
DitherLoop1   2   1
DitherLoop1   2   2


Test**********************************************BEGIN
go5 2 1
DitherLoop2  -2  -2
DitherLoop2  -2  -1
DitherLoop2  -2   0
DitherLoop2  -2   1
DitherLoop2  -2   2
DitherLoop2  -1   2
DitherLoop2  -1   1
DitherLoop2  -1   0
DitherLoop2  -1  -1
DitherLoop2  -1  -2
DitherLoop2   0  -2
DitherLoop2   0  -1
DitherLoop2   0   0
DitherLoop2   0   1
DitherLoop2   0   2
DitherLoop2   1   2
DitherLoop2   1   1
DitherLoop2   1   0
DitherLoop2   1  -1
DitherLoop2   1  -2
DitherLoop2   2  -2
DitherLoop2   2  -1
DitherLoop2   2   0
DitherLoop2   2   1
DitherLoop2   2   2

#endif