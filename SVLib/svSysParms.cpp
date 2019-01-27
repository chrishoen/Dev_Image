//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#define  _SVSYSPARMS_CPP_
#include "svSysParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

SysParms::SysParms()
{
   reset();
}

void SysParms::reset()
{
   BaseClass::reset();
   BaseClass::setFileName_RelAlphaFiles("Image/SV_Sys_Parms.txt");

   mTargetPixelPitch = 0.0;
   mSensorPixelPitch = 0.0;

   mTargetSize.reset();
   mSensorSize.reset();

   mSensorRowLimit = 0;
   mSensorColLimit = 0;

   mTargetPixelPerMM = 0.0;
   mTargetMMPerPixel = 0.0;
   mSensorPixelPerMM = 0.0;
   mSensorMMPerPixel = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void SysParms::expand()
{
   mTargetPixelPerMM = 1.0/mTargetPixelPitch;
   mTargetMMPerPixel = mTargetPixelPitch;
   mSensorPixelPerMM = 1.0/mSensorPixelPitch;
   mSensorMMPerPixel = mSensorPixelPitch;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SysParms::show()
{
   printf("\n");
   printf("SysParms************************************************ %s\n", mTargetSection);

   printf("TargetPixelPitch      %10.6f\n", mTargetPixelPitch);
   printf("SensorPixelPitch      %10.6f\n", mSensorPixelPitch);

   printf("\n");
   printf("TargetSize            %10d %10d\n",  mTargetSize.mRows,mTargetSize.mCols);
   printf("SensorSize            %10d %10d\n",  mSensorSize.mRows,mSensorSize.mCols);

   printf("\n");
   printf("SensorRowLimit        %10d\n",  mSensorRowLimit);
   printf("SensorColLimit        %10d\n",  mSensorColLimit);

   printf("\n");
   printf("TargetPixelPerMM      %10.6f\n", mTargetPixelPerMM);
   printf("TargetMMPerPixel      %10.6f\n", mTargetMMPerPixel);
   printf("SensorPixelPerMM      %10.6f\n", mSensorPixelPerMM);
   printf("SensorMMPerPixel      %10.6f\n", mSensorMMPerPixel);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void SysParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("TargetPixelPitch"))      mTargetPixelPitch = aCmd->argDouble(1);
   if (aCmd->isCmd("SensorPixelPitch"))      mSensorPixelPitch = aCmd->argDouble(1);
   if (aCmd->isCmd("SensorRowLimit"))        mSensorRowLimit = aCmd->argInt(1);
   if (aCmd->isCmd("SensorColLimit"))        mSensorColLimit = aCmd->argInt(1);

   if (aCmd->isCmd("TargetSize"))            mTargetSize.execute(aCmd);
   if (aCmd->isCmd("SensorSize"))            mSensorSize.execute(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Override some variables with grid parms variables.

void SysParms::readOverrides(GridParms* aGridParms)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace