/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "CPrintDir.h"
#include "pxGCodeWriter.h"

namespace PX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

GCodeWriter::GCodeWriter()
{
}
#if 0
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate a synthetic gcode file from the prototype files.

void GCodeWriter::doGenerate(
   const std::string& aGCodeFileName,
   int aRepeatCount)
{
   // Input file path.
   mInputBeginFilePath = ;
   mInputRepeatFilePath;
   mInputEndFilePath;

   // Output file path.
   std::string mOutputGCodeFilePath;

   mGCodeFilePath =
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Open the files.

bool GCodeWriter::doOpenFiles(
   const std::string& aGCodeFilePath,
   const std::string& aScriptFilePath)
{
   mGCodeFile.open(aGCodeFilePath.c_str(), std::ios::in);
   if (!mGCodeFile.is_open())
   {
      std::cout << "ERROR gcode file open fail" << aGCodeFilePath <<std::endl;
      return false;
   }

   mScriptFile.open(aScriptFilePath.c_str(), std::ios::out | std::ios::trunc);
   if (!mScriptFile.is_open())
   {
      std::cout << "ERROR script file open fail" << aScriptFilePath << std::endl;
      return false;
   }

   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Close the files.

void GCodeWriter::doCloseFiles()
{
   mGCodeFile.close();
   mScriptFile.close();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read from the gcode file. Write to the script file. For each input line
// from the gcode file, write a corresponding set of script file output
// lines. Return true if successful.

bool GCodeWriter::doWrite(
   const std::string& aGCodeFilePath,           // Input
   const std::string& aSliceFilePrefixPath,     // Input
   const std::string& aWorkDirPath,             // Input
   const std::string& aScriptFilePath)          // Output
{
   // Store this.
   mSliceFilePrefixPath = aSliceFilePrefixPath;
   mWorkDirPath = aWorkDirPath;

   // Open the input and output files.
   if (!doOpenFiles(aGCodeFilePath, aScriptFilePath)) return false;

   // Execute a loop that reads lines from the input gcode file and writes 
   // commands to the script output file.
   while (true)
   {
      // Read an input line from the gcode file.
      std::string tGCodeLine;
      std::getline(mGCodeFile, tGCodeLine);

      // Exit if end of file.
      if (mGCodeFile.eof()) break;

      // Try to process the input line. Each tryForLine method tests the input
      // line and, if appropriate, writes commands to the output file.
      if (tryLineFor_Exit(tGCodeLine)) break;
      else if (tryLineFor_Send(tGCodeLine)) continue;
      else if (tryLineFor_Slice(tGCodeLine)) continue;
      else if (tryLineFor_PWM(tGCodeLine)) continue;
      else if (tryLineFor_Test(tGCodeLine)) continue;
      else if (tryLineFor_State1(tGCodeLine)) continue;
      else if (tryLineFor_State2(tGCodeLine)) continue;
      else if (tryLineFor_State3(tGCodeLine)) continue;
      else if (tryLineFor_Info(tGCodeLine)) continue;
   }

   // Close the files.
   doCloseFiles();

   // Done.
   std::cout << "done" << std::endl;
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
#endif
}//namespace

