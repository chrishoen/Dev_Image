/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risSystemCalls.h"
#include "CPrintDir.h"

#include "cxFileManager.h"

namespace CX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the gcode name list from the gcode directory.

void FileManager::getGCodeNameList()
{
   CPrint::getGCodeNameList(mGCodeDirPath, mGCodeNameList);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the gcode name list from the gcode directory.

void FileManager::showGCodeNameList()
{
   for (int i = 0; i < mGCodeNameList.size(); i++)
   {
      Prn::print(0, "%3d %s", i, mGCodeNameList[i].c_str());
   }
   Prn::print(0, "done");
   Prn::print(0, "");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Select a gcode name from the gcode name list. Return true if successful.

bool FileManager::setGCodeName(int aGCodeNum)
{
   // Do this first.
   mGCodeName.clear();
   mGCodeFilePath.clear();

   // Guard.
   if (mGCodeNameList.empty())
   {
      mError = "ERROR GCode name list does not exist";
      Prn::print(0, mError.c_str());
      return false;
   }

   // Guard.
   if (aGCodeNum <0 || aGCodeNum >= mGCodeNameList.size())
   {
      mError = "ERROR GCode number out of bounds";
      Prn::print(0, mError.c_str());
      mGCodeName = "NULL";
      mGCodeFilePath = "NULL FILE";
      return false;
   }

   // Set gcode name and file path.
   mGCodeName = mGCodeNameList[aGCodeNum];
   mGCodeFilePath = mGCodeDirPath + mGCodeName;

   // Test if the gcode file exists.
   if (!exists(mGCodeFilePath))
   {
      mError = "ERROR GCode File does not exist " + mGCodeFilePath;
      Prn::print(0, mError.c_str());
      mGCodeName.clear();
      mGCodeFilePath.clear();
      return false;
   }

   // Done.
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set the gcode name. Return true if successful.

bool FileManager::setGCodeName(const char* aGCodeName)
{
   // Set gcode name and file path.
   mGCodeName = aGCodeName;
   mGCodeFilePath = mGCodeDirPath + mGCodeName;

   // Test if the gcode file exists.
   if (!exists(mGCodeFilePath))
   {
      mError = "ERROR GCode File does not exist " + mGCodeFilePath;
      Prn::print(0, mError.c_str());
      mGCodeName.clear();
      mGCodeFilePath.clear();
      return false;
   }

   // Done.
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Ungcode the gcode file from the gcode directory into the work directory.
// Return true if successful.

bool FileManager::doLoadGCode(int aGCodeNum)
{
   mError.clear();
   // Try to set the gcode name.
   if (!setGCodeName(aGCodeNum)) return false;

   // Load the gcode.
   return doLoadGCode();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Ungcode the gcode file from the gcode directory into the work directory.
// Return true if successful.

bool FileManager::doLoadGCode(const char* aGCodeName)
{
   mError.clear();
   // Try to set the gcode name.
   if (!setGCodeName(aGCodeName)) return false;

   // Load the gcode.
   return doLoadGCode();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Ungcode the gcode file from the gcode directory into the work directory.
// Return true if successful.

bool FileManager::doLoadGCode()
{
   // Guard.
   if (!exists(mGCodeFilePath))
   {
      mError = "ERROR GCode File does not exist " + mGCodeFilePath;
      Prn::print(0, mError.c_str());
      return false;
   }

   // Clean the work directory.
   CPrint::doCleanWork();

   // Copy the gcode file into the work directory.
   CPrint::doCopyToWork(mGCodeFilePath);

   // Done.
   mError = "PASS";
   Prn::print(0, "done");
   Prn::print(0, "");
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

