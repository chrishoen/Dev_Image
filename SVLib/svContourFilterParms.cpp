//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svDefs.h"
#include "svSysParms.h"

#include "svContourFilterParms.h"

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

ContourFilterParms::ContourFilterParms()
{
   reset();
}

void ContourFilterParms::reset()
{
   mClassifyCode = 0;
   mClassifyTable1.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void ContourFilterParms::show()
{
   printf("ContourFilterParms*******************\n");
   printf("ClassifyCode             %10d\n",   mClassifyCode);
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
   printf("ContourFilterParms*******************\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void ContourFilterParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("ClassifyCode"))       mClassifyCode = aCmd->argInt(1);
   if (aCmd->isCmd("ClassifyTable1"))     nestedPush(aCmd, &mClassifyTable1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace