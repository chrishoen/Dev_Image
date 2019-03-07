//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"

#define  _SVTESTPARMS_CPP_
#include "svTestParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

TestParms::TestParms()
{
   reset();
}

void TestParms::reset()
{
   BaseClass::reset();
   BaseClass::setFileName_RelAlphaFiles("Image/SV_Test_Parms.txt");

   mTileParms.reset();

   mCorner.reset();;
   mCenter.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void TestParms::expand()
{
   mTileParms.expand();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void TestParms::show()
{
   printf("\n");
   printf("TestParms************************************************ %s\n", mTargetSection);

   mTileParms.show("Tile");

   printf("\n");
   printf("Corner                   %10d %4d\n", mCorner.mRow, mCorner.mCol);
   printf("Center                   %10d %4d\n", mCenter.mRow, mCenter.mCol);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void TestParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("TileParms"))            readSection(aCmd->argString(1), &mTileParms);

   if (aCmd->isCmd("Corner"))               mCorner.execute(aCmd);
   if (aCmd->isCmd("Center"))               mCenter.execute(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace