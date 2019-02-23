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
   mStackWriteFirst = false;
   mStackMorphParmsA.reset();
   mStackMorphParmsB.reset();
   mStackMorphParmsC.reset();
   mStackMorphParmsD.reset();
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

   mStackMorphParmsA.expand();
   mStackMorphParmsB.expand();
   mStackMorphParmsC.expand();
   mStackMorphParmsD.expand();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SimParms::show()
{
   printf("\n");
   printf("SimParms************************************************ %s\n", mTargetSection);

   bool tStackFlag = false;
   if (mStackMorphParmsA.mValid)
   {
      tStackFlag = true;
      printf("StackName                         %s\n", mStackName);
      printf("StackWriteFirst                   %s\n", my_string_from_bool(mStackWriteFirst));
      mStackMorphParmsA.show("MorphA");
   }
   if (mStackMorphParmsB.mValid)
   {
      tStackFlag = true;
      mStackMorphParmsB.show("MorphB");
   }
   if (mStackMorphParmsC.mValid)
   {
      tStackFlag = true;
      mStackMorphParmsC.show("MorphC");
   }
   if (mStackMorphParmsD.mValid)
   {
      tStackFlag = true;
      mStackMorphParmsD.show("MorphD");
   }

   if (!tStackFlag)
   {
      mImageGenParmsS1.show("S1");
      mImageGenParmsS2.show("S2");
      mImageGenParmsS3.show("S3");
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
   if (aCmd->isCmd("StackWriteFirst"))     mStackWriteFirst = aCmd->argBool(1);
   if (aCmd->isCmd("StackMorphParmsA"))    readSection(aCmd->argString(1), &mStackMorphParmsA);
   if (aCmd->isCmd("StackMorphParmsB"))    readSection(aCmd->argString(1), &mStackMorphParmsB);
   if (aCmd->isCmd("StackMorphParmsC"))    readSection(aCmd->argString(1), &mStackMorphParmsC);
   if (aCmd->isCmd("StackMorphParmsD"))    readSection(aCmd->argString(1), &mStackMorphParmsD);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace