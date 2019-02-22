//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#define  _SVSIMPARMS_CPP_
#include "svSimParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

SimParms::SimParms()
{
   reset();
}

void SimParms::reset()
{
   BaseClass::reset();
   BaseClass::setFileName_RelAlphaFiles("Image/SV_Sim_Parms.txt");

   mImageGenParmsS1.reset();
   mImageGenParmsS2.reset();
   mImageGenParmsS3.reset();

   mStackName[0] = 0;
   mStackSize = 0;
   mStackMorphParms.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void SimParms::expand()
{
   mImageGenParmsS1.expand();
   mImageGenParmsS2.expand();
   mImageGenParmsS3.expand();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SimParms::show()
{
   printf("\n");
   printf("SimParms************************************************ %s\n", mTargetSection);

   if (mStackSize == 0)
   {
      mImageGenParmsS1.show("D");
      mImageGenParmsS2.show("C");
      mImageGenParmsS3.show("U");
   }
   else
   {
      printf("StackName                         %s\n", mStackName);
      printf("StackSize                         %10d\n", mStackSize);
      mStackMorphParms.show("Stack");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void SimParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("ImageGenParmsS1"))      readSection(aCmd->argString(1), &mImageGenParmsS1);
   if (aCmd->isCmd("ImageGenParmsS2"))      readSection(aCmd->argString(1), &mImageGenParmsS2);
   if (aCmd->isCmd("ImageGenParmsS3"))      readSection(aCmd->argString(1), &mImageGenParmsS3);

   if (aCmd->isCmd("StackName"))           aCmd->copyArgString(1, mStackName, cMaxStringSize);
   if (aCmd->isCmd("StackSize"))           mStackSize = aCmd->argInt(1);

   if (aCmd->isCmd("StackMorphParms"))     readSection(aCmd->argString(1), &mStackMorphParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace