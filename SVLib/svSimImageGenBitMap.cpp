/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svRCLoop.h"
#include "svImageWrapper.h"

#include "svSimImageGenBitMap.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

SimImageGenBitMap::SimImageGenBitMap()
{
   reset();
}

SimImageGenBitMap::SimImageGenBitMap(SimImageGenParms* aParms)
{
   BaseClass::mP = aParms;
   reset();
}

void SimImageGenBitMap::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the image, depending on the parms.

void SimImageGenBitMap::doGenerateImage(
   cv::Mat&       aImage)          // Output
{
   Prn::print(0, "SimImageGenBitMap::doGenerateImage");
   // Create an image filled with all zeros.
   BaseClass::doCreateZeroImage(aImage);

   // Image wrappers.
   ImageWrapper tImage(aImage);

   // Loop through all of the pixels of the input image.
   SV::RCIndexLoop tBitMapLoop(mP->mBitMapSize);
   while (tBitMapLoop.loop())
   {
      // Image target pixel.
      RCIndex tImagePixel = mP->mBitMapCorner + tBitMapLoop();

      // If a bitmap pixel is true then set the corresponging
      // image pixel.
      if (mP->mBitMap[tBitMapLoop.mRow][tBitMapLoop.mCol])
      {
         //Prn::print(0, "SET PIXEL %4d %4d", tImagePixel.mRow, tImagePixel.mCol);
         tImage.at(tImagePixel) = 255;
      }
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace