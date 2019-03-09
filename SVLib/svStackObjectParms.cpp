//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svStackObjectParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

StackObjectParms::StackObjectParms()
{
   reset();
}

void StackObjectParms::reset()
{
   mValid = false;
   mName[0] = 0;

   mTileEnable.reset();
   mTileHeight.reset();
   mTileParmSection.reset();

   for (int i = 0; i < cMaxTiles; i++)
   {
      mTileBegin[0] = 0;
      mTileEnd[0] = 0;
      mTileParms[i].reset();
   }
}

void StackObjectParms::setCenter(RCIndex aCenter)
{
   for (int i = 0; i < cMaxTiles; i++)
   {
      mTileParms[i].mCenter = aCenter;
   }
}

RCIndex StackObjectParms::getReverseRoiCenter(int aReverseIndex)
{
   int tTileIndex = 0;
   int tTileReverseIndex = 0;
   getTileIndex(aReverseIndex, tTileIndex, tTileReverseIndex);

   return mTileParms[tTileIndex].getReverseRoiCenter(tTileReverseIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a tile index and a tile reverse stack index as a function of a
// reverse stack index.

void StackObjectParms::getTileIndex(int aReverseIndex, int& aTileIndex, int& aTileReverseIndex)
{
   aTileIndex = 0;
   aTileReverseIndex = 0;
   for (int i = 0; i < cMaxTiles; i++)
   {
      if (mTileEnable[i] && mTileBegin[i] <= aReverseIndex && aReverseIndex <= mTileEnd[i])
      {
         aTileIndex = i;
         aTileReverseIndex = aReverseIndex - mTileBegin[i];
         return;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set expanded member variables. This is called after the entire
// section of the command file has been processed.

void StackObjectParms::expand()
{
   int tBegin = 0;
   int tEnd = 0;

   for (int i = 0; i < cMaxTiles; i++)
   {
      if (mTileEnable[i])
      {
         mTileBegin[i] = tBegin;
         mTileEnd[i]   = tBegin + mTileHeight[i] - 1;
         tBegin += mTileHeight[i];
      }
      else
      {
         mTileBegin[i] = -1;
         mTileEnd[i] = -1;
      }
   }

   for (int i = 0; i < cMaxTiles; i++)
   {
      if (strlen(mTileParmSection[i]) != 0 && strcmp(mTileParmSection[i], "empty") != 0)
      {
         if (mTileEnable[i])
         {
            readSection(mTileParmSection[i], &mTileParms[i]);
            mTileParms[i].setName(mTileParmSection[i]);
            mTileParms[i].mValid = true;
         }
      }
   }

   for (int i = 0; i < cMaxTiles; i++)
   {
      mTileParms[i].expand();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void StackObjectParms::show()
{
   printf("\n");
   printf("StackObjectParms*************************************BEGIN\n");

   printf("Name           %20s\n", mName);

   mTileEnable.show("TileEnable");
   mTileHeight.show("TileHeight");
   mTileParmSection.show("TileParmSection");

   for (int i = 0; i < cMaxTiles; i++)
   {
   printf("TileBeginEnd             %10d %4d\n", mTileBegin[i], mTileEnd[i]);
   }

   for (int i = 0; i < cMaxTiles; i++)
   {
      mTileParms[i].show("Tile");
   }
   printf("StackObjectParms*************************************END\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void StackObjectParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("Name"))              aCmd->copyArgString(1, mName, cMaxStringSize);

   if (aCmd->isCmd("TileEnable"))        nestedPush(aCmd, &mTileEnable);
   if (aCmd->isCmd("TileHeight"))        nestedPush(aCmd, &mTileHeight);
   if (aCmd->isCmd("TileParmSection"))   nestedPush(aCmd, &mTileParmSection);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace