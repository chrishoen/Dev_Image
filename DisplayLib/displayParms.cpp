//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"

#define  _DISPLAYPARMS_CPP_
#include "displayParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Display
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

Parms::Parms()
{
   reset();
}

void Parms::reset()
{
   BaseClass::reset();
   BaseClass::setFileName_RelAlphaFiles("Image/Display_Parms.txt");

   mDisplayEnable = false;
   mDisplayNum = 0;

   mWindowWidth = 0;
   mWindowHeight = 0;

   mForeColor[0] = 0;
   mForeColor[1] = 0;
   mForeColor[2] = 0;
   mForeColor[3] = 0;

   mBackColor[0] = 0;
   mBackColor[1] = 0;
   mBackColor[2] = 0;
   mBackColor[3] = 0;

   mSideX = 0;
   mSideY = 0;
   mShowCode = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void Parms::show()
{
   char tBuffer[40];
   printf("\n");
   printf("DisplayParms******************************************** %s\n", mTargetSection);

   printf("DisplayEnable            %10s\n", my_string_from_bool(mDisplayEnable));
   printf("DisplayNum               %10d\n", mDisplayNum);
   printf("WindowWidthHeight        %10d %10d\n", mWindowWidth, mWindowHeight);
   return;

   printf("ForeColor             %-4d %4d %4d %4d\n", mForeColor[0], mForeColor[1], mForeColor[2], mForeColor[3]);
   printf("BackColor             %-4d %4d %4d %4d\n", mBackColor[0], mBackColor[1], mBackColor[2], mBackColor[3]);
   printf("SideX                 %-4d\n", mSideX);
   printf("sideY                 %-4d\n", mSideY);
   printf("PrintLevel            %-10s\n", mPrintLevel.asString(tBuffer));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void Parms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("DisplayEnable")) mDisplayEnable = aCmd->argBool(1);
   if (aCmd->isCmd("DisplayNum"))    mDisplayNum = aCmd->argInt(1);

   if (aCmd->isCmd("WindowWidthHeight"))
   {
      mWindowWidth = aCmd->argInt(1);
      mWindowHeight = aCmd->argInt(2);
   }

   if (aCmd->isCmd("ForeColor"))
   {
      mForeColor[0] = aCmd->argInt(1);
      mForeColor[1] = aCmd->argInt(2);
      mForeColor[2] = aCmd->argInt(3);
      mForeColor[3] = aCmd->argInt(4);
   }

   if (aCmd->isCmd("BackColor"))
   {
      mBackColor[0] = aCmd->argInt(1);
      mBackColor[1] = aCmd->argInt(2);
      mBackColor[2] = aCmd->argInt(3);
      mBackColor[3] = aCmd->argInt(4);
   }

   if (aCmd->isCmd("SideX"))        mSideX = aCmd->argInt(1);
   if (aCmd->isCmd("SideY"))        mSideY = aCmd->argInt(1);

   if (aCmd->isCmd("ShowCode"))     mShowCode = aCmd->argInt(1);
   if (aCmd->isCmd("PrintLevel"))          mPrintLevel.readArgs(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void Parms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace