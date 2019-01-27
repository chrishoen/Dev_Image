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

   mImagePixelPitch = 0.0;

   mImageSize.reset();

   mImageRowLimit = 0;
   mImageColLimit = 0;

   mImagePixelPerMM = 0.0;
   mImageMMPerPixel = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void SysParms::expand()
{
   mImagePixelPerMM = 1.0/mImagePixelPitch;
   mImageMMPerPixel = mImagePixelPitch;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SysParms::show()
{
   printf("\n");
   printf("SysParms************************************************ %s\n", mTargetSection);

   printf("ImagePixelPitch      %10.6f\n", mImagePixelPitch);

   printf("\n");
   printf("ImageSize            %10d %10d\n",  mImageSize.mRows,mImageSize.mCols);

   printf("\n");
   printf("ImageRowLimit        %10d\n",  mImageRowLimit);
   printf("ImageColLimit        %10d\n",  mImageColLimit);

   printf("\n");
   printf("ImagePixelPerMM      %10.6f\n", mImagePixelPerMM);
   printf("ImageMMPerPixel      %10.6f\n", mImageMMPerPixel);
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

   if (aCmd->isCmd("ImagePixelPitch"))      mImagePixelPitch = aCmd->argDouble(1);
   if (aCmd->isCmd("ImageRowLimit"))        mImageRowLimit = aCmd->argInt(1);
   if (aCmd->isCmd("ImageColLimit"))        mImageColLimit = aCmd->argInt(1);

   if (aCmd->isCmd("ImageSize"))            mImageSize.execute(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace