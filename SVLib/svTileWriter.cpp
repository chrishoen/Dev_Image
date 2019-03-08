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
   Prn::print(Prn::View11, "TileWriter::doWrite %3d", mP->mNumLoop);

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
   int tDitherRows = mP->mNumRow * mP->mNumLoop;
   int tDitherCols = mP->mNumCol * mP->mNumLoop;
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
   int tNumLoop = mP->mNumLoop + 1;
   int tNumRow = mP->mNumRow;
   int tNumCol = mP->mNumCol;

   int tRowCount = tNumLoop * tNumRow - tNumRow / 2;
   int tColCount = tNumLoop * tNumCol - tNumCol / 2;

   for (int tRow = 0; tRow < tRowCount; tRow++)
   {
      int tRowIndex = (tRow + tNumRow / 2) / tNumRow;
      for (int tCol = 0; tCol < tColCount; tCol++)
      {
         int tColIndex = (tCol + tNumCol / 2) / tNumCol;
         bool tFlag = tColIndex <= tNumLoop - tRowIndex - 1;
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

