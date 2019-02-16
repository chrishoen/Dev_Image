/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "pxScriptReader.h"

namespace PX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

ScriptReader::ScriptReader()
{
   mFile = 0;
   mCmdCode = 0;
   mString[0] = 0;
   mStringLength = 0;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Open the files.

bool ScriptReader::doOpenFile(std::string& aScriptFilePath)
{
   // Open the log file.
   mFile = fopen(aScriptFilePath.c_str(), "r");

   if (mFile == 0)
   {
      Prn::print(0, "ERROR ScriptReader file open FAIL %d", aScriptFilePath);
      return false;
   }
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Close the files.

void ScriptReader::doCloseFile()
{
   if (mFile) fclose(mFile);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read two lines from the script file. The first line is a command and
// the second line is a string that is associated with the command.
// Set the corresponding member variables. Return true if successful.
// Return false if end of file.

bool ScriptReader::doRead()
{
   // Do this first.
   mCmdCode = cScriptCmd_None;
   mString[0] = 0;
   mStringLength = 0;

   // Guard.
   if (mFile == 0) return false;
   if (feof(mFile)) return false;

   // Locals.
   char* tRet = 0;
   int tLength = 0;

   // Read the first line.
   tRet = fgets(mString, cMaxStringSize, mFile);
   if (tRet == 0) return false;

   // Trim the end of the string.
   tLength = (int)strlen(mString);
   if (tLength) mString[tLength - 1] = 0;

   // Decode the command.
   mCmdCode = cScriptCmd_Error;
   if (strcmp(mString, "SEND") == 0)    mCmdCode = cScriptCmd_Send;
   if (strcmp(mString, "SLICE") == 0)   mCmdCode = cScriptCmd_Slice;
   if (strcmp(mString, "PWM") == 0)     mCmdCode = cScriptCmd_PWM;
   if (strcmp(mString, "TEST") == 0)    mCmdCode = cScriptCmd_Test;
   if (strcmp(mString, "STATE1") == 0)  mCmdCode = cScriptCmd_State1;
   if (strcmp(mString, "STATE2") == 0)  mCmdCode = cScriptCmd_State2;
   if (strcmp(mString, "STATE3") == 0)  mCmdCode = cScriptCmd_State3;
   if (strcmp(mString, "INFO") == 0)    mCmdCode = cScriptCmd_Info;
   if (mCmdCode == cScriptCmd_Error)    return false;

   // Read the second line.
   tRet = fgets(mString, cMaxStringSize, mFile);
   if (tRet == 0) return false;

   // Trim the end of the string.
   tLength = (int)strlen(mString);
   if (tLength) mString[tLength - 1] = 0;
   mStringLength = tLength - 1;

   // Done.
   return true;
}
//Prn::print(0, "Read string1 %3d %s", strlen(mString), mString);

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

