//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svDefs.h"
#include "svSysParms.h"

#define  _SVSimImageGenParms_CPP_
#include "svSimImageGenParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

SimImageGenParms::SimImageGenParms()
{
   reset();
}

void SimImageGenParms::reset()
{
   mImageType    = cNone;

   mImageSize = gSysParms.mImageSize;

   mImageB = 0;

   mGaussianWidth = 0.0;
   mGaussianAmplitude = 0.0;

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SimImageGenParms::show()
{
   printf("\n");
   printf("SimImageGenParms*******************************************\n");
   printf("ImageType                %10s\n",        asStringImageType(mImageType));
   printf("ImageSize                %10d %10d\n",   mImageSize.mRows,mImageSize.mCols);
   printf("ImageB                   %10d\n", mImageB);
   printf("GaussianWidth            %10.6f\n", mGaussianWidth);
   printf("GaussianAmplitude        %10.6f\n", mGaussianAmplitude);
   printf("SimImageGenParms*******************************************\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void SimImageGenParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("ImageSize"))            mImageSize.execute(aCmd);

   if (aCmd->isCmd("ImageType"))
   {
      if (aCmd->isArgString(1, asStringImageType(cNone)))             mImageType = cNone;
      if (aCmd->isArgString(1, asStringImageType(cImageCircle)))      mImageType = cImageCircle;
      if (aCmd->isArgString(1, asStringImageType(cImageSquare)))      mImageType = cImageSquare;
      if (aCmd->isArgString(1, asStringImageType(cImageImpulse)))     mImageType = cImageImpulse;
      if (aCmd->isArgString(1, asStringImageType(cImageGaussian)))    mImageType = cImageGaussian;
   }

   if (aCmd->isCmd("ImageB"))              mImageB = aCmd->argInt(1);
   if (aCmd->isCmd("GaussianWidth"))       mGaussianWidth = aCmd->argDouble(1);
   if (aCmd->isCmd("GaussianAmplitude"))   mGaussianAmplitude = aCmd->argDouble(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

char* SimImageGenParms::asStringImageType(int aX)
{
   switch (aX)
   {
   case cNone               : return "None";
   case cImageCircle        : return "Circle";
   case cImageSquare        : return "Square";
   case cImageImpulse       : return "Impulse";
   case cImageGaussian      : return "Gaussian";
   default : return "UNKNOWN";
   }
}

char* SimImageGenParms::asStringImageType()
{
   return asStringImageType(mImageType);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace