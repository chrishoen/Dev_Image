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
// Find the name of the gcode file in the work directory, no file 
// extension.

bool FileManager::doFindWorkGCodeName()
{
   mWorkGCodeName.clear();
   std::string pattern = mWorkDirPath + "\\*.gcode";
   WIN32_FIND_DATA data;
   HANDLE hFind;
   if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE)
   {
      do
      {
         mWorkGCodeName = data.cFileName;
      } while (FindNextFile(hFind, &data) != 0);
      FindClose(hFind);
   }

   // Guard.
   if (mWorkGCodeName.empty())
   {
      mError = "ERROR gcode file does not exist";
      Prn::print(0, mError.c_str());
      mWorkGCodeName = "NULL";
      return false;
   }

//EXT mWorkGCodeFilePath = "./work/" + mWorkGCodeName + ".gcode";
   mWorkGCodeFilePath = "./work/" + mWorkGCodeName;

   mWorkSliceFilePrefixPath = "./work/" + mWorkGCodeName;
   std::size_t tErasePos = mWorkSliceFilePrefixPath.find_last_of(".");
   std::size_t tEraseLength = mWorkSliceFilePrefixPath.size() - tErasePos;
   mWorkSliceFilePrefixPath.erase(tErasePos,tEraseLength);

   mWorkScriptFilePath = "./work/aaaa_script.txt";

   Prn::print(0, "GCodeName       %s",  mWorkGCodeName.c_str());
   Prn::print(0, "GCodeFilePath   %s",  mWorkGCodeFilePath.c_str());
   Prn::print(0, "GCodePrefixpath %s",  mWorkSliceFilePrefixPath.c_str());
   Prn::print(0, "ScriptFilePath   %s", mWorkScriptFilePath.c_str());
   Prn::print(0, "done");
   Prn::print(0, "");

   // Done.
   return true;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return the file path to the gcode file.

std::string FileManager::getWorkGCodeFilePath()
{
   return mWorkGCodeFilePath;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return the file path to a slice file.

std::string FileManager::getWorkSliceFilePath(int aSliceNumber)
{
   char tString[200];
   sprintf(tString, "%s%04d.png", mWorkSliceFilePrefixPath.c_str(), aSliceNumber);
   return std::string(tString);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

