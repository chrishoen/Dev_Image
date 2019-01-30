//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#define  _SVSIMULATIONPARMS_CPP_
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

   mImageFileName1[0] = 0;
   mImageFileName2[0] = 0;

   mNoiseSigma = 0.0;

   mImageGenParms.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void SimParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SimParms::show()
{
   printf("\n");
   printf("SimParms****************************************** %s\n", mTargetSection);

   printf("\n");
   printf("CenterPixel            %10d %10d\n", mCenterPixel.mRow, mCenterPixel.mCol);

   printf("\n");
   printf("ImageFileName1         %-10s\n", mImageFileName1);
   printf("ImageFileName2         %-10s\n", mImageFileName2);

   printf("\n");
   printf("NoiseSigma             %10.2f\n", mNoiseSigma);

   printf("\n");
   mImageGenParms.show();
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

   if (aCmd->isCmd("CenterPixel"))         mCenterPixel.execute(aCmd);
   if (aCmd->isCmd("ImageFileName1"))      aCmd->copyArgString(1, mImageFileName1, cMaxStringSize);
   if (aCmd->isCmd("ImageFileName2"))      aCmd->copyArgString(1, mImageFileName2, cMaxStringSize);

   if (aCmd->isCmd("NoiseSigma"))          mNoiseSigma = aCmd->argDouble(1);

   if (aCmd->isCmd("ImageGenParms"))       readSection(aCmd->argString(1), &mImageGenParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace