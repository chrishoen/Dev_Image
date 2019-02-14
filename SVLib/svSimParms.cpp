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

   mNoiseSigma = 0.0;

   mImageGenParmsD.reset();
   mImageGenParmsC.reset();
   mImageGenParmsU.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void SimParms::expand()
{
   mImageGenParmsD.expand();
   mImageGenParmsC.expand();
   mImageGenParmsU.expand();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SimParms::show()
{
   printf("\n");
   printf("SimParms************************************************ %s\n", mTargetSection);
   mImageGenParmsD.show("D");
   mImageGenParmsC.show("C");
   mImageGenParmsU.show("U");
   return;
   printf("NoiseSigma             %10.2f\n", mNoiseSigma);
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

   if (aCmd->isCmd("NoiseSigma"))          mNoiseSigma = aCmd->argDouble(1);

   if (aCmd->isCmd("ImageGenParmsD"))      readSection(aCmd->argString(1), &mImageGenParmsD);
   if (aCmd->isCmd("ImageGenParmsC"))      readSection(aCmd->argString(1), &mImageGenParmsC);
   if (aCmd->isCmd("ImageGenParmsU"))      readSection(aCmd->argString(1), &mImageGenParmsU);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace