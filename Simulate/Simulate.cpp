/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "CPrintDir.h"
#include "svSysParms.h"
#include "svImageParms.h"
#include "svSimParms.h"
#include "svParmParms.h"
#include "svSimStackGenerator.h"
#include "pxGCodeWriter.h"
#include "pxZipWriter.h"

#include "Simulate.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

Simulate::Simulate()
{
}

void Simulate::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This simulates an input image stack.

void Simulate::doSimStack()
{
   // Clean the cprint work directory.
   CPrint::doCleanWork();

   // Generate the image stack.
   SV::SimStackGenerator tStackGen(&SV::gSimParms);
   tStackGen.doGenerateImageStack();

   // Generate the stack gcode file.
   PX::GCodeWriter tGCodeWriter;
   tGCodeWriter.doWrite(SV::gSimParms.mStackName,SV::gSimParms.mStackSize);

   // Generate the stack gcode file.
   PX::ZipWriter tZipWriter;
   tZipWriter.doZipWork(SV::gSimParms.mStackName,0);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
