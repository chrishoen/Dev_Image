#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Row and column index.
Row and column loop index.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineCmd.h"

#include "svRCSize.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates an index pair. It contains row and column integer
// members.
//

class RCIndex
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   // Matrix row and column index pair.
   short int mRow;
   short int mCol;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   RCIndex();
   RCIndex(int aRow,int aCol);
   void RCIndex::reset();
   void RCIndex::set(int aRow,int aCol);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Show.
   void show(int aPrintFilter, char* aLabel);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Operators:

   // Equality.
   bool operator==(RCIndex& aRight)const;

   // Inequality.
   bool operator!=(RCIndex& aRight)const;

   // Increment.
   void operator+=(RCIndex& aRight);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Execute to read variables from a command line command. 
   void execute(Ris::CmdLineCmd* aCmd);
};

// Addition and subtraction operators.
RCIndex operator+(RCIndex aLeft, RCIndex aRight);
RCIndex operator-(RCIndex aLeft, RCIndex aRight);

//******************************************************************************
//******************************************************************************
//******************************************************************************
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
   RCIndexLoop();
   RCIndexLoop(int aRows,int aCols);
   RCIndexLoop(RCSize aSize);

   // Return the current row and column.
   RCIndex operator()();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Advance the loop. Return true if the loop is not finished.
   bool advance();
   bool loop();

   // These are used by for loops. See the examples at the end of the file.
   void first();
   void firstRow();
   void firstCol();

   bool test();
   bool testRow();
   bool testCol();

   void nextRow();
   void nextCol();
   void next();
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
   RCDitherLoop1(int aLoop,int aDelta);

   // Return the current row and column.
   RCIndex operator()();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Advance the loop. Return true if the loop is not finished.
   bool advance();
   bool loop();

   // These are used by for loops. See the examples at the end of the file.
   void first();
   bool test();
   void next();
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
   RCDitherLoop2(int aLoop,int aDelta);

   // Return the current row and column.
   RCIndex operator()();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Advance the loop. Return true if the loop is not finished.
   bool advance();
   bool loop();

   // These are used by for loops. See the examples at the end of the file.
   void first();
   bool test();
   void next();
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
   RCCircuitLoop(int aDelta);
   RCCircuitLoop(RCIndex aCenter,int aDelta);

   // Return the current row and column.
   RCIndex operator()();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Advance the loop. Return true if the loop is not finished.
   bool advance();
   bool loop();

   // These are used by for loops. See the examples at the end of the file.
   void first();
   bool test();
   void next();
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