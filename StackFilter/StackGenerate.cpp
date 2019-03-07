/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "CPrintDir.h"
#include "svStackParms.h"
#include "svStackWriter.h"
#include "pxGCodeWriter.h"
#include "pxZipWriter.h"

#include "StackGenerate.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

StackGenerate::StackGenerate()
{
}

void StackGenerate::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate a stack of simulated images.

void StackGenerate::doGenerateStack()
{
   // Clean the cprint work directory.
   CPrint::doCleanWork();

   // Generate the image stack.
   SV::StackWriter tStackWriter(&SV::gStackParms);
   tStackWriter.doWriteStack();

   // Generate the stack gcode file.
   PX::GCodeWriter tGCodeWriter;
   tGCodeWriter.doWrite(SV::gStackParms.mStackName, SV::gStackParms.mStackSize);

   // Zip the work directory.
   PX::ZipWriter tZipWriter;
   tZipWriter.doZipWork(SV::gStackParms.mStackName);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
