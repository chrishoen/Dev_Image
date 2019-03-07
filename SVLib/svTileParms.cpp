//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svTileParms.h"

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
// Constructor.

TileParms::TileParms()
{
   reset();
}

void TileParms::reset()
{
   mValid = false;
   mName[0] = 0;

   mNumLoop = 0;
   mShape = 0;
   mNumLoop = 0;
   mNumRow = 0;
   mNumCol = 0;
   mStepH = 0;
   mStepV = 0;
   mB = 0;

   mCenter.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void TileParms::show(const char* aLabel)
{
   if (!mValid) return;

   printf("TileParms******************* %s\n",aLabel);
   printf("Name           %20s\n", mName);
   printf("Shape                    %10s\n", asStringShape(mShape));
   printf("NumLoop                  %10d\n", mNumLoop);
   printf("NumRow                   %10d\n", mNumRow);
   printf("NumCol                   %10d\n", mNumCol);
   printf("StepH                    %10d\n", mStepH);
   printf("StepV                    %10d\n", mStepV);
   printf("B                        %10d\n", mB);
   printf("Center                   %10d %10d\n", mCenter.mRow, mCenter.mCol);
   printf("TileParms*******************\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void TileParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("Shape"))          mShape = aCmd->argInt(1);
   if (aCmd->isCmd("NumLoop"))        mNumLoop = aCmd->argInt(1);
   if (aCmd->isCmd("NumRow"))         mNumRow = aCmd->argInt(1);
   if (aCmd->isCmd("NumCol"))         mNumCol = aCmd->argInt(1);
   if (aCmd->isCmd("StepH"))          mStepH = aCmd->argInt(1);
   if (aCmd->isCmd("StepV"))          mStepV = aCmd->argInt(1);
   if (aCmd->isCmd("Center"))         mCenter.execute(aCmd);

   if (aCmd->isCmd("Shape"))
   {
      if (aCmd->isArgString(1, asStringShape(cNone)))              mShape = cNone;
      if (aCmd->isArgString(1, asStringShape(cShapeSquare)))       mShape = cShapeSquare;
      if (aCmd->isArgString(1, asStringShape(cShapeDiamond)))      mShape = cShapeDiamond;
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

void TileParms::expand()
{
   mValid = mNumRow != 0 || mNumCol != 0;

   mCenter.mRow = gSysParms.mImageSize.mRows / 2;
   mCenter.mCol = gSysParms.mImageSize.mCols / 2;


   if (isSquare())
   {
      int tRowCount = mNumLoop * mNumRow;
      int tColCount = mNumLoop * mNumCol;
      mB = my_imax(tRowCount, tColCount);
   }
   else
   {
      int tRowCount = mNumLoop * mNumRow - mNumRow / 2;
      int tColCount = mNumLoop * mNumCol - mNumCol / 2;
      mB = my_imax(tRowCount, tColCount);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Adjust the loop number according to the stack index.

void TileParms::adjust(int aStackIndex)
{
   mNumLoop = mStepH * (aStackIndex / mStepV);

   if (isSquare())
   {
      int tRowCount = mNumLoop * mNumRow;
      int tColCount = mNumLoop * mNumCol;
      mB = my_imax(tRowCount, tColCount);
   }
   else
   {
      int tRowCount = mNumLoop * mNumRow - mNumRow / 2;
      int tColCount = mNumLoop * mNumCol - mNumCol / 2;
      mB = my_imax(tRowCount, tColCount);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a roi center as a function of the stack index.

RCIndex TileParms::getRoiCenter(int aStackIndex)
{
   int tNumLoop = mStepH * (aStackIndex / mStepV);
   int tRowCount = 0;
   int tColCount = 0;
   RCIndex tRoiCenter;

   if (isSquare())
   {
      tRowCount = tNumLoop * mNumRow;
      tColCount = tNumLoop * mNumCol;
      tRoiCenter = mCenter + RCIndex(-tRowCount, -tColCount);
   }
   else
   {
      tRowCount = tNumLoop * mNumRow - mNumRow / 2;
      tColCount = tNumLoop * mNumCol - mNumCol / 2;
      tRoiCenter = mCenter + RCIndex(-tRowCount,0);
   }

   return tRoiCenter;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

void TileParms::setName(const char* aName)
{
   strncpy(mName, aName, cMaxStringSize);
}

char* TileParms::asStringShape(int aX)
{
   switch (aX)
   {
   case cNone: return "None";
   case cShapeSquare: return "Square";
   case cShapeDiamond: return "Diamond";
   default: return "UNKNOWN";
   }
}

char* TileParms::asStringShape()
{
   return asStringShape(mShape);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace