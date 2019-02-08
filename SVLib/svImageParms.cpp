//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#define  _SVIMAGEPARMS_CPP_
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

   mInputImageFileName[0] = 0;
   mOutputImageFileName[0] = 0;
   mTestImageFileName[0] = 0;

   mContourFilterParms.reset();

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
   printf("ImageParms********************************************** %s\n", mTargetSection);
   printf("RoiPixel                 %10d %10d\n", mRoiPixel.mRow, mRoiPixel.mCol);
   printf("RoiB                     %10d\n", mRoiB);
   printf("InputImageFileName                %s\n", mInputImageFileName);
   printf("OutputImageFileName               %s\n", mOutputImageFileName);
   printf("TestImageFileName                 %s\n", mTestImageFileName);
   mContourFilterParms.show();
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
   if (aCmd->isCmd("OutputImageFileName")) aCmd->copyArgString(1, mOutputImageFileName, cMaxStringSize);
   if (aCmd->isCmd("TestImageFileName"))   aCmd->copyArgString(1, mTestImageFileName, cMaxStringSize);

   if (aCmd->isCmd("ContourFilterParms"))  readSection(aCmd->argString(1), &mContourFilterParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Override some variables with simulation parms variables.

void ImageParms::readOverrides(SimParms* aSimParms)
{
   if (aSimParms->mImageGenParms.mRoiPixel.mRow != 0)
   {
      mRoiPixel = aSimParms->mImageGenParms.mRoiPixel;
   }

   if (aSimParms->mImageGenParms.mRoiB != 0)
   {
      mRoiB = aSimParms->mImageGenParms.mRoiB;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace