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

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate a synthetic gcode file from the prototype files.

void GCodeWriter::doWrite(
   const std::string& aGCodeName,
   int aRepeatCount)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // File paths.

   mInputBeginFilePath  = CPrint::getSpecialDirPath() + "gcode_begin.txt";
   mInputRepeatFilePath = CPrint::getSpecialDirPath() + "gcode_repeat.txt";
   mInputEndFilePath    = CPrint::getSpecialDirPath() + "gcode_end.txt";
   mOutputGCodeFilePath = CPrint::getWorkDirPath() + aGCodeName + ".gcode";

   std::cout << "InputBeginFilePath   " << mInputBeginFilePath << std::endl;
   std::cout << "InputRepeatFilePath  " << mInputRepeatFilePath << std::endl;
   std::cout << "InputEndFilePath     " << mInputEndFilePath << std::endl;
   std::cout << "OutputGCodeFilePath  " << mOutputGCodeFilePath << std::endl;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Open files.

   mInputBeginFile.open(mInputBeginFilePath.c_str(), std::ios::in);
   mInputRepeatFile.open(mInputRepeatFilePath.c_str(), std::ios::in);
   mInputEndFile.open(mInputEndFilePath.c_str(), std::ios::in);
   mOutputGCodeFile.open(mOutputGCodeFilePath.c_str(), std::ios::out | std::ios::trunc);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Copy file.

   while (true)
   {
      // Read an input line from the input file.
      std::string tLine;
      std::getline(mInputBeginFile, tLine);

      // Exit if end of file.
      if (mInputBeginFile.eof()) break;

      // Write to the output file.
      mOutputGCodeFile << tLine << std::endl;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Repeat copy file.

   for (int tSliceIndex = 0; tSliceIndex < aRepeatCount; tSliceIndex++)
   {
      // Write slice gcode.
      mOutputGCodeFile << "; *********** START LAYER" << std::endl;
      mOutputGCodeFile << ";<Slice> " << tSliceIndex << std::endl;

      // Copy file.
      mInputRepeatFile.clear();
      mInputRepeatFile.seekg(0, std::ios::beg);
      while (true)
      {
         // Read an input line from the input file.
         std::string tLine;
         std::getline(mInputRepeatFile, tLine);

         // Exit if end of file.
         if (mInputRepeatFile.eof()) break;

         // Write to the output file.
         mOutputGCodeFile << tLine << std::endl;
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Copy file.

   while (true)
   {
      // Read an input line from the input file.
      std::string tLine;
      std::getline(mInputEndFile, tLine);

      // Exit if end of file.
      if (mInputEndFile.eof()) break;

      // Write to the output file.
      mOutputGCodeFile << tLine << std::endl;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Close files.

   mInputBeginFile.close();
   mInputRepeatFile.close();
   mInputEndFile.close();
   mInputEndFile.close();
   mOutputGCodeFile.close();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate a synthetic gcode file from the prototype files.

void GCodeWriter::doWrite(
   const char* aGCodeFileName,
   int aRepeatCount)
{
   doWrite(std::string(aGCodeFileName), aRepeatCount);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

