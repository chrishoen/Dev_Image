/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svRCLoop.h"
#include "svImageParms.h"

#include "svContourShow.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show record list.

void showRecordList(
   int                  aPF,           // Input
   const char*          aLabel,        // Input
   ContourRecordList&   aList)         // Input
{
   Prn::print(aPF, "RecordList %-12s %4d", aLabel, aList.size());
   for (int i = 0; i < aList.size(); i++)
   {
      Prn::print(aPF, "Record %4d $ %4d %4d",
         i,
         aList[i].mXX.mRow,
         aList[i].mXX.mCol);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show record list.

void showRecordArray(
   const char*          aLabel,        // Input
   ContourRecordArray&  aArray)        // Input
{
   printf("RecordArray %-12s %4d %4d\n", aLabel, aArray.mRows, aArray.mCols);
   if (aArray.mRows == 0) return;

   // Region of interest variables.
   RCIndex tCenterPixel = gImageParms.mRoiPixel;
   int tB = gImageParms.mRoiB;

   SV::RCDitherLoop1 tLoop(tCenterPixel, tB, 1);
   for (tLoop.firstRow(); tLoop.testRow(); tLoop.nextRow())
   {
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         printf("$%4d %4d", tLoop.mRow, tLoop.mCol);
      }
      printf("\n");
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
