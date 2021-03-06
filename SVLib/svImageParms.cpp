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

   mNN2dRuleFilterParms.reset();
   mNN3dRuleFilterParms.reset();

   mRoiCenter.reset();
   mRoiB = 0;
   mRoiHeaderCode = 0;
   mRoiSelectCode = 0;
   mRoiShowMode = 0;
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
   printf("RoiCenter                 %10d %10d\n", mRoiCenter.mRow, mRoiCenter.mCol);
   printf("RoiB                     %10d\n", mRoiB);
   printf("RoiHeaderCode            %10d\n", mRoiHeaderCode);
   printf("RoiShowMode              %10d\n", mRoiShowMode);
   printf("RoiSelectCode            %10d\n", mRoiSelectCode);
   mNN3dRuleFilterParms.show();
   return;
   printf("InputImageFileName                %s\n", mInputImageFileName);
   printf("OutputImageFileName               %s\n", mOutputImageFileName);
   mNN2dRuleFilterParms.show();
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

   if (aCmd->isCmd("RoiCenter"))            mRoiCenter.execute(aCmd);
   if (aCmd->isCmd("RoiB"))                mRoiB = aCmd->argInt(1);
   if (aCmd->isCmd("RoiHeaderCode"))       mRoiHeaderCode = aCmd->argInt(1);
   if (aCmd->isCmd("RoiShowMode"))         mRoiShowMode = aCmd->argInt(1);
   if (aCmd->isCmd("RoiSelectCode"))       mRoiSelectCode = aCmd->argInt(1);

   if (aCmd->isCmd("InputImageFileName"))  aCmd->copyArgString(1, mInputImageFileName, cMaxStringSize);
   if (aCmd->isCmd("OutputImageFileName")) aCmd->copyArgString(1, mOutputImageFileName, cMaxStringSize);

   if (aCmd->isCmd("NN2dRuleFilterParms")) readSection(aCmd->argString(1), &mNN2dRuleFilterParms);
   if (aCmd->isCmd("NN3dRuleFilterParms")) readSection(aCmd->argString(1), &mNN3dRuleFilterParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Override some variables with simulation parms variables.

void ImageParms::readOverrides(SimParms* aSimParms)
{
   if (aSimParms->mImageGenParmsS2.mRoiCenter.mRow != 0)
   {
      mRoiCenter = aSimParms->mImageGenParmsS2.mRoiCenter;
   }

   if (aSimParms->mImageGenParmsS2.mRoiB != 0)
   {
      mRoiB = aSimParms->mImageGenParmsS2.mRoiB;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace