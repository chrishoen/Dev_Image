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
#include "svRCRect.h"

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
   short int mRowA;
   short int mRowB;
   short int mRow;
   short int mColA;
   short int mColB;
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
      mRowA = 0;
      mRowB = 0;
      mRow  = 0;
      mColA = 0;
      mColB = 0;
      mCol  = 0;
      mRows = 0;
      mCols = 0;
   }

   // Constructor.
   RCIndexLoop(int aRows, int aCols)
   {
      mFirst = true;
      mRowForward = true;
      mColForward = true;
      mRowA = 0;
      mRowB = 0;
      mRow = 0;
      mColA = 0;
      mColB = 0;
      mCol = 0;
      mRows = aRows;
      mCols = aCols;
   }

   // Constructor.
   RCIndexLoop(RCIndex aOffset,int aRows, int aCols)
   {
      mFirst = true;
      mRowForward = true;
      mColForward = true;
      mRowA = 0;
      mRowB = aOffset.mRow;
      mRow = aOffset.mRow;
      mColA = 0;
      mColB = aOffset.mCol;
      mCol = aOffset.mCol;
      mRows = aRows;
      mCols = aCols;
   }

   // Constructor.
   RCIndexLoop(RCSize aSize)
   {
      mFirst = true;
      mRowForward = true;
      mColForward = true;
      mRowA = 0;
      mRowB = 0;
      mRow = 0;
      mColA = 0;
      mColB = 0;
      mCol = 0;
      mRows = aSize.mRows;
      mCols = aSize.mCols;
   }

   // Constructor.
   RCIndexLoop(RCIndex aOffset, RCSize aSize)
   {
      mFirst = true;
      mRowForward = true;
      mColForward = true;
      mRowA = 0;
      mRowB = aOffset.mRow;
      mRow = aOffset.mRow;
      mColA = 0;
      mColB = aOffset.mCol;
      mCol = aOffset.mCol;
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
         mRowA = 0;
      }
      else
      {
         mRowA = mRows - 1;
      }
      mRow = mRowA + mRowB;
   }

   void firstCol()
   {
      if (mColForward)
      {
         mColA = 0;
      }
      else
      {
         mColA = mCols - 1;
      }
      mCol = mColA + mColB;
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
         return (mRowA < mRows);
      }
      else
      {
         return (mRowA >= 0);
      }
   }

   bool testCol()
   {
      if (mColForward)
      {
         return (mColA < mCols);
      }
      else
      {
         return (mColA >= 0);
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
         mRowA++;
      }
      else
      {
         mRowA--;
      }
      mRow = mRowA + mRowB;
   }

   void nextCol()
   {
      if (mColForward)
      {
         mColA++;
      }
      else
      {
         mColA--;
      }
      mCol = mColA + mColB;
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
      if (++mColA == mCols)
      {
         mColA = 0;
         if (++mRowA == mRows)
         {
            mRow = mRowA + mRowB;
            mCol = mColA + mColB;
            return false;
         }
      }
      mRow = mRowA + mRowB;
      mCol = mColA + mColB;
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
   short int mLoop;
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
   RCDitherLoop1()
   {
      mFirst = true;
      mLoop = 0;
      mDelta = 0;
      mRowA = 0;
      mColA = 0;
      mRowC = 0;
      mColC = 0;
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;
   }

   // Constructor.
   RCDitherLoop1(int aLoop, int aDelta)
   {
      mFirst = true;
      mLoop = aLoop;
      mDelta = aDelta;
      mRowA = -aLoop * aDelta;
      mColA = -aLoop * aDelta;
      mRowC = 0;
      mColC = 0;
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;
   }

   // Constructor.
   RCDitherLoop1(RCIndex aCenter,int aLoop, int aDelta)
   {
      mFirst = true;
      mLoop = aLoop;
      mDelta = aDelta;
      mRowA = -aLoop * aDelta;
      mColA = -aLoop * aDelta;
      mRowC = aCenter.mRow;
      mColC = aCenter.mCol;
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;
   }

   // Constructor.
   void set(int aLoop, int aDelta)
   {
      mFirst = true;
      mLoop = aLoop;
      mDelta = aDelta;
      mRowA = -aLoop * aDelta;
      mColA = -aLoop * aDelta;
      mRowC = 0;
      mColC = 0;
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;
   }

   // Constructor.
   void set(RCIndex aCenter, int aLoop, int aDelta)
   {
      mFirst = true;
      mLoop = aLoop;
      mDelta = aDelta;
      mRowA = -aLoop * aDelta;
      mColA = -aLoop * aDelta;
      mRowC = aCenter.mRow;
      mColC = aCenter.mCol;
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;
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
      if (mColA != mLoop * mDelta)
      {
         mColA += mDelta;
      }
      else
      {
         mColA = -mLoop * mDelta;
         mRowA += mDelta;
      }
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;

      return mRowA <= mLoop * mDelta;
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
      mRowA = -mLoop * mDelta;
      mColA = -mLoop * mDelta;
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;
   }

   void firstRow()
   {
      mRowA = -mLoop * mDelta;
      mRow = mRowA + mRowC;
   }

   void firstCol()
   {
      mColA = -mLoop * mDelta;
      mCol = mColA + mColC;
   }

   void centerRow()
   {
      mRowA = 0;
      mRow = mRowA + mRowC;
   }

   void centerCol()
   {
      mColA = 0;
      mCol = mColA + mColC;
   }

   bool test()
   {
      return mRowA <= mLoop * mDelta;
   }

   bool testRow()
   {
      return mRowA <= mLoop * mDelta;
   }

   bool testCol()
   {
      return mColA <= mLoop * mDelta;
   }

   void next()
   {
      if (mColA != mLoop * mDelta)
      {
         mColA += mDelta;
      }
      else
      {
         mColA = -mLoop * mDelta;
         mRowA += mDelta;
      }
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;
   }

   void nextRow()
   {
      mRowA += mDelta;
      mRow = mRowA + mRowC;
   }

   void nextCol()
   {
      mColA += mDelta;
      mCol = mColA + mColC;
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

class RCDitherLoop2
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   bool mFirst;
   short int mRowLoop;
   short int mColLoop;
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
   RCDitherLoop2(RCIndex aCenter, int aRowLoop, int aColLoop)
   {
      mFirst = true;
      mRowLoop = aRowLoop;
      mColLoop = aColLoop;
      mRowA = -aRowLoop;
      mColA = -aColLoop;
      mRowC = aCenter.mRow;
      mColC = aCenter.mCol;
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;
   }

   // Constructor.
   void set(RCIndex aCenter, int aRowLoop, int aColLoop)
   {
      mFirst = true;
      mRowLoop = aRowLoop;
      mColLoop = aColLoop;
      mRowA = -aRowLoop;
      mColA = -aColLoop;
      mRowC = aCenter.mRow;
      mColC = aCenter.mCol;
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;
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
      if (mColA != mColLoop)
      {
         mColA++;
      }
      else
      {
         mColA = -mColLoop;
         mRowA++;
      }
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;

      return mRowA <= mRowLoop;
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
      mRowA = -mRowLoop;
      mColA = -mColLoop;
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;
   }

   void firstRow()
   {
      mRowA = -mRowLoop;
      mRow = mRowA + mRowC;
   }

   void firstCol()
   {
      mColA = -mColLoop;
      mCol = mColA + mColC;
   }

   void centerRow()
   {
      mRowA = 0;
      mRow = mRowA + mRowC;
   }

   void centerCol()
   {
      mColA = 0;
      mCol = mColA + mColC;
   }

   bool test()
   {
      return mRowA <= mRowLoop;
   }

   bool testRow()
   {
      return mRowA <= mRowLoop;
   }

   bool testCol()
   {
      return mColA <= mColLoop;
   }

   void next()
   {
      if (mColA != mColLoop)
      {
         mColA++;
      }
      else
      {
         mColA = -mColLoop;
         mRowA++;
      }
      mRow = mRowA + mRowC;
      mCol = mColA + mColC;
   }

   void nextRow()
   {
      mRowA++;
      mRow = mRowA + mRowC;
   }

   void nextCol()
   {
      mColA++;
      mCol = mColA + mColC;
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
   RCCircuitLoop(int aDelta)
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
   RCCircuitLoop(RCIndex aCenter, int aDelta)
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
// This class encapsulates an index loop iterator. It provides the
// functionality to construct for loops with array indices.

class RCRectLoop
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   bool mFirst;
   bool mRowForward;
   bool mColForward;
   short int mRowA;
   short int mRowB;
   short int mRow;
   short int mColA;
   short int mColB;
   short int mCol;
   short int mRows;
   short int mCols;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   RCRectLoop()
   {
      mFirst = true;
      mRowForward = true;
      mColForward = true;
      mRowA = 0;
      mRowB = 0;
      mRow = 0;
      mColA = 0;
      mColB = 0;
      mCol = 0;
   }

   // Constructor.
   RCRectLoop(RCRect aRect)
   {
      mFirst = true;
      mRowForward = true;
      mColForward = true;
      mRowA = aRect.mARow;
      mRowB = aRect.mBRow;
      mRow = 0;
      mColA = aRect.mACol;
      mColB = aRect.mBCol;
      mCol = 0;
   }

   // Constructor.

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
         mRow = mRowA;
      }
      else
      {
         mRow = mRowB;
      }
   }

   void firstCol()
   {
      if (mColForward)
      {
         mCol = mColA;
      }
      else
      {
         mColA = mColB;
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
         return (mRow <= mRowB);
      }
      else
      {
         return (mRow >= mRowA);
      }
   }

   bool testCol()
   {
      if (mColForward)
      {
         return (mCol <= mColB);
      }
      else
      {
         return (mCol >= mColA);
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
      if (++mCol > mColB)
      {
         mCol = mColA;
         if (++mRow > mRowB)
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
         mRow = mRowA;
         mCol = mColA;
         mFirst = false;
         return true;
      }

      return advance();
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