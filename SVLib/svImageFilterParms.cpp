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
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void ImageFilterParms::show()
{
   printf("\n");
   printf("ImageFilterParms*******************************************\n");
   printf("FilterType               %10s\n", asStringFilterType(mFilterType));
   printf("GaussBlurCode            %10d\n", mGaussBlurCode);
   printf("ImageFilterParms*******************************************\n");
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
      if (aCmd->isArgString(1, asStringFilterType(cFilterSquare)))      mFilterType = cFilterSquare;
   }

   if (aCmd->isCmd("GaussBlurCode"))       mGaussBlurCode = aCmd->argInt(1);
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
   case cFilterSquare        : return "Square";
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