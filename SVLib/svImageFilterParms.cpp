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
   mCharacterCode = 0;
   mCharacterTable.reset();
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
   printf("CharacterCode            %10d\n", mCharacterCode);
   if (mCharacterTable.mRows != 0)
   {
      printf("CharacterTable\n");
      for (int i = 0; i < 8;i++)
      {
         printf("%3d ", mCharacterTable[0][i]);
      }
      printf("\n");
      for (int i = 0; i < 8; i++)
      {
         printf("%3d ", mCharacterTable[1][i]);
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
      if (aCmd->isArgString(1, asStringFilterType(cFilterCharacter)))   mFilterType = cFilterCharacter;
   }

   if (aCmd->isCmd("GaussBlurCode"))       mGaussBlurCode = aCmd->argInt(1);
   if (aCmd->isCmd("CharacterCode"))       mCharacterCode = aCmd->argInt(1);

   if (aCmd->isCmd("CharacterTable"))      nestedPush(aCmd, &mCharacterTable);
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
   case cFilterCharacter     : return "Character";
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