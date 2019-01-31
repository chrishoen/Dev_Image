//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#define  _SVSIMULATIONPARMS_CPP_
#include "svImageParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

ImageParms::ImageParms()
{
   reset();
}

void ImageParms::reset()
{
   BaseClass::reset();
   BaseClass::setFileName_RelAlphaFiles("Image/SV_Image_Parms.txt");

   mImageFileName1[0] = 0;
   mImageFileName2[0] = 0;

   mRoiPixel.reset();
   mRoiB = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void ImageParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void ImageParms::show()
{
   printf("\n");
   printf("ImageParms****************************************** %s\n", mTargetSection);

   printf("\n");
   printf("RoiPixel               %10d %10d\n", mRoiPixel.mRow, mRoiPixel.mCol);
   printf("RoiB                   %10d\n", mRoiB);

   printf("\n");
   printf("ImageFileName1         %-10s\n", mImageFileName1);
   printf("ImageFileName2         %-10s\n", mImageFileName2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void ImageParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("RoiPixel"))            mRoiPixel.execute(aCmd);
   if (aCmd->isCmd("RoiB"))                mRoiB = aCmd->argInt(1);

   if (aCmd->isCmd("ImageFileName1"))      aCmd->copyArgString(1, mImageFileName1, cMaxStringSize);
   if (aCmd->isCmd("ImageFileName2"))      aCmd->copyArgString(1, mImageFileName2, cMaxStringSize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace