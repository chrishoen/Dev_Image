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

   mFx = 0.0;
   mFy = 0.0;
   mCx = 0.0;
   mCy = 0.0;
   
   mUseGamma = false;
   mGamma = 0.0;
   mWD = 0.0;

   mSigma = 0.0;

   mNumTrialTests = 0;
   mTrialDeltaA = 0.0;
   mTrialDeltaT = 0.0;

   mSyntheticFlag = false;
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
   printf("Fx                     %10.6f\n", mFx);
   printf("Fy                     %10.6f\n", mFy);
   printf("Cx                     %10.6f\n", mCx);
   printf("Cy                     %10.6f\n", mCy);

   printf("\n");
   printf("UseGamma               %10s\n",   my_string_from_bool(mUseGamma));
   printf("Gamma                  %10.2f\n", deg(mGamma));
   printf("WD                     %10.2f\n", mWD);

   printf("\n");
   printf("NumTrialTests          %10d\n",   mNumTrialTests);
   printf("TrialDeltaA            %10.2f\n", deg(mTrialDeltaA));
   printf("TrialDeltaT            %10.2f\n", mTrialDeltaT);

   printf("\n");
   printf("Sigma                  %10.2f\n", mSigma);

   printf("\n");
   printf("SyntheticFlag          %10s\n",   my_string_from_bool(mSyntheticFlag));
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


   if (aCmd->isCmd("Fx"))               mFx  = aCmd->argDouble(1);
   if (aCmd->isCmd("Fy"))               mFy  = aCmd->argDouble(1);
   if (aCmd->isCmd("Cx"))               mCx  = aCmd->argDouble(1);
   if (aCmd->isCmd("Cy"))               mCy  = aCmd->argDouble(1);

   if (aCmd->isCmd("UseGamma"))        mUseGamma      = aCmd->argBool(1);
   if (aCmd->isCmd("Gamma"))           mGamma         = aCmd->argAngle(1);
   if (aCmd->isCmd("WD"))              mWD            = aCmd->argDouble(1);

   if (aCmd->isCmd("Sigma"))           mSigma         = aCmd->argDouble(1);

   if (aCmd->isCmd("NumTrialTests"))   mNumTrialTests = aCmd->argInt(1);
   if (aCmd->isCmd("TrialDeltaA"))     mTrialDeltaA   = aCmd->argAngle(1);
   if (aCmd->isCmd("TrialDeltaT"))     mTrialDeltaA   = aCmd->argDouble(1);

   if (aCmd->isCmd("SyntheticFlag"))       mSyntheticFlag      = aCmd->argBool(1);
   if (aCmd->isCmd("PulsePixelWidth"))     mPulsePixelWidth    = aCmd->argInt(1);
   if (aCmd->isCmd("PulseGaussianWidth"))  mPulseGaussianWidth = aCmd->argDouble(1);
   if (aCmd->isCmd("PulseAmplitude"))      mPulseAmplitude     = aCmd->argDouble(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace