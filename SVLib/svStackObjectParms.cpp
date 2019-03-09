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
   mTileHeights.reset();
   mTileParmSections.reset();

   for (int i = 0; i < cMaxTiles; i++)
   {
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

RCIndex StackObjectParms::getRoiCenter(int aStackIndex)
{
   return mTileParms[0].getRoiCenter(aStackIndex);
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void StackObjectParms::expand()
{
   for (int i = 0; i < cMaxTiles; i++)
   {
      if (strlen(mTileParmSections[i]) != 0 && strcmp(mTileParmSections[i], "empty") != 0)
      {
         if (mTileEnable[i])
         {
            readSection(mTileParmSections[i], &mTileParms[i]);
            mTileParms[i].setName(mTileParmSections[i]);
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
   printf("StackObjectParms****************************************** %s\n", mTargetSection);

   printf("Name           %20s\n", mName);

   for (int i = 0; i < cMaxTiles; i++)
   {
      mTileParms[i].show("Tile");
   }
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
   if (aCmd->isCmd("TileHeight"))        nestedPush(aCmd, &mTileHeights);
   if (aCmd->isCmd("TileParmSections"))  nestedPush(aCmd, &mTileParmSections);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace