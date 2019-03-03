//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"
#include "svImageParms.h"
#include "svSimParms.h"
#include "svStackParms.h"

#define  _SVPARMPARMS_CPP_
#include "svParmParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

ParmParms::ParmParms()
{
   reset();
}

void ParmParms::reset()
{
   BaseClass::reset();
   BaseClass::setFileName_RelAlphaFiles("Image/SV_Parm_Parms.txt");

   mImageParmsFileName[0] = 0;
   mSimParmsFileName[0] = 0;
   mStackParmsFileName[0] = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void ParmParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void ParmParms::show()
{
   printf("\n");
   printf("ParmParms********************************************** %s\n", mTargetSection);
   printf("ImageParmsFileName                %s\n", mImageParmsFileName);
   printf("SimParmsFileName                  %s\n", mSimParmsFileName);
   printf("StackParmsFileName                %s\n", mStackParmsFileName);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void ParmParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("ImageParmsFileName"))  aCmd->copyArgString(1, mImageParmsFileName, cMaxStringSize);
   if (aCmd->isCmd("SimParmsFileName"))    aCmd->copyArgString(1, mSimParmsFileName, cMaxStringSize);
   if (aCmd->isCmd("StackParmsFileName"))  aCmd->copyArgString(1, mStackParmsFileName, cMaxStringSize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read more parms files.

void ParmParms::readMoreParms(char* aSection)
{
   // Read parameters files.
   SV::gSimParms.reset();
   SV::gSimParms.setFileName_RelAlphaFiles(mSimParmsFileName);
   SV::gSimParms.readSection(aSection);

   SV::gImageParms.reset();
   SV::gImageParms.setFileName_RelAlphaFiles(mImageParmsFileName);
   SV::gImageParms.readSection(aSection);
   SV::gImageParms.readOverrides(&SV::gSimParms);

   SV::gStackParms.reset();
   SV::gStackParms.setFileName_RelAlphaFiles(mStackParmsFileName);
   SV::gStackParms.readSection(aSection);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace