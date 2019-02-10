/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svConRecordListWriter.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

ConRecordListWriter::ConRecordListWriter()
{
   reset();
}

ConRecordListWriter::ConRecordListWriter(ConParms* aParms)
{
   mP = aParms;
   reset();
}

void ConRecordListWriter::initialize(ConParms* aParms)
{
   mP = aParms;
   reset();
}

void ConRecordListWriter::reset()
{
   mNumPixels = 0;
   mXM1.reset();
   mX0.reset();
   mXP1.reset();
   mXV.reset();
   mXA.reset();

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write to a pixel record list.

void ConRecordListWriter::doWriteRecordList(
   RCIndexList&              aIndexList,           // Input
   ConRecordList&            aRecordList)          // Output
{
   Prn::print(Prn::View11, "**************************************Contour %d", aIndexList.size());

   // Clear the output.
   aRecordList.clear();

   // Loop for each pixel in the contour.
   mNumPixels = (int)aIndexList.size();
   int jM1 = 0;  // Previous pixel array index.
   int jP1 = 0;  // Next pixel array index.
   for (int j = 0; j < aIndexList.size(); j++)
   {
      // First pixel indices.
      if (j == 0)
      {
         jM1 = mNumPixels - 1;       // Previous pixel array index.
         jP1 = j + 1;                // Next pixel array index. 
      }
      // Last pixel indices.
      else if (j == mNumPixels - 1)
      {
         jM1 = j - 1;                // Previous pixel array index. 
         jP1 = 0;                    // Next pixel array index.
      }
      // Otherwise pixel indices.
      else
      {
         jM1 = j - 1;                // Previous pixel array index.
         jP1 = j + 1;                // Next pixel array index.
      }
      // Extract the previous, current, and next pixels.
      mXM1 = aIndexList[jM1];   // Previous pixel.
      mX0  = aIndexList[j];     // Current pixel.  
      mXP1 = aIndexList[jP1];   // Nexy pixel.

      // Filter the current pixel.
      doFilterContourPixel(j);

      // Transfer the results to the record list.
      ConRecord tRecord;
      tRecord.mValidFlag = true;
      tRecord.mK = j;
      tRecord.mXX = mX0;
      tRecord.mXV = mXV;
      tRecord.mXA = mXA;
      aRecordList.push_back(tRecord);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter an image pixel that is contained in a contour.

void ConRecordListWriter::doFilterContourPixel(int aN)
{
   mXV.mRow = mXP1.mRow - mXM1.mRow;
   mXV.mCol = mXP1.mCol - mXM1.mCol;

   mXA.mRow = mXP1.mRow + mXM1.mRow - 2 * mX0.mRow;
   mXA.mCol = mXP1.mCol + mXM1.mCol - 2 * mX0.mCol;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace