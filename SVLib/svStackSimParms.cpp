//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"

#define  _SVSTACKSIMPARMS_CPP_
#include "svStackSimParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

StackSimParms::StackSimParms()
{
   reset();
}

void StackSimParms::reset()
{
   BaseClass::reset();
   BaseClass::setFileName_RelAlphaFiles("Image/SV_StackSim_Parms.txt");

   mObjectFileName1[0];
   mObjectFileName2[0];
   mObjectFileName3[0];
   mObjectFileName4[0];

   mMajorSize.reset();
   mObject1Major.reset();
   mObject2Major.reset();
   mObject3Major.reset();
   mObject4Major.reset();
   mObjectSize.reset();
   mObject1Offset.reset();
   mObject2Offset.reset();
   mObject3Offset.reset();
   mObject4Offset.reset();

   mObjectParms1.reset();
   mObjectParms2.reset();
   mObjectParms3.reset();
   mObjectParms4.reset();


}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void StackSimParms::expand()
{
   // Stack objects.
   if (strlen(mObjectFileName1) != 0)
   {
      mObjectParms1.setFileName_RelAlphaFiles(mObjectFileName1);
      mObjectParms1.readSection("default");
      mObjectParms1.mValid = true;
   }


   // Stack object row column roi size.
   mObjectSize.mRows = gSysParms.mImageSize.mRows;
   mObjectSize.mCols = gSysParms.mImageSize.mCols;
   if (mMajorSize.mRows != 0)
   {
      mObjectSize.mRows = gSysParms.mImageSize.mRows / mMajorSize.mRows;
      mObjectSize.mCols = gSysParms.mImageSize.mCols / mMajorSize.mCols;
   }

   // Stack object row column upper left corner offsets.
   mObject1Offset.mRow = mObject1Major.mRow * mObjectSize.mRows;
   mObject1Offset.mCol = mObject1Major.mCol * mObjectSize.mCols;

   mObject2Offset.mRow = mObject2Major.mRow * mObjectSize.mRows;
   mObject2Offset.mCol = mObject2Major.mCol * mObjectSize.mCols;

   mObject3Offset.mRow = mObject3Major.mRow * mObjectSize.mRows;
   mObject3Offset.mCol = mObject3Major.mCol * mObjectSize.mCols;

   mObject4Offset.mRow = mObject4Major.mRow * mObjectSize.mRows;
   mObject4Offset.mCol = mObject4Major.mCol * mObjectSize.mCols;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void StackSimParms::show()
{
   printf("\n");
   printf("StackSimParms************************************************ %s\n", mTargetSection);

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
   printf("Object1Offset            %10d %4d\n", mObject1Offset.mRow, mObject1Offset.mCol);
   printf("Object2Offset            %10d %4d\n", mObject2Offset.mRow, mObject2Offset.mCol);
   printf("Object3Offset            %10d %4d\n", mObject3Offset.mRow, mObject3Offset.mCol);
   printf("Object4Offset            %10d %4d\n", mObject4Offset.mRow, mObject4Offset.mCol);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void StackSimParms::execute(Ris::CmdLineCmd* aCmd)
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