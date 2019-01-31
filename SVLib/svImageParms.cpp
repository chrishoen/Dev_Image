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

   mInputImageFileName[0]=0;
   mInputRoiFileName[0] = 0;
   mOutputImageFileName[0] = 0;
   mOutputRoiFileName[0] = 0;

   mFilterParms.reset();

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
   printf("InputImageFileName     %-12s\n", mInputImageFileName);
   printf("InputRoiFileName       %-12s\n", mInputRoiFileName);
   printf("OutputImageFileName    %-12s\n", mOutputImageFileName);
   printf("OutputRoiFileName      %-12s\n", mOutputRoiFileName);

   printf("\n");
   mFilterParms.show();
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

   if (aCmd->isCmd("InputImageFileName"))  aCmd->copyArgString(1, mInputImageFileName, cMaxStringSize);
   if (aCmd->isCmd("InputRoiFileName"))    aCmd->copyArgString(1, mInputRoiFileName, cMaxStringSize);
   if (aCmd->isCmd("OutputImageFileName")) aCmd->copyArgString(1, mOutputImageFileName, cMaxStringSize);
   if (aCmd->isCmd("OutputRoiFileName"))   aCmd->copyArgString(1, mOutputRoiFileName, cMaxStringSize);

   if (aCmd->isCmd("FilterParms"))         readSection(aCmd->argString(1), &mFilterParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace