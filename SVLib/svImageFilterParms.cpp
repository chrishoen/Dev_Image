//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svDefs.h"
#include "svSysParms.h"

#define  _SVIMAGEFILTERPARMS_CPP_
#include "svImageFilterParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

ImageFilterParms::ImageFilterParms()
{
   reset();
}

void ImageFilterParms::reset()
{
   mFilterType    = cNone;
   mGaussBlurCode = 0;
   mClassifyCode = 0;
   mClassifyTable1.reset();
   mClassifyTable2.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void ImageFilterParms::show()
{
   printf("ImageFilterParms*******************\n");
   printf("FilterType               %10s\n", asStringFilterType(mFilterType));
   printf("GaussBlurCode            %10d\n", mGaussBlurCode);
   printf("ClassifyCode             %10d\n", mClassifyCode);
   if (mClassifyTable1.mRows != 0)
   {
      printf("ClassifyTable1\n");
      for (int i = 0; i < 8;i++)
      {
         printf("%3d ", mClassifyTable1[0][i]);
      }
      printf("\n");
      for (int i = 0; i < 8; i++)
      {
         printf("%3d ", mClassifyTable1[1][i]);
      }
      printf("\n");
   }
   if (mClassifyTable2.mRows != 0)
   {
      printf("ClassifyTable2\n");
      for (int i = 0; i < 8; i++)
      {
         printf("%3d ", mClassifyTable2[0][i]);
      }
      printf("\n");
      for (int i = 0; i < 8; i++)
      {
         printf("%3d ", mClassifyTable2[1][i]);
      }
      printf("\n");
   }
   printf("ImageFilterParms*******************\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void ImageFilterParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("FilterType"))
   {
      if (aCmd->isArgString(1, asStringFilterType(cNone)))              mFilterType = cNone;
      if (aCmd->isArgString(1, asStringFilterType(cFilterGaussBlur)))   mFilterType = cFilterGaussBlur;
      if (aCmd->isArgString(1, asStringFilterType(cFilterClassify)))    mFilterType = cFilterClassify;
   }

   if (aCmd->isCmd("GaussBlurCode"))      mGaussBlurCode = aCmd->argInt(1);
   if (aCmd->isCmd("ClassifyCode"))       mClassifyCode = aCmd->argInt(1);

   if (aCmd->isCmd("ClassifyTable1"))     nestedPush(aCmd, &mClassifyTable1);
   if (aCmd->isCmd("ClassifyTable2"))     nestedPush(aCmd, &mClassifyTable2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

char* ImageFilterParms::asStringFilterType(int aX)
{
   switch (aX)
   {
   case cNone                : return "None";
   case cFilterGaussBlur     : return "GaussBlur";
   case cFilterClassify      : return "Classify";
   default : return "UNKNOWN";
   }
}

char* ImageFilterParms::asStringFilterType()
{
   return asStringFilterType(mFilterType);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace