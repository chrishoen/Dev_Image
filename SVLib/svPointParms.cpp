//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"


#define  _POINTPARMS_CPP_
#include "svPointParms.h"

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

PointParms::PointParms()
{
   reset();
}

void PointParms::reset()
{
   BaseClass::reset();
   BaseClass::setFileName_RelAlphaFiles("Image/SV_Point_Parms.txt");

   mMajorGridSize.reset();
   mGridSize.reset();
   mSubGridSize.reset();

   mNeighborhoodSize = 0;
   mPointEstimatorLimit = 0;

   mNoiseFloorFlag = false;

   mSearchThreshold = 0.0;
   mTrackThresholdScale = 0.0;
   mTrackThresholdMin = 0.0;

   mThresholdAboveMin = 0;
   mThresholdAboveMax = 0;

   mSearch4AutoFlag = false;
   mSearch4Scale = 0.0;
   mSearch4Limit = 0;

   mSlantFilterAlpha = 0.0;

   mPointEstimatorLimit = 0;
   mStage4ThrowFlag = false;

   mGaussBlurFlag = false;
   mGaussBlur = 0;

   mAlphaFilterFlag = false;
   mAlpha = 0.0;

   mLogEnable = false;

   mImageDir [0]=0;
   mImageSaveFlag    = false;

   mCapturedImageFileName          [0]=0;
   mFilteredImageFileName          [0]=0;
   mNoiseFloorFileName             [0]=0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void PointParms::show()
{
   printf("\n");
   printf("PointParms************************************************** %s\n", mTargetSection);

   printf("\n");
   printf("\n");
   printf("MajorGridSize            %10d %10d\n",   mMajorGridSize.mRows,mMajorGridSize.mCols);
   printf("GridSize                 %10d %10d\n",   mGridSize.mRows,mGridSize.mCols);
   printf("SubGridSize              %10d %10d\n",   mSubGridSize.mRows,mSubGridSize.mCols);
   printf("\n");
   printf("NeighborhoodSize         %10d\n",        mNeighborhoodSize);
   printf("PointEstimatorLimit      %10d\n",        mPointEstimatorLimit);
   printf("Search4AutoFlag          %10s\n",        my_string_from_bool(mSearch4AutoFlag));

   printf("\n");
   printf("NoiseFloorFlag           %10s\n",        my_string_from_bool(mNoiseFloorFlag));
   printf("SearchThreshold          %10.2f\n",      mSearchThreshold);
   printf("TrackThresholdScale      %10.2f\n",      mTrackThresholdScale);
   printf("TrackThresholdMin        %10.2f\n",      mTrackThresholdMin);
   printf("ThresholdAboveMin        %10d\n",        mThresholdAboveMin);
   printf("ThresholdAboveMax        %10d\n",        mThresholdAboveMax);
   printf("Search4Scale             %10.2f\n",      mSearch4Scale);
   printf("Search4Limit             %10d\n",        mSearch4Limit);
   printf("SlantFilterAlpha         %10.2f\n",      mSlantFilterAlpha);
   printf("PointEstimatorLimit      %10d\n",        mPointEstimatorLimit);
   printf("Stage4ThrowFlag          %10s\n",        my_string_from_bool(mStage4ThrowFlag));

   printf("\n");
   printf("GaussBlurFlag                  %10s\n",   my_string_from_bool(mGaussBlurFlag));
   printf("GaussBlur                      %10d\n",   mGaussBlur);
   printf("AlphaFilterFlag                %10s\n",   my_string_from_bool(mAlphaFilterFlag));
   printf("Alpha                          %10.2f\n", mAlpha);

   printf("\n");
   printf("LogEnable                      %s\n", my_string_from_bool(mLogEnable));
   
   printf("\n");
   printf("ImageDir                       %s\n", mImageDir);
   printf("ImageSaveFlag                  %s\n", my_string_from_bool(mImageSaveFlag));

   printf("\n");
   printf("CapturedImageFileName          %s\n", mCapturedImageFileName);
   printf("FilteredImageFileName          %s\n", mFilteredImageFileName);
   printf("NoiseFloorFileName             %s\n", mNoiseFloorFileName);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void PointParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("MajorGridSize"))            mMajorGridSize.execute(aCmd);
   if (aCmd->isCmd("GridSize"))                 mGridSize.execute(aCmd);

   if (aCmd->isCmd("NeighborhoodSize"))         mNeighborhoodSize = aCmd->argInt(1);
   if (aCmd->isCmd("PointEstimatorLimit"))      mPointEstimatorLimit = aCmd->argInt(1);
   if (aCmd->isCmd("Search4AutoFlag"))          mSearch4AutoFlag = aCmd->argBool(1);

   if (aCmd->isCmd("NoiseFloorFlag"))           mNoiseFloorFlag = aCmd->argBool(1);
   if (aCmd->isCmd("SearchThreshold"))          mSearchThreshold = aCmd->argInt(1);
   if (aCmd->isCmd("TrackThresholdScale"))      mTrackThresholdScale  = aCmd->argDouble(1);
   if (aCmd->isCmd("TrackThresholdMin"))        mTrackThresholdMin  = aCmd->argDouble(1);
   if (aCmd->isCmd("ThresholdAboveMin"))        mThresholdAboveMin  = aCmd->argInt(1);
   if (aCmd->isCmd("ThresholdAboveMax"))        mThresholdAboveMax  = aCmd->argInt(1);
   if (aCmd->isCmd("Search4Scale"))             mSearch4Scale = aCmd->argDouble(1);
   if (aCmd->isCmd("Search4Limit"))             mSearch4Limit = aCmd->argInt(1);
   if (aCmd->isCmd("SlantFilterAlpha"))         mSlantFilterAlpha = aCmd->argDouble(1);
   if (aCmd->isCmd("PointEstimatorLimit"))      mPointEstimatorLimit = aCmd->argInt(1);
   if (aCmd->isCmd("Stage4ThrowFlag"))          mStage4ThrowFlag = aCmd->argBool(1);

   if (aCmd->isCmd("GaussBlurFlag"))            mGaussBlurFlag   = aCmd->argBool(1);
   if (aCmd->isCmd("GaussBlur"))                mGaussBlur       = aCmd->argInt(1);
   if (aCmd->isCmd("AlphaFilterFlag"))          mAlphaFilterFlag = aCmd->argBool(1);
   if (aCmd->isCmd("Alpha"))                    mAlpha           = aCmd->argDouble(1);

   if (aCmd->isCmd("LogEnable"))                mLogEnable = aCmd->argBool(1);
   if (aCmd->isCmd("ImageDir"))                 aCmd->copyArgString(1, mImageDir,cMaxStringSize);
   if (aCmd->isCmd("ImageSaveFlag"))            mImageSaveFlag = aCmd->argBool(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void PointParms::expand()
{
   strcpy(mCapturedImageFileName,mImageDir);
   strcat(mCapturedImageFileName,"\\CapturedImage.png");

   strcpy(mFilteredImageFileName,mImageDir);
   strcat(mFilteredImageFileName,"\\FilteredImage.png");

   strcpy(mNoiseFloorFileName,mImageDir);
   strcat(mNoiseFloorFileName,"\\NoiseFloor.png");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace