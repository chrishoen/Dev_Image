/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"
#include <windows.h>

#include "risSystemCalls.h"

#include "pxFileManager.h"

namespace PX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the gcode name list from the gcode directory.

void FileManager::getGCodeNameList()
{
   mGCodeNameList.clear();
   std::string pattern = mGCodeDirPath + "\\*.gcode";
   WIN32_FIND_DATA data;
   HANDLE hFind;
   if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE)
   {
      do
      {
         mGCodeNameList.push_back(data.cFileName);
      } while (FindNextFile(hFind, &data) != 0);
      FindClose(hFind);
   }

   // Exit if the list is empty.
   if (mGCodeNameList.empty()) return;

   // Sort the list.
   std::sort(mGCodeNameList.begin(), mGCodeNameList.end());
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
//EXT   mGCodeFilePath = "./gcode/" + mGCodeName + ".gcode";
   mGCodeFilePath = "./gcode/" + mGCodeName;

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
//EXT   mGCodeFilePath = "./gcode/" + mGCodeName + ".gcode";
   mGCodeFilePath = "./gcode/" + mGCodeName;

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

   // Temp.
   int tRet;
   char tString[200];

   // Clean the work directory.
   Ris::doSystemCommand("rm -rf ./work/*");

   // Copy the gcode file into the work directory.
   // Ex. "cp ./gcode/Test100.gcode ./work"
   sprintf(tString, "cp %s ./work", mGCodeFilePath.c_str());
   tRet = Ris::doSystemCommand(tString);

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

