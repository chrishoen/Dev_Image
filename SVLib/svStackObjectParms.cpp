//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svStackObjectParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

StackObjectParms::StackObjectParms()
{
   reset();
}

void StackObjectParms::reset()
{
   mValid = false;

   mTileParmsA.reset();
   mTileParmsB.reset();
   mTileParmsC.reset();
   mTileParmsD.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void StackObjectParms::expand()
{
   mTileParmsA.expand();
   mTileParmsB.expand();
   mTileParmsC.expand();
   mTileParmsD.expand();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void StackObjectParms::show()
{
   printf("\n");
   printf("StackObjectParms************************************************ %s\n", mTargetSection);

   mTileParmsA.show("TileA");
   mTileParmsB.show("TileB");
   mTileParmsC.show("TileC");
   mTileParmsD.show("TileD");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void StackObjectParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("StackTileParmsA"))
   {
      readSection(aCmd->argString(1), &mTileParmsA);
      mTileParmsA.setName(aCmd->argString(1));
   }

   if (aCmd->isCmd("StackTileParmsB"))
   {
      readSection(aCmd->argString(1), &mTileParmsB);
      mTileParmsB.setName(aCmd->argString(1));
   }

   if (aCmd->isCmd("StackTileParmsC"))
   {
      readSection(aCmd->argString(1), &mTileParmsC);
      mTileParmsC.setName(aCmd->argString(1));
   }

   if (aCmd->isCmd("StackTileParmsD"))
   {
      readSection(aCmd->argString(1), &mTileParmsD);
      mTileParmsD.setName(aCmd->argString(1));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace