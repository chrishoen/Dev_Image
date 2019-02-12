//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svNNRuleParms.h"

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

NNRuleParms::NNRuleParms()
{
   reset();
}

void NNRuleParms::reset()
{
   mClassifyCode = 0;
   mHC1 = 0;
   mHC2 = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void NNRuleParms::show()
{
   printf("NNRuleParms*******************\n");
   printf("ClassifyCode             %10d\n", mClassifyCode);
   printf("HC1                      %10d\n", mHC1);
   printf("HC2                      %10d\n", mHC2);
   printf("NNRuleParms*******************\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void NNRuleParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("ClassifyCode"))   mClassifyCode = aCmd->argInt(1);
   if (aCmd->isCmd("HC1"))            mHC1 = aCmd->argInt(1);
   if (aCmd->isCmd("HC2"))            mHC2 = aCmd->argInt(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace