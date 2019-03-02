#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Two dimensional array rectangle.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineCmd.h"

#include "svRCIndex.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a two dimensional array rectangle. It is used to
// define regions within an array. See the description at the bottom of this
// file.
//

class RCRect
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   // RCRectangle row range and column ranges.
   int mARow;
   int mBRow;
   int mACol;
   int mBCol;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Constructor.
   RCRect();
   void reset();
   RCRect         (int aARow,int aBRow,int aACol,int aBCol);
   void initialize(int aARow,int aBRow,int aACol,int aBCol);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Split this rectangle into two halfs, one left and one left.
   // Return true if the split actually ocurred, that the input 
   // width was not equal to one.
   bool splitLeftRight(
      RCRect& aLeft,       // Output
      RCRect& aRight);     // Output

   // Split this rectangle into two halfs, one upper and one lower.
   // Return true if the split actually ocurred, that the input 
   // height was not equal to one.
   bool splitUpperLower(
      RCRect& aUpper,      // Output
      RCRect& aLower);     // Output

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // return height and width.
   int height()  { return mBRow - mARow; }
   int width()   { return mBCol - mACol; }
   int isCell()  { return height()==1 && width()==1; }
   int isEmpty() { return height()==0 || width()==0; }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Show.
   void show (int aPrintFilter,char* aLabel);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Return the intersection of two rectangles.
   RCRect operator&(RCRect aRight);

   // Set this rectangle to the intersection of itself and another rectangle.
   RCRect operator&=(RCRect aRight);

   // Return this rectangle plus an offset.
   RCRect operator+(RCIndex aRight);

   // Add an offset to this rectangle.
   RCRect operator+=(RCIndex aRight);

   // Equality.
   bool operator==(RCRect& rhs)const;

   // Inequality.
   bool operator!=(RCRect& rhs)const;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // Return true if the rectangle contains the index,
   bool contains(RCIndex aIndex);

   // Shrink/expand by a delta.
   void shrink(int aDelta);
   void expand(int aDelta);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Execute to read variables from a command line command. 
   void execute(Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

#if 0

The rectangle is defined by a row range A..B [upper to lower] and
a column range A..B [left to right]. So the rectangle is defined
by four indices ARow,BRow and ACol,BCol. These are closed intervals.

         mARow                            mBRow
mACol P1 +------------------------------------+ P2
         +                                    +
         +                                    +
         +                                    +
         +                                    +
mBCol P3 +------------------------------------+ P4
                                    mBRow,mBCol


         mARow,mACol                mARow,mBCol
      P1 +------------------------------------+ P2
         +                                    +
         +                                    +
         +                                    +
         +                                    +
      P3 +------------------------------------+ P4
         mBRow,mACol                mBRow,mBCol

   The indices represent closed intervals:

   Row = 0..2, Col = 0..3
   +-----+-----+-----+-----+
   + 0,0 + 0,1 + 0,2 + 0,3 +
   +-----+-----+-----+-----+
   + 1,0 + 1,1 + 1,2 + 1,3 +
   +-----+-----+-----+-----+
   + 2,0 + 2,1 + 2,2 + 2,3 +
   +-----+-----+-----+-----+

   The single cell at 1,1 has rectangle 1 1 1 1

   The height is mBRow - mARow
   The width  is mBCol - mACol

   To loop from P1 to P2 use : for (int tCol = mACol; tCol <= mBCol; tCol++) {table(mARow,tCol)}
   To loop from P3 to P4 use : for (int tCol = mACol; tCol <= mBCol; tCol++) {table(mBRow,tCol)}

   To loop from P1 to P3 use : for (int tRow = mARow; tRow <= mBRow; tRow++) {table(tRow,mACol)}
   To loop from P2 to P4 use : for (int tRow = mARow; tRow <= mBRow; tRow++) {table(tRow,mBCol)}

   To loop from P1 to P2 use : for (int tCol = mACol; tCol <= mBCol; tCol++) {table(mARow,tCol)}
   To loop from P2 to P4 use : for (int tRow = mARow; tRow <= mBRow; tRow++) {table(tRow,mBCol)}
   To loop from P4 to P3 use : for (int tCol = mBCol; tCol >= mACol; tCol--) {table(mBRow,tCol)}
   To loop from P3 to P1 use : for (int tRow = mBRow; tRow >= mARow; tRow++) {table(tRow,mACol)}



   splitLeftRight
   0                        6  
 0 +------------------------+
   +                        +
   +                        +
   +                        +
   +                        +
   +                        +
 5 +------------------------+
   0..6,0..5

   0           3            6
 0 +-----------+------------+  
   +           +            +
   +           +            +
   +           +            +
   +           +            +
   +           +            +
 5 +-----------+------------+
   0..3,0..5   3..6,0..5 

   splitUpperLower
   0                        6  
 0 +------------------------+  0..6,0..5
   +                        +
   +                        +
   +                        +
   +                        +
   +                        +
 5 +------------------------+
   

   0                        6
 0 +------------------------+ 0..6,0..3
   +                        +
   +                        +
 3 +------------------------+ 0..6,3..5
   +                        +
   +                        +
 5 +------------------------+

#endif
