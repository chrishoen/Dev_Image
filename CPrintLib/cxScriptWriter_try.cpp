/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cxScriptWriter.h"

namespace CX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

const std::string my_trim_whitespace = " \n\r\t\"";

std::string my_trim_left(const std::string& s)
{
   size_t startpos = s.find_first_not_of(my_trim_whitespace);
   return (startpos == std::string::npos) ? "" : s.substr(startpos);
}

std::string my_trim_right(const std::string& s)
{
   size_t endpos = s.find_last_not_of(my_trim_whitespace);
   return (endpos == std::string::npos) ? "" : s.substr(0, endpos + 1);
}

std::string my_trim_left_right(const std::string& s)
{
   size_t startpos = s.find_first_not_of(my_trim_whitespace);
   size_t endpos = s.find_last_not_of(my_trim_whitespace);
   return (endpos == std::string::npos) ? "" : s.substr(startpos, endpos - startpos + 1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// If the input gcode line is for an exit then return true.

bool ScriptWriter::tryLineFor_Exit(std::string& aInput)
{
   return aInput.substr(0, 4).compare("EXIT")==0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// If the input gcode line is for a gcode send then write the corresponding
// commands to the output script file and return true.
// G91; Ensure We're In Relative Positioning
// G1 Z100.0 F9999.0  ; lift model clear of resin

bool ScriptWriter::tryLineFor_Send(std::string& aInput)
{
   // If not a gcode string then exit.
   bool tPass = false;
   if (aInput[0] == 'G') tPass = true;
   if (aInput[0] == 'M') tPass = true;
   if (!tPass) return false;

   // Make a copy of the input.
   std::string tInput = aInput;

   // Trim the string.
   std::size_t tPos = tInput.find_first_of(";");
   if (tPos != std::string::npos)
   {
      tInput.erase(tPos, tInput.size() - tPos);
   }
   std::string tTrimmed = my_trim_right(tInput);

   // Write a script command to the output script file.
   mScriptFile << "SEND" << std::endl;
   mScriptFile << tTrimmed << std::endl;
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// If the input gcode line is for a slice then write the corresponding
// commands to the output script file and return true.
//
// Slice commands can have one of two formats: 
// ;<Slice> 0001
// ;<Slice> "1.png"

bool ScriptWriter::tryLineFor_Slice(std::string& aInput)
{
   if (aInput.substr(0, 8).compare(";<Slice>") != 0) return false;

   // Extract the slice label.
   std::string tSliceLabel = my_trim_left_right(aInput.erase(0, 8));

   // Try to convert the slice label to a number.
   char* tEndPtr = 0;
   int tSliceNumber = strtol(tSliceLabel.c_str(), &tEndPtr, 0);
   bool tIsNumber = *tEndPtr == 0;

   if (tIsNumber)
   {
      // The slice format is ;<Slice> 0001
      char tSliceFileNameEndPart[40];
      sprintf(tSliceFileNameEndPart, "%04d.png", tSliceNumber);
      // Write a script command to the output script file.
      mScriptFile << "SLICE" << std::endl;
      mScriptFile << mSliceFilePrefixPath << tSliceFileNameEndPart << std::endl;
   }
   else
   {
      // The slice format is ;<Slice> "1.png"
      char tSliceFileName[40];
      sprintf(tSliceFileName, "%s", tSliceLabel.c_str());
      // Write a script command to the output script file.
      mScriptFile << "SLICE" << std::endl;
      mScriptFile << mWorkDirPath << "/" << tSliceFileName << std::endl;
   }

   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// If the input gcode line is for a state then write the corresponding
// commands to the output script file and return true.

bool ScriptWriter::tryLineFor_PWM(std::string& aInput)
{
   if (aInput.substr(0, 6).compare(";<PWM>") != 0) return false;

   // Make a copy of the input.
   std::string tInput = aInput;

   // Erase the begining.
   tInput.erase(0, 6);

   // Extract the state value.
   int tValue = std::stoi(tInput);
   char tTemp[40];
   sprintf(tTemp, "%04d", tValue);

   // Write a script command to the output script file.
   mScriptFile << "PWM" << std::endl;
   mScriptFile << tTemp << std::endl;
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// If the input gcode line is for a state then write the corresponding
// commands to the output script file and return true.

bool ScriptWriter::tryLineFor_Test(std::string& aInput)
{
   if (aInput.substr(0, 7).compare(";<Test>") != 0) return false;

   // Make a copy of the input.
   std::string tInput = aInput;

   // Erase the begining.
   tInput.erase(0, 7);

   // Extract the command argument.
   int tValue = 0;
   if (tInput.length() > 1)  tValue = std::stoi(tInput);
   char tTemp[40];
   sprintf(tTemp, "%04d", tValue);

   // Write a script command to the output script file.
   mScriptFile << "TEST" << std::endl;
   mScriptFile << tTemp << std::endl;
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// If the input gcode line is for a state then write the corresponding
// commands to the output script file and return true.

bool ScriptWriter::tryLineFor_State1 (std::string& aInput)
{
   if (aInput.substr(0, 9).compare(";<State1>") != 0) return false;

   // Make a copy of the input.
   std::string tInput = aInput;

   // Erase the begining.
   tInput.erase(0, 9);

   // Extract the command argument.
   int tValue = -1;
   if (tInput.length() > 1)  tValue = std::stoi(tInput);
   char tTemp[40];
   sprintf(tTemp, "%04d", tValue);

   // Write a script command to the output script file.
   mScriptFile << "STATE1" << std::endl;
   mScriptFile << tTemp << std::endl;
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// If the input gcode line is for a state then write the corresponding
// commands to the output script file and return true.

bool ScriptWriter::tryLineFor_State2(std::string& aInput)
{
   if (aInput.substr(0, 9).compare(";<State2>") != 0) return false;

   // Make a copy of the input.
   std::string tInput = aInput;

   // Erase the begining.
   tInput.erase(0, 9);

   // Extract the command argument.
   int tValue = -1;
   if (tInput.length() > 1)  tValue = std::stoi(tInput);
   char tTemp[40];
   sprintf(tTemp, "%04d", tValue);

   // Write a script command to the output script file.
   mScriptFile << "STATE2" << std::endl;
   mScriptFile << tTemp << std::endl;
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// If the input gcode line is for a state then write the corresponding
// commands to the output script file and return true.

bool ScriptWriter::tryLineFor_State3(std::string& aInput)
{
   if (aInput.substr(0, 9).compare(";<State3>") != 0) return false;

   // Make a copy of the input.
   std::string tInput = aInput;

   // Erase the begining.
   tInput.erase(0, 9);

   // Extract the command argument.
   int tValue = -1;
   if (tInput.length() > 1)  tValue = std::stoi(tInput);
   char tTemp[40];
   sprintf(tTemp, "%04d", tValue);

   // Write a script command to the output script file.
   mScriptFile << "STATE3" << std::endl;
   mScriptFile << tTemp << std::endl;
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// If the input gcode line is for info then write the corresponding
// commands to the output script file and return true.

bool ScriptWriter::tryLineFor_Info(std::string& aInput)
{
   bool tPass = false;
   if (aInput.substr(0, 8).compare(";*******") == 0) tPass = true;
   if (aInput.substr(0,12).compare(";<Completed>") == 0) tPass = true;
   if (!tPass) return false;

   // Make a copy of the input.
   std::string tInput = aInput;

   // Erase the begining.
   tInput.erase(0, 1);

   // Write a script command to the output script file.
   mScriptFile << "INFO" << std::endl;
   mScriptFile << tInput << std::endl;
   return true;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

