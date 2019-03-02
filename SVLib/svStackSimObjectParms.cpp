//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svStackSimObjectParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

StackSimObjectParms::StackSimObjectParms()
{
   reset();
}

void StackSimObjectParms::reset()
{
   mValid = false;

   mMorphParmsA.reset();
   mMorphParmsB.reset();
   mMorphParmsC.reset();
   mMorphParmsD.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void StackSimObjectParms::expand()
{
   mMorphParmsA.expand();
   mMorphParmsB.expand();
   mMorphParmsC.expand();
   mMorphParmsD.expand();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void StackSimObjectParms::show()
{
   printf("\n");
   printf("StackSimObjectParms************************************************ %s\n", mTargetSection);

   mMorphParmsA.show("MorphA");
   mMorphParmsB.show("MorphB");
   mMorphParmsC.show("MorphC");
   mMorphParmsD.show("MorphD");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void StackSimObjectParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("StackMorphParmsA"))
   {
      readSection(aCmd->argString(1), &mMorphParmsA);
      mMorphParmsA.setName(aCmd->argString(1));
   }

   if (aCmd->isCmd("StackMorphParmsB"))
   {
      readSection(aCmd->argString(1), &mMorphParmsB);
      mMorphParmsB.setName(aCmd->argString(1));
   }

   if (aCmd->isCmd("StackMorphParmsC"))
   {
      readSection(aCmd->argString(1), &mMorphParmsC);
      mMorphParmsC.setName(aCmd->argString(1));
   }

   if (aCmd->isCmd("StackMorphParmsD"))
   {
      readSection(aCmd->argString(1), &mMorphParmsD);
      mMorphParmsD.setName(aCmd->argString(1));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace