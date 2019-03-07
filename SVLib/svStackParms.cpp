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

   mObjectEnable.reset();
   mObjectFileName.reset();
   mObjectLayout.reset();
   mMajorSize.reset();

   mObjectSize.reset();

   for (int i = 0; i < cMaxObjects; i++)
   {
      mObjectMajor[i].reset();
      mObjectParms[i].reset();
      mObjectSector[i].reset();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void StackParms::expand()
{
   // Read Stack objects from object parms files.
   for (int i = 0; i < cMaxObjects; i++)
   {
      if (strlen(mObjectFileName[i]) != 0 && mObjectEnable[i])
      {
         mObjectParms[i].setFileName_RelAlphaFiles(mObjectFileName[i]);
         mObjectParms[i].readSection("default");
         mObjectParms[i].mValid = true;
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
   mMajorSize.set(mObjectLayout.mRows, mObjectLayout.mCols);
   mObjectSize.mRows = gSysParms.mImageSize.mRows / mMajorSize.mRows;
   mObjectSize.mCols = gSysParms.mImageSize.mCols / mMajorSize.mCols;

   // Set stack object positioning parameters.
   for (int i = 0; i < cMaxObjects; i++)
   {
      RCIndex tCorner;
      RCIndex tCenter;

      // Stack object row column upper left corner offsets.
      tCorner.mRow = mObjectMajor[i].mRow * mObjectSize.mRows;
      tCorner.mCol = mObjectMajor[i].mCol * mObjectSize.mCols;

      // Stack object row column centers.
      tCenter.mRow = tCorner.mRow + mObjectSize.mRows / 2;
      tCenter.mCol = tCorner.mCol + mObjectSize.mCols / 2;

      // Stack object row column sectors.
      mObjectSector[i].set(tCorner, tCenter);
   }


   // Set stack objects parameters.
   for (int i = 0; i < cMaxObjects; i++)
   {
      mObjectParms[i].setCenter(mObjectSector[i].mCenter);
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void StackParms::show()
{
   printf("\n");
   printf("StackParms************************************************ %s\n", mTargetSection);

   for (int i = 0; i < cMaxObjects; i++)
   {
      if (mObjectParms[i].mValid)  mObjectParms[i].show();
   }

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
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void StackParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("ObjectFileName"))      nestedPush(aCmd, &mObjectFileName);
   if (aCmd->isCmd("ObjectEnable"))        nestedPush(aCmd, &mObjectEnable);

   if (aCmd->isCmd("ObjectLayout"))        nestedPush(aCmd, &mObjectLayout);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace