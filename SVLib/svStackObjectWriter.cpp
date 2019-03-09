/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svStackObjectWriter.h"

#include "svImageFunctions.h"
#include "svImageShow.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Infastruccture.

StackObjectWriter::StackObjectWriter()
{
}

StackObjectWriter::~StackObjectWriter()
{
}

StackObjectWriter::StackObjectWriter(StackObjectParms* aParms)
{
   initialize(aParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void StackObjectWriter::initialize(StackObjectParms* aParms)
{
   // Store parms.
   mP = aParms;

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a stack object slice to an output image, based on a
// reverse stack index, according to the parms.

void StackObjectWriter::doWriteStackObject(
   int            aReverseIndex,   // Control
   cv::Mat&       aOutputImage)    // Output
{
   Prn::print(Prn::View11, "StackObjectWriter::doWriteStackObject");

   // Get the tile index and the tile reverse stack index from 
   // the reverse stack index.
   int tTileIndex = 0;
   int tTileReverseIndex = 0;
   mP->getTileIndex(aReverseIndex, tTileIndex, tTileReverseIndex);

   // Adjust the selected tile parameters.
   mP->mTileParms[tTileIndex].doAdjust(tTileReverseIndex);

   // Initialize the tile writer with the selected tile parameters.
   mTileWriter.initialize(&mP->mTileParms[tTileIndex]);

   // Write a selected tile to the output image.
   mTileWriter.doWrite(aOutputImage);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace