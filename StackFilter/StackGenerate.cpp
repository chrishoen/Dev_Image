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
#include "cxGCodeWriter.h"
#include "cxZipWriter.h"

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
   CX::GCodeWriter tGCodeWriter;
   tGCodeWriter.doWrite(SV::gStackParms.mStackName, SV::gStackParms.mStackHeight);

   // Zip the work directory.
   CX::ZipWriter tZipWriter;
   tZipWriter.doZipWork(SV::gStackParms.mStackName);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
