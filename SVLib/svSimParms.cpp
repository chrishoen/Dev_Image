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

   mPulsePixelWidth = 0;
   mPulseGaussianWidth = 0.0;
   mPulseAmplitude = 0.0;
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
   printf("Sigma                  %10.2f\n", mSigma);

   printf("\n");
   printf("PulsePixelWidth        %10d\n",   mPulsePixelWidth);
   printf("PulseGaussianWidth     %10.2f\n", mPulseGaussianWidth);
   printf("PulseAmplitude         %10.2f\n", mPulseAmplitude);
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

   if (aCmd->isCmd("Sigma"))           mSigma         = aCmd->argDouble(1);

   if (aCmd->isCmd("PulsePixelWidth"))     mPulsePixelWidth    = aCmd->argInt(1);
   if (aCmd->isCmd("PulseGaussianWidth"))  mPulseGaussianWidth = aCmd->argDouble(1);
   if (aCmd->isCmd("PulseAmplitude"))      mPulseAmplitude     = aCmd->argDouble(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace