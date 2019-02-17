#pragma once
/*==============================================================================
printer executive - script file reader.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string>

namespace PX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants.

// script file command codes.
static const int cScriptCmd_None   = 0;
static const int cScriptCmd_Send   = 1;
static const int cScriptCmd_Slice  = 2;
static const int cScriptCmd_PWM    = 3;
static const int cScriptCmd_Test   = 4;
static const int cScriptCmd_State1 = 5;
static const int cScriptCmd_State2 = 6;
static const int cScriptCmd_State3 = 7;
static const int cScriptCmd_Info   = 8;
static const int cScriptCmd_Error  = 9;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encalsulates a script file reader. It reads inputs from
// a script file and provides commands to the print sequencer thread.

class ScriptReader
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static const std::streamsize cMaxStringSize = 200;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // File descriptors.
   FILE* mFile;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // After a read call from the script file (which reads two lines), these
   // contain the command code and string for the script command.
   int mCmdCode;
   char mString[cMaxStringSize];
   int mStringLength;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   ScriptReader();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Open the files. Return true if successful.
   bool doOpenFile(std::string& aScriptFilePath);

   // Close the files.
   void doCloseFile();

   // Read two lines from the script file. The first line is a command and
   // the second line is a string that is associated with the command.
   // Set the corresponding member variables. Return true if successful.
   // Return false if end of file.
   bool doRead();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



