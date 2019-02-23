//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svSimMorphParms.h"

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

SimMorphParms::SimMorphParms()
{
   reset();
}

void SimMorphParms::reset()
{
   mValid = false;
   mName[0] = 0;
   mImageSize = gSysParms.mImageSize;
   mRepeatNum = 0;
   mMorphNum = 0;
   mWriteNum = 0;
   mMode = 0;
   mDelta.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SimMorphParms::show(const char* aLabel)
{
   if (!mValid) return;
   printf("SimMorphParms******************* %s\n",aLabel);
   printf("Name                     %10s\n", mName);
   printf("ImageSize                %10d %10d\n", mImageSize.mRows, mImageSize.mCols);
   printf("RepeatNum                %10d\n", mRepeatNum);
   printf("MorphNum                 %10d\n", mMorphNum);
   printf("WriteNum                 %10d\n", mWriteNum);
   printf("Mode                     %10d\n", mMode);
   printf("Delta                    %10d %10d\n", mDelta.mRows, mDelta.mCols);
   printf("SimMorphParms*******************\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void SimMorphParms::execute(Ris::CmdLineCmd* aCmd)
{
   mValid = true;
   if (aCmd->isCmd("ImageSize"))      mImageSize.execute(aCmd);
   if (aCmd->isCmd("RepeatNum"))      mRepeatNum = aCmd->argInt(1);
   if (aCmd->isCmd("MorphNum"))       mMorphNum = aCmd->argInt(1);
   if (aCmd->isCmd("WriteNum"))       mWriteNum = aCmd->argInt(1);
   if (aCmd->isCmd("Mode"))           mMode = aCmd->argInt(1);
   if (aCmd->isCmd("Delta"))          mDelta.execute(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

void SimMorphParms::expand()
{
   mValid = mRepeatNum != 0;
}

void SimMorphParms::setName(const char* aName)
{
   strncpy(mName,aName,cMaxStringSize);
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace