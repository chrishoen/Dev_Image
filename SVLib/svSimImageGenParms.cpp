//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"

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
   mRoiPixel.reset();
   mRoiB = 0;
   mGaussianWidth = 0.0;
   mGaussianAmplitude = 0.0;
   mPolygonPoints.reset();
   mBitMapCorner.reset();
   mBitMap.reset();
   mBitMapSize.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SimImageGenParms::show()
{
   printf("SimImageGenParms*******************\n");
   printf("ImageType                %10s\n",        asStringImageType(mImageType));
   printf("ImageSize                %10d %10d\n",   mImageSize.mRows,mImageSize.mCols);
   printf("ImageB                   %10d\n",        mImageB);
   printf("GaussianWidth            %10.2f\n",      mGaussianWidth);
   printf("GaussianAmplitude        %10.2f\n",      mGaussianAmplitude);
   printf("RoiPixel                 %10d %10d\n",   mRoiPixel.mRow, mRoiPixel.mCol);
   printf("RoiB                     %10d\n",        mRoiB);
   mPolygonPoints.show("PolygonPoints");
   printf("BitMapCorner             %10d %10d\n",   mBitMapCorner.mRow, mBitMapCorner.mCol);
   printf("BitMapSize               %10d %10d\n",   mBitMapSize.mRows, mBitMapSize.mCols);
   mBitMap.show("BitMap");
   printf("SimImageGenParms*******************\n");
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
      if (aCmd->isArgString(1, asStringImageType(cImagePolygon)))     mImageType = cImagePolygon;
      if (aCmd->isArgString(1, asStringImageType(cImageBitMap)))      mImageType = cImageBitMap;
   }

   if (aCmd->isCmd("ImageB"))              mImageB = aCmd->argInt(1);
   if (aCmd->isCmd("RoiPixel"))            mRoiPixel.execute(aCmd);
   if (aCmd->isCmd("RoiB"))                mRoiB = aCmd->argInt(1);
   if (aCmd->isCmd("GaussianWidth"))       mGaussianWidth = aCmd->argDouble(1);
   if (aCmd->isCmd("GaussianAmplitude"))   mGaussianAmplitude = aCmd->argDouble(1);

   if (aCmd->isCmd("PolygonPoints"))       nestedPush(aCmd, &mPolygonPoints);

   if (aCmd->isCmd("BitMapCorner"))        mBitMapCorner.execute(aCmd);
   if (aCmd->isCmd("BitMap"))              nestedPush(aCmd, &mBitMap);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

void SimImageGenParms::expand()
{
   mBitMapSize.mRows = mBitMap.mRows;
   mBitMapSize.mCols = mBitMap.mCols;
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
   case cImagePolygon       : return "Polygon";
   case cImageBitMap        : return "BitMap";
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