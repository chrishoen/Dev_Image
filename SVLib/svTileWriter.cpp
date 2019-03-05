/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svRCIndex.h"
#include "svRCLoop.h"
#include "svTileWriter.h"

#include "svImageFunctions.h"
#include "svImageShow.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

TileWriter::TileWriter()
{
   reset();
}

TileWriter::TileWriter(TileParms* aParms)
{
   mP = aParms;
   reset();
}

void TileWriter::initialize(TileParms* aParms)
{
   mP = aParms;
   reset();
}

void TileWriter::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a tile to an image according to the parms.

void TileWriter::doWrite(
   cv::Mat&       aOutputImage)    // Output
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   Prn::print(Prn::View11, "doWrite %4d %4d", aOutputImage.rows, aOutputImage.cols);

   // Set the image wrappers.
   mOutput.set(aOutputImage);

   // Write the tile.
   if (mP->isSquare())  doWriteSquare();
   if (mP->isDiamond()) doWriteDiamond();

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a square tile according to the parms.

void TileWriter::doWriteSquare()
{
   // Loop to set output image pixels high.
   int tDitherRows = mP->mDelta.mRows * mP->mRepeatNum;
   int tDitherCols = mP->mDelta.mCols * mP->mRepeatNum;
   SV::RCDitherLoop2 tDitherLoop(mP->mCenter, tDitherRows, tDitherCols);
   while (tDitherLoop.loop())
   {
      mOutput.at(tDitherLoop()) = 255;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a diamond tile according to the parms.

void TileWriter::doWriteDiamond()
{
   int tRepeatNum = mP->mRepeatNum;
   int tRowNum = mP->mDelta.mRows;
   int tColNum = mP->mDelta.mCols;

   int tRowIndex = 0;
   for (int tRow = 0; tRow < tRepeatNum; tRow++)
   {
      for (int tRowWrite = 0; tRowWrite < tRowNum; tRowWrite++)
      {
         int tColIndex = 0;
         mOutput.at(mP->mCenter + RCIndex(tRowIndex,tColIndex)) = 255;
         for (int tCol = 0; tCol < tRepeatNum - tRow - 1; tCol++)
         {
            for (int tColWrite = 0; tColWrite < tColNum; tColWrite++)
            {
               tColIndex++;
               mOutput.at(mP->mCenter + RCIndex(tRowIndex, tColIndex)) = 255;
            }
         }
         tRowIndex++;
      }
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

