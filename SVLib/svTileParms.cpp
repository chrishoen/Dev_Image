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
   mRepeatNum = 0;
   mShape = 0;
   mDelta.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void TileParms::show(const char* aLabel)
{

   printf("TileParms******************* %s\n",aLabel);
   printf("Shape                    %10s\n", asStringShape(mShape));
   printf("RepeatNum                %10d\n", mRepeatNum);
   printf("Delta                    %10d %10d\n", mDelta.mRows, mDelta.mCols);
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
   if (aCmd->isCmd("RepeatNum"))      mRepeatNum = aCmd->argInt(1);
   if (aCmd->isCmd("Delta"))          mDelta.execute(aCmd);
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
   mCenter.mRow = gSysParms.mImageSize.mRows / 2;
   mCenter.mCol = gSysParms.mImageSize.mCols / 2;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

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