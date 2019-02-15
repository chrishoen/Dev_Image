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

   mInputImageDFileName[0] = 0;
   mInputImageCFileName[0] = 0;
   mInputImageUFileName[0] = 0;
   mOutputImageFileName[0] = 0;

   mNN2dRuleFilterParms.reset();
   mNN3dRuleFilterParms.reset();
   mContourFilterParms.reset();

   mRoiPixel.reset();
   mRoiB = 0;
   mRoiCode = 0;
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
   printf("RoiCode                  %10d\n", mRoiCode);
   printf("InputImageDFileName               %s\n", mInputImageDFileName);
   printf("InputImageCFileName               %s\n", mInputImageCFileName);
   printf("InputImageUFileName               %s\n", mInputImageUFileName);
   printf("OutputImageFileName               %s\n", mOutputImageFileName);
   mNN2dRuleFilterParms.show();
   mNN3dRuleFilterParms.show();
   return;
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
   if (aCmd->isCmd("RoiCode"))             mRoiCode = aCmd->argInt(1);

   if (aCmd->isCmd("InputImageDFileName"))  aCmd->copyArgString(1, mInputImageDFileName, cMaxStringSize);
   if (aCmd->isCmd("InputImageCFileName"))  aCmd->copyArgString(1, mInputImageCFileName, cMaxStringSize);
   if (aCmd->isCmd("InputImageUFileName"))  aCmd->copyArgString(1, mInputImageUFileName, cMaxStringSize);
   if (aCmd->isCmd("OutputImageFileName"))  aCmd->copyArgString(1, mOutputImageFileName, cMaxStringSize);

   if (aCmd->isCmd("NN2dRuleFilterParms"))   readSection(aCmd->argString(1), &mNN2dRuleFilterParms);
   if (aCmd->isCmd("NN3dRuleFilterParms"))   readSection(aCmd->argString(1), &mNN3dRuleFilterParms);
   if (aCmd->isCmd("ContourFilterParms"))    readSection(aCmd->argString(1), &mContourFilterParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Override some variables with simulation parms variables.

void ImageParms::readOverrides(SimParms* aSimParms)
{
   if (aSimParms->mImageGenParmsC.mRoiPixel.mRow != 0)
   {
      mRoiPixel = aSimParms->mImageGenParmsC.mRoiPixel;
   }

   if (aSimParms->mImageGenParmsC.mRoiB != 0)
   {
      mRoiB = aSimParms->mImageGenParmsC.mRoiB;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace