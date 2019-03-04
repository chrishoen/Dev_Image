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
   mImageSize = gSysParms.mImageSize;
   mGenerateFirst = false;
   mWriteFirst = false;

   mRepeatNum = 0;
   mTileNum = 0;
   mWriteNum = 0;
   mMode = 0;
   mAddFlag = false;
   mDelta.reset();
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
   printf("ImageSize                %10d %10d\n", mImageSize.mRows, mImageSize.mCols);
   printf("GenerateFirst            %10s\n", my_string_from_bool(mGenerateFirst));
   printf("WriteFirst               %10s\n", my_string_from_bool(mWriteFirst));
   printf("RepeatNum                %10d\n", mRepeatNum);
   printf("TileNum                 %10d\n", mTileNum);
   printf("WriteNum                 %10d\n", mWriteNum);
   printf("Mode                     %10s\n", asStringMode(mMode));
   printf("AddFlag                  %10s\n", my_string_from_bool(mAddFlag));
   printf("Delta                    %10d %10d\n", mDelta.mRows, mDelta.mCols);
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
   mValid = true;
   if (aCmd->isCmd("ImageSize"))      mImageSize.execute(aCmd);
   if (aCmd->isCmd("GenerateFirst"))  mGenerateFirst = aCmd->argBool(1);
   if (aCmd->isCmd("WriteFirst"))     mWriteFirst = aCmd->argBool(1);
   if (aCmd->isCmd("RepeatNum"))      mRepeatNum = aCmd->argInt(1);
   if (aCmd->isCmd("TileNum"))       mTileNum = aCmd->argInt(1);
   if (aCmd->isCmd("WriteNum"))       mWriteNum = aCmd->argInt(1);
   if (aCmd->isCmd("Mode"))           mMode = aCmd->argInt(1);
   if (aCmd->isCmd("AddFlag"))        mAddFlag = aCmd->argBool(1);
   if (aCmd->isCmd("Delta"))          mDelta.execute(aCmd);

   if (aCmd->isCmd("Mode"))
   {
      if (aCmd->isArgString(1, asStringMode(cNone)))             mMode = cNone;
      if (aCmd->isArgString(1, asStringMode(cModeSquare)))       mMode = cModeSquare;
      if (aCmd->isArgString(1, asStringMode(cModeDiamond)))      mMode = cModeDiamond;
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

void TileParms::expand()
{
   mValid = mRepeatNum != 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

void TileParms::setName(const char* aName)
{
   strncpy(mName, aName, cMaxStringSize);
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

char* TileParms::asStringMode(int aX)
{
   switch (aX)
   {
   case cNone: return "None";
   case cModeSquare: return "Square";
   case cModeDiamond: return "Diamond";
   default: return "UNKNOWN";
   }
}

char* TileParms::asStringMode()
{
   return asStringMode(mMode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace