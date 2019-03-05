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
   int tLoopNum = mP->mRepeatNum;
   int tRowNum = mP->mDelta.mRows;
   int tColNum = mP->mDelta.mCols;

   int tRowCount = tLoopNum * tRowNum - tRowNum / 2;
   int tColCount = tLoopNum * tColNum - tColNum / 2;

   for (int tRow = 0; tRow < tRowCount; tRow++)
   {
      int tRowIndex = (tRow + tRowNum / 2) / tRowNum;
      for (int tCol = 0; tCol < tColCount; tCol++)
      {
         int tColIndex = (tCol + tColNum / 2) / tColNum;
         bool tFlag = tColIndex <= tLoopNum - tRowIndex - 1;
         if (tFlag)
         {
            mOutput.at(mP->mCenter + RCIndex(-tRow, -tCol)) = 255;
            mOutput.at(mP->mCenter + RCIndex(-tRow,  tCol)) = 255;
            mOutput.at(mP->mCenter + RCIndex( tRow, -tCol)) = 255;
            mOutput.at(mP->mCenter + RCIndex( tRow,  tCol)) = 255;
         }
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

