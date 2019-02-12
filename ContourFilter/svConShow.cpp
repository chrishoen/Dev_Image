/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svRCLoop.h"
#include "svImageParms.h"

#include "svConShow.h"

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
   ConRecordList&   aList)         // Input
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
   int              aCode,         // Input
   const char*      aLabel,        // Input
   ConRecordArray&  aArray)        // Input
{
   // Guard.
   if (aArray.mRows == 0)return;

   // Region of interest variables.
   RCIndex tCenterPixel = gImageParms.mRoiPixel;
   int tB = gImageParms.mRoiB;

   printf("\n");
   printf("********************************************* %-12s %4d %4d $ %4d %4d\n",
      aLabel, aArray.mRows, aArray.mCols,
      tCenterPixel.mRow, tCenterPixel.mRow);
   printf("\n");

   SV::RCDitherLoop1 tLoop(tCenterPixel, tB, 1);

   // Print header.
   printf("     $ ");
   for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
   {
      printf(" %8d", tLoop.mCol);
   }
   printf("\n");
   printf("     $\n");

   // Loop through all of the rows and columns of the pulse.
   for (tLoop.firstRow(); tLoop.testRow(); tLoop.nextRow())
   {
      if (true)
      {
         printf("%4d V ", tLoop().mRow);
         for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
         {
            ConRecord tRecord = aArray.at(tLoop());
            if (tRecord.mValidFlag)
            {
               printf(" %1d%1d", abs(tRecord.mXV.mRow), abs(tRecord.mXV.mCol));
            }
            else
            {
               printf("        .");
            }
         }
         printf("\n");
      }
      if (aCode == 2)
      {
         printf("     A ");
         for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
         {
            ConRecord tRecord = aArray.at(tLoop());
            if (tRecord.mValidFlag)
            {
               printf("   : %2d%2d", tRecord.mXA.mRow, tRecord.mXA.mCol);
            }
            else
            {
               printf("        .");
            }
         }
         printf("\n");
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show image in tabular form.

void showRecordArray2(
   const char*      aLabel,        // Input
   ConRecordArray&  aArray)        // Input
{
   // Guard.
   if (aArray.mRows == 0)return;

   // Region of interest variables.
   RCIndex tCenterPixel = gImageParms.mRoiPixel;
   int tB = gImageParms.mRoiB;

   printf("\n");
   printf("********************************************* %-12s %4d %4d $ %4d %4d\n",
      aLabel, aArray.mRows, aArray.mCols,
      tCenterPixel.mRow, tCenterPixel.mRow);
   printf("\n");

   SV::RCDitherLoop1 tLoop(tCenterPixel, tB, 1);

   // Print header.
   printf("     $ ");
   for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
   {
      printf("  %1d", (tLoop.mCol / 100) % 10);
   }
   printf("\n");

   printf("     $ ");
   for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
   {
      printf("  %1d", (tLoop.mCol / 10) % 10);
   }
   printf("\n");

   printf("     $ ");
   for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
   {
      printf("  %1d", tLoop.mCol % 10);
   }
   printf("\n");


   printf("     $\n");

   // Loop through all of the rows and columns of the pulse.
   for (tLoop.firstRow(); tLoop.testRow(); tLoop.nextRow())
   {
      printf("%4d $ ", tLoop().mRow);
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         ConRecord tRecord = aArray.at(tLoop());
         if (tRecord.mValidFlag)
         {
            printf(" %1d%1d", abs(tRecord.mXV.mRow), abs(tRecord.mXV.mCol));
         }
         else
         {
            printf("  .");
         }
      }
      printf("\n");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
