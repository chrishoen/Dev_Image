//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svMorphParms.h"

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

MorphParms::MorphParms()
{
   reset();
}

void MorphParms::reset()
{
   mValid = false;
   mName[0] = 0;
   mImageSize = gSysParms.mImageSize;
   mGenerateFirst = false;
   mWriteFirst = false;

   mRepeatNum = 0;
   mMorphNum = 0;
   mWriteNum = 0;
   mMode = 0;
   mAddFlag = false;
   mDelta.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void MorphParms::show(const char* aLabel)
{
   if (!mValid) return;
   printf("MorphParms******************* %s\n",aLabel);
   printf("Name                     %10s\n", mName);
   printf("ImageSize                %10d %10d\n", mImageSize.mRows, mImageSize.mCols);
   printf("GenerateFirst            %10s\n", my_string_from_bool(mGenerateFirst));
   printf("WriteFirst               %10s\n", my_string_from_bool(mWriteFirst));
   printf("RepeatNum                %10d\n", mRepeatNum);
   printf("MorphNum                 %10d\n", mMorphNum);
   printf("WriteNum                 %10d\n", mWriteNum);
   printf("Mode                     %10s\n", asStringMode(mMode));
   printf("AddFlag                  %10s\n", my_string_from_bool(mAddFlag));
   printf("Delta                    %10d %10d\n", mDelta.mRows, mDelta.mCols);
   printf("MorphParms*******************\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void MorphParms::execute(Ris::CmdLineCmd* aCmd)
{
   mValid = true;
   if (aCmd->isCmd("ImageSize"))      mImageSize.execute(aCmd);
   if (aCmd->isCmd("GenerateFirst"))  mGenerateFirst = aCmd->argBool(1);
   if (aCmd->isCmd("WriteFirst"))     mWriteFirst = aCmd->argBool(1);
   if (aCmd->isCmd("RepeatNum"))      mRepeatNum = aCmd->argInt(1);
   if (aCmd->isCmd("MorphNum"))       mMorphNum = aCmd->argInt(1);
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

void MorphParms::expand()
{
   mValid = mRepeatNum != 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

void MorphParms::setName(const char* aName)
{
   strncpy(mName, aName, cMaxStringSize);
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

char* MorphParms::asStringMode(int aX)
{
   switch (aX)
   {
   case cNone: return "None";
   case cModeSquare: return "Square";
   case cModeDiamond: return "Diamond";
   default: return "UNKNOWN";
   }
}

char* MorphParms::asStringMode()
{
   return asStringMode(mMode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace