//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"

#define  _SOMEIMAGEPARMS_CPP_
#include "someImageParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

ImageParms::ImageParms()
{
   reset();
}

void ImageParms::reset()
{
   BaseClass::reset();
   BaseClass::setFileName_RelAlphaFiles("Image/Image_Parms.txt");


   mImageFilename[0] = 0;

   mImageWidth = 0;
   mImageHeight = 0;

   mForeColor[0] = 0;
   mForeColor[1] = 0;
   mForeColor[2] = 0;

   mBackColor[0] = 0;
   mBackColor[1] = 0;
   mBackColor[2] = 0;

   mSideX = 0;
   mSideY = 0;
   mImageBorder = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void ImageParms::show()
{
   printf("\n");
   printf("ImageParms************************************************ %s\n", mTargetSection);

   printf("\n");
   printf("ImageFilename         %-10s\n", mImageFilename);

   printf("\n");
   printf("ImageWidthHeight      %-4d %4d\n", mImageWidth, mImageHeight);

   printf("\n");
   printf("ForeColor             %-4d %4d %4d\n", mForeColor[0], mForeColor[1], mForeColor[2]);
   printf("BackColor             %-4d %4d %4d\n", mBackColor[0], mBackColor[1], mBackColor[2]);

   printf("\n");
   printf("SideX                 %-4d\n", mSideX);
   printf("sideY                 %-4d\n", mSideY);
   printf("ImageBorder           %-4s\n", my_string_from_bool(mImageBorder));
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void ImageParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("ImageFilename"))  aCmd->copyArgString(1, mImageFilename, cMaxStringSize);

   if (aCmd->isCmd("ImageWidthHeight"))
   {
      mImageWidth = aCmd->argInt(1);
      mImageHeight = aCmd->argInt(2);
   }

   if (aCmd->isCmd("ForeColor"))
   {
      mForeColor[0] = aCmd->argInt(1);
      mForeColor[1] = aCmd->argInt(2);
      mForeColor[2] = aCmd->argInt(3);
   }

   if (aCmd->isCmd("BackColor"))
   {
      mBackColor[0] = aCmd->argInt(1);
      mBackColor[1] = aCmd->argInt(2);
      mBackColor[2] = aCmd->argInt(3);
   }

   if (aCmd->isCmd("SideX"))        mSideX = aCmd->argInt(1);
   if (aCmd->isCmd("SideY"))        mSideY = aCmd->argInt(1);
   if (aCmd->isCmd("ImageBorder"))  mImageBorder = aCmd->argBool(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void ImageParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace