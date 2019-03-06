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

   mObjectFileName1[0];
   mObjectFileName2[0];
   mObjectFileName3[0];
   mObjectFileName4[0];

   mMajorSize.reset();
   mObject1Major.reset();
   mObject2Major.reset();
   mObject3Major.reset();
   mObject4Major.reset();

   mObjectParms1.reset();
   mObjectParms2.reset();
   mObjectParms3.reset();
   mObjectParms4.reset();

   mObjectSize.reset();
   mObject1Center.reset();
   mObject2Center.reset();
   mObject3Center.reset();
   mObject4Center.reset();

   mObject1Rect.reset();
   mObject2Rect.reset();
   mObject3Rect.reset();
   mObject4Rect.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void StackParms::expand()
{
   // Stack objects.
   if (strlen(mObjectFileName1) != 0)
   {
      mObjectParms1.setFileName_RelAlphaFiles(mObjectFileName1);
      mObjectParms1.readSection("default");
      mObjectParms1.mValid = true;
   }

   // Stack object row column roi size.
   // Stack object row column upper left corner offsets.
   RCIndex tObject1Offset;
   RCIndex tObject2Offset;
   RCIndex tObject3Offset;
   RCIndex tObject4Offset;

   // Stack object size.
   mObjectSize.mRows = gSysParms.mImageSize.mRows / mMajorSize.mRows;
   mObjectSize.mCols = gSysParms.mImageSize.mCols / mMajorSize.mCols;

   // Stack object row column upper left corner offsets.
   tObject1Offset.mRow = mObject1Major.mRow * mObjectSize.mRows;
   tObject1Offset.mCol = mObject1Major.mCol * mObjectSize.mCols;

   tObject2Offset.mRow = mObject2Major.mRow * mObjectSize.mRows;
   tObject2Offset.mCol = mObject2Major.mCol * mObjectSize.mCols;

   tObject3Offset.mRow = mObject3Major.mRow * mObjectSize.mRows;
   tObject3Offset.mCol = mObject3Major.mCol * mObjectSize.mCols;

   tObject4Offset.mRow = mObject4Major.mRow * mObjectSize.mRows;
   tObject4Offset.mCol = mObject4Major.mCol * mObjectSize.mCols;

   // Stack object row column centers.
   mObject1Center.mRow = tObject1Offset.mRow + mObjectSize.mRows / 2;
   mObject1Center.mCol = tObject1Offset.mCol + mObjectSize.mCols / 2;

   mObject2Center.mRow = tObject2Offset.mRow + mObjectSize.mRows / 2;
   mObject2Center.mCol = tObject2Offset.mCol + mObjectSize.mCols / 2;

   mObject3Center.mRow = tObject3Offset.mRow + mObjectSize.mRows / 2;
   mObject3Center.mCol = tObject3Offset.mCol + mObjectSize.mCols / 2;

   mObject4Center.mRow = tObject4Offset.mRow + mObjectSize.mRows / 2;
   mObject4Center.mCol = tObject4Offset.mCol + mObjectSize.mCols / 2;


   // Stack object row column rectangles.
   mObject1Rect.initialize(
      tObject1Offset.mRow, tObject1Offset.mRow + mObjectSize.mRows - 1,
      tObject1Offset.mCol, tObject1Offset.mCol + mObjectSize.mCols - 1);

   mObject2Rect.initialize(
      tObject2Offset.mRow, tObject2Offset.mRow + mObjectSize.mRows - 1,
      tObject2Offset.mCol, tObject2Offset.mCol + mObjectSize.mCols - 1);

   mObject3Rect.initialize(
      tObject3Offset.mRow, tObject3Offset.mRow + mObjectSize.mRows - 1,
      tObject3Offset.mCol, tObject3Offset.mCol + mObjectSize.mCols - 1);

   mObject4Rect.initialize(
      tObject4Offset.mRow, tObject4Offset.mRow + mObjectSize.mRows - 1,
      tObject4Offset.mCol, tObject4Offset.mCol + mObjectSize.mCols - 1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void StackParms::show()
{
   printf("\n");
   printf("StackParms************************************************ %s\n", mTargetSection);

   if (mObjectParms1.mValid)  mObjectParms1.show();
   if (mObjectParms2.mValid)  mObjectParms2.show();
   if (mObjectParms3.mValid)  mObjectParms3.show();
   if (mObjectParms4.mValid)  mObjectParms4.show();

   printf("ObjectFileName1   %s\n", mObjectFileName1);
   printf("ObjectFileName2   %s\n", mObjectFileName2);
   printf("ObjectFileName3   %s\n", mObjectFileName3);
   printf("ObjectFileName4   %s\n", mObjectFileName4);

   printf("\n");
   printf("MajorSize                %10d %4d\n", mMajorSize.mRows, mMajorSize.mCols);
   printf("Object1Major             %10d %4d\n", mObject1Major.mRow, mObject1Major.mCol);
   printf("Object2Major             %10d %4d\n", mObject2Major.mRow, mObject1Major.mCol);
   printf("Object3Major             %10d %4d\n", mObject3Major.mRow, mObject1Major.mCol);
   printf("Object4Major             %10d %4d\n", mObject4Major.mRow, mObject1Major.mCol);

   printf("\n");
   printf("ObjectSize               %10d %4d\n", mObjectSize.mRows, mObjectSize.mCols);

   printf("\n");
   printf("Object1Center            %10d %4d\n", mObject1Center.mRow, mObject1Center.mCol);
   printf("Object2Center            %10d %4d\n", mObject2Center.mRow, mObject2Center.mCol);
   printf("Object3Center            %10d %4d\n", mObject3Center.mRow, mObject3Center.mCol);
   printf("Object4Center            %10d %4d\n", mObject4Center.mRow, mObject4Center.mCol);

   printf("\n");
   printf("Object1Rect              %10d %4d   %4d %4d\n",
      mObject1Rect.mARow, mObject1Rect.mBRow, mObject1Rect.mACol, mObject1Rect.mBCol);
   printf("Object2Rect              %10d %4d   %4d %4d\n",
      mObject2Rect.mARow, mObject2Rect.mBRow, mObject2Rect.mACol, mObject2Rect.mBCol);
   printf("Object3Rect              %10d %4d   %4d %4d\n",
      mObject3Rect.mARow, mObject3Rect.mBRow, mObject3Rect.mACol, mObject3Rect.mBCol);
   printf("Object4Rect              %10d %4d   %4d %4d\n",
      mObject4Rect.mARow, mObject4Rect.mBRow, mObject4Rect.mACol, mObject4Rect.mBCol);
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

   if (aCmd->isCmd("ObjectFileName1"))      aCmd->copyArgString(1, mObjectFileName1, cMaxStringSize);
   if (aCmd->isCmd("ObjectFileName2"))      aCmd->copyArgString(1, mObjectFileName2, cMaxStringSize);
   if (aCmd->isCmd("ObjectFileName3"))      aCmd->copyArgString(1, mObjectFileName3, cMaxStringSize);
   if (aCmd->isCmd("ObjectFileName4"))      aCmd->copyArgString(1, mObjectFileName4, cMaxStringSize);

   if (aCmd->isCmd("MajorSize"))            mMajorSize.execute(aCmd);
   if (aCmd->isCmd("Object1Major"))         mObject1Major.execute(aCmd);
   if (aCmd->isCmd("Object2Major"))         mObject2Major.execute(aCmd);
   if (aCmd->isCmd("Object3Major"))         mObject3Major.execute(aCmd);
   if (aCmd->isCmd("Object4Major"))         mObject4Major.execute(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace