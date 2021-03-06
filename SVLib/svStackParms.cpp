//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svRCLoop.h"

#define  _SVSTACKPARMS_CPP_
#include "svStackParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

StackParms::StackParms()
{
   reset();
}

void StackParms::reset()
{
   BaseClass::reset();
   BaseClass::setFileName_RelAlphaFiles("Image/SV_Stack_Parms.txt");

   mStackName[0] = 0;
   mStackHeight = 0;
   mObjectHeight = 0;
   mRaftHeight = 0;
   mWarp.reset();

   mObjectEnable.reset();
   mObjectFileName.reset();
   mObjectLayout.reset();
   mObjectMajorSize.reset();
   mObjectSize.reset();
   for (int i = 0; i < cMaxObjects; i++)
   {
      mObjectMajor[i].reset();
      mObjectParms[i].reset();
      mObjectSector[i].reset();
   }

   mRaftEnable.reset();
   mRaftFileName.reset();
   mRaftLayout.reset();
   mRaftMajorSize.reset();
   mRaftSize.reset();
   for (int i = 0; i < cMaxRafts; i++)
   {
      mRaftMajor[i].reset();
      mRaftParms[i].reset();
      mRaftSector[i].reset();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get roi centers.

RCIndex StackParms::getReverseRoiCenter(int aObjectIndex, int aReverseIndex)
{
   int tObjectReverseIndex = aReverseIndex;
   int tRaftReverseIndex = aReverseIndex - mObjectHeight;

   if (aReverseIndex < mObjectHeight)
   {
      return mObjectParms[aObjectIndex].getReverseRoiCenter(tObjectReverseIndex);
   }
   else
   {
      return mRaftParms[aObjectIndex].getReverseRoiCenter(tRaftReverseIndex);
   }
}

RCIndex StackParms::getStackRoiCenter(int aObjectIndex, int aStackIndex)
{
   int tReverseIndex = mStackHeight - aStackIndex - 1;
   return getReverseRoiCenter(aObjectIndex,tReverseIndex);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void StackParms::expand()
{
   mStackHeight = mObjectHeight + mRaftHeight;
   expandObjects();
   expandRafts();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void StackParms::expandObjects()
{
   // Read Stack objects from object parms files.
   for (int i = 0; i < cMaxObjects; i++)
   {
      if (strlen(mObjectFileName[i]) != 0 && strcmp(mObjectFileName[i],"empty") != 0)
      {
         if (mObjectEnable[i])
         {
            mObjectParms[i].setFileName_RelAlphaFiles(mObjectFileName[i]);
            mObjectParms[i].readSection("default");
            mObjectParms[i].mValid = true;
         }
      }
   }

   // Set object major positioning.
   SV::RCIndexLoop tLoop(mObjectLayout.mRows, mObjectLayout.mCols);
   while (tLoop.loop())
   {
      int tObjectIndex = mObjectLayout[tLoop().mRow][tLoop().mCol];
      if (tObjectIndex > 0 && tObjectIndex < cMaxObjects)
      {
         mObjectMajor[tObjectIndex] = tLoop();
      }
   }

   // Stack object size.
   mObjectMajorSize.set(mObjectLayout.mRows, mObjectLayout.mCols);
   mObjectSize.mRows = gSysParms.mImageSize.mRows / mObjectMajorSize.mRows;
   mObjectSize.mCols = gSysParms.mImageSize.mCols / mObjectMajorSize.mCols;

   // Warp stack object size.
   mObjectSize.mRows = mWarp * mObjectSize.mRows;
   mObjectSize.mCols = mWarp * mObjectSize.mCols;

   // Set stack object positioning parameters.
   for (int i = 0; i < cMaxObjects; i++)
   {
      if (mObjectEnable[i])
      {
         RCIndex tCorner;
         RCIndex tCenter;

         // Stack object row column upper left corner offsets.
         tCorner.mRow = mObjectMajor[i].mRow * mObjectSize.mRows;
         tCorner.mCol = mObjectMajor[i].mCol * mObjectSize.mCols;

         // Stack object row column centers.
         tCenter.mRow = tCorner.mRow + mObjectSize.mRows / 2;
         tCenter.mCol = tCorner.mCol + mObjectSize.mCols / 2;

         // Warp shift corners and centers.
         int tRowWarpShift = (gSysParms.mImageSize.mRows - mWarp * gSysParms.mImageSize.mRows) / 2;
         int tColWarpShift = (gSysParms.mImageSize.mCols - mWarp * gSysParms.mImageSize.mCols) / 2;
         tCorner.mRow += tRowWarpShift;
         tCorner.mCol += tColWarpShift;
         tCenter.mRow += tRowWarpShift;
         tCenter.mCol += tColWarpShift;

         // Stack object row column sectors.
         mObjectSector[i].set(tCorner, tCenter);
      }
   }

   // Set stack objects parameters.
   for (int i = 0; i < cMaxObjects; i++)
   {
      mObjectParms[i].setSector(mObjectSector[i]);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void StackParms::expandRafts()
{
   // Read Stack rafts from raft parms files.
   for (int i = 0; i < cMaxRafts; i++)
   {
      if (strlen(mRaftFileName[i]) != 0 && strcmp(mRaftFileName[i], "empty") != 0)
      {
         if (mRaftEnable[i])
         {
            mRaftParms[i].setFileName_RelAlphaFiles(mRaftFileName[i]);
            mRaftParms[i].readSection("default");
            mRaftParms[i].mValid = true;
         }
      }
   }

   // Set raft major positioning.
   SV::RCIndexLoop tLoop(mRaftLayout.mRows, mRaftLayout.mCols);
   while (tLoop.loop())
   {
      int tRaftIndex = mRaftLayout[tLoop().mRow][tLoop().mCol];
      if (tRaftIndex > 0 && tRaftIndex < cMaxRafts)
      {
         mRaftMajor[tRaftIndex] = tLoop();
      }
   }

   // Stack raft size.
   mRaftMajorSize.set(mRaftLayout.mRows, mRaftLayout.mCols);
   mRaftSize.mRows = gSysParms.mImageSize.mRows / mRaftMajorSize.mRows;
   mRaftSize.mCols = gSysParms.mImageSize.mCols / mRaftMajorSize.mCols;

   // Warp stack raft size.
   mRaftSize.mRows = mWarp * mRaftSize.mRows;
   mRaftSize.mCols = mWarp * mRaftSize.mCols;

   // Set stack raft positioning parameters.
   for (int i = 0; i < cMaxRafts; i++)
   {
      if (mRaftEnable[i])
      {
         RCIndex tCorner;
         RCIndex tCenter;

         // Stack raft row column upper left corner offsets.
         tCorner.mRow = mRaftMajor[i].mRow * mRaftSize.mRows;
         tCorner.mCol = mRaftMajor[i].mCol * mRaftSize.mCols;

         // Stack raft row column centers.
         tCenter.mRow = tCorner.mRow + mRaftSize.mRows / 2;
         tCenter.mCol = tCorner.mCol + mRaftSize.mCols / 2;

         // Warp shift corners and centers.
         int tRowWarpShift = (gSysParms.mImageSize.mRows - mWarp * gSysParms.mImageSize.mRows) / 2;
         int tColWarpShift = (gSysParms.mImageSize.mCols - mWarp * gSysParms.mImageSize.mCols) / 2;
         tCorner.mRow += tRowWarpShift;
         tCorner.mCol += tColWarpShift;
         tCenter.mRow += tRowWarpShift;
         tCenter.mCol += tColWarpShift;

         // Stack raft row column sectors.
         mRaftSector[i].set(tCorner, tCenter);
      }
   }

   // Set stack rafts parameters.
   for (int i = 0; i < cMaxRafts; i++)
   {
      mRaftParms[i].setSector(mRaftSector[i]);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void StackParms::show(int aCode)
{
   switch (aCode)
   {
   case 0:
      showObjects();
      showRafts();
      break;
   case 1:
      showObjects();
      break;
   case 2:
      showRafts();
      break;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void StackParms::showObjects()
{
   printf("\n");
   printf("StackParms************************************************ %s\n", mTargetSection);

   for (int i = 0; i < cMaxObjects; i++)
   {
      if (mObjectParms[i].mValid)  mObjectParms[i].show();
   }

   printf("StackName      %20s\n", mStackName);
   printf("StackHeight              %10d\n", mStackHeight);
   printf("ObjectHeight             %10d\n", mObjectHeight);
   printf("RaftHeight               %10d\n", mRaftHeight);
   printf("Warp                     %10d %4d\n", mWarp.mNumer, mWarp.mDenom);

   mObjectEnable.show("ObjectEnable");
   mObjectFileName.show("ObjectFileName");
   mObjectLayout.show("ObjectLayout");

   printf("\n");
   printf("ObjectSize               %10d %4d\n", mObjectSize.mRows, mObjectSize.mCols);

   printf("\n");
   for (int i = 0; i < cMaxObjects; i++)
   {
   printf("Object1Major             %10d %4d\n", mObjectMajor[i].mRow, mObjectMajor[i].mCol);
   }

   printf("\n");
   for (int i = 0; i < cMaxObjects; i++)
   {
      mObjectSector[i].show1(0,"ObjectSector");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void StackParms::showRafts()
{
   printf("\n");
   printf("StackParms************************************************ %s\n", mTargetSection);

   for (int i = 0; i < cMaxRafts; i++)
   {
      if (mRaftParms[i].mValid)  mRaftParms[i].show();
   }

   printf("StackName      %20s\n", mStackName);
   printf("StackHeight              %10d\n", mStackHeight);
   printf("ObjectHeight             %10d\n", mObjectHeight);
   printf("RaftHeight               %10d\n", mRaftHeight);
   printf("Warp                     %10d %4d\n", mWarp.mNumer, mWarp.mDenom);

   mRaftEnable.show("RaftEnable");
   mRaftFileName.show("RaftFileName");
   mRaftLayout.show("RaftLayout");

   printf("\n");
   printf("RaftSize               %10d %4d\n", mRaftSize.mRows, mRaftSize.mCols);

   printf("\n");
   for (int i = 0; i < cMaxRafts; i++)
   {
      printf("Raft1Major             %10d %4d\n", mRaftMajor[i].mRow, mRaftMajor[i].mCol);
   }

   printf("\n");
   for (int i = 0; i < cMaxRafts; i++)
   {
      mRaftSector[i].show1(0, "RaftSector");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void StackParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("StackName"))         aCmd->copyArgString(1, mStackName, cMaxStringSize);
   if (aCmd->isCmd("ObjectHeight"))      mObjectHeight = aCmd->argInt(1);
   if (aCmd->isCmd("RaftHeight"))        mRaftHeight = aCmd->argInt(1);
   if (aCmd->isCmd("Warp"))              mWarp.readArgs(aCmd);

   if (aCmd->isCmd("ObjectFileName"))    nestedPush(aCmd, &mObjectFileName);
   if (aCmd->isCmd("ObjectEnable"))      nestedPush(aCmd, &mObjectEnable);
   if (aCmd->isCmd("ObjectLayout"))      nestedPush(aCmd, &mObjectLayout);

   if (aCmd->isCmd("RaftFileName"))      nestedPush(aCmd, &mRaftFileName);
   if (aCmd->isCmd("RaftEnable"))        nestedPush(aCmd, &mRaftEnable);
   if (aCmd->isCmd("RaftLayout"))        nestedPush(aCmd, &mRaftLayout);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace