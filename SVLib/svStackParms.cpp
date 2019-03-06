//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"

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
   mMajorSize.reset();
   mObjectMajorTable.reset();

   mObjectSize.reset();

   for (int i = 0; i < cMaxObjects; i++)
   {
      mObjectMajor[i].reset();
      mObjectParms[i].reset();
      mObjectOffset[i].reset();
      mObjectCenter[i].reset();
      mObjectRect[i].reset();
   }

   mTestTable.reset();
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
// mMajorSize.set(mObjectMajorTable.mRows, mObjectMajorTable.mCols);
   for (int i = 0; i < cMaxObjects; i++)
   {
      mObjectMajor[i].set(mObjectMajorTable[i][0], mObjectMajorTable[i][1]);
   }

   // Stack object size.
   mObjectSize.mRows = gSysParms.mImageSize.mRows / mMajorSize.mRows;
   mObjectSize.mCols = gSysParms.mImageSize.mCols / mMajorSize.mCols;

   // Set stack object positioning parameters.
   for (int i = 0; i < cMaxObjects; i++)
   {
      // Stack object row column upper left corner offsets.
      mObjectOffset[i].mRow = mObjectMajor[i].mRow * mObjectSize.mRows;
      mObjectOffset[i].mCol = mObjectMajor[i].mCol * mObjectSize.mCols;

      // Stack object row column centers.
      mObjectCenter[i].mRow = mObjectOffset[i].mRow + mObjectSize.mRows / 2;
      mObjectCenter[i].mCol = mObjectOffset[i].mCol + mObjectSize.mCols / 2;

      // Stack object row column rectangles.
      mObjectRect[i].initialize(
         mObjectOffset[i].mRow, mObjectOffset[i].mRow + mObjectSize.mRows - 1,
         mObjectOffset[i].mCol, mObjectOffset[i].mCol + mObjectSize.mCols - 1);
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

   mObjectEnable.show("ObjectEnable");
   mObjectFileName.show("ObjectFileName");
   mObjectMajorTable.show("ObjectMajorTable");

   for (int i = 0; i < cMaxObjects; i++)
   {
      if (mObjectParms[i].mValid)  mObjectParms[i].show();
   }

   printf("\n");
   printf("MajorSize                %10d %4d\n", mMajorSize.mRows, mMajorSize.mCols);
   for (int i = 0; i < cMaxObjects; i++)
   {
   printf("Object1Major             %10d %4d\n", mObjectMajor[i].mRow, mObjectMajor[i].mCol);
   }

   printf("\n");
   printf("ObjectSize               %10d %4d\n", mObjectSize.mRows, mObjectSize.mCols);

   printf("\n");
   for (int i = 0; i < cMaxObjects; i++)
   {
   printf("ObjectCenter             %10d %4d\n", mObjectCenter[i].mRow, mObjectCenter[i].mCol);
   }

   printf("\n");
   for (int i = 0; i < cMaxObjects; i++)
   {
   printf("ObjectRect               %10d %4d   %4d %4d\n",
      mObjectRect[i].mARow, mObjectRect[i].mBRow, mObjectRect[i].mACol, mObjectRect[i].mBCol);
   }

   printf("\n");
   printf("TestTableSize            %10d %4d\n", mTestTable.mRows, mTestTable.mCols);
   mTestTable.show("TestTable");
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

   if (aCmd->isCmd("MajorSize"))           mMajorSize.execute(aCmd);
   if (aCmd->isCmd("ObjectMajorTable"))    nestedPush(aCmd, &mObjectMajorTable);

   if (aCmd->isCmd("TestTable"))           nestedPush(aCmd, &mTestTable);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace