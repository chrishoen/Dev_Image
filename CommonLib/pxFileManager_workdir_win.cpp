/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"
#include <windows.h>

#include "risSystemCalls.h"
#include "CPrintDir.h"

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
   // Find the filename of the gcode file in the work directory.
   CPrint::doFindWorkGCodeName(mWorkGCodeName);

   // Guard.
   if (mWorkGCodeName.empty())
   {
      mError = "ERROR gcode file does not exist";
      Prn::print(0, mError.c_str());
      mWorkGCodeName = "NULL";
      return false;
   }

   mWorkGCodeFilePath = mWorkDirPath + mWorkGCodeName;

   mWorkSliceFilePrefixPath = mWorkDirPath + mWorkGCodeName;
   std::size_t tErasePos = mWorkSliceFilePrefixPath.find_last_of(".");
   std::size_t tEraseLength = mWorkSliceFilePrefixPath.size() - tErasePos;
   mWorkSliceFilePrefixPath.erase(tErasePos,tEraseLength);

   mWorkScriptFilePath = mWorkDirPath + "aaaa_script.txt";

   Prn::print(Prn::View02, "GCodeName        %s",  mWorkGCodeName.c_str());
   Prn::print(Prn::View02, "GCodeFilePath    %s",  mWorkGCodeFilePath.c_str());
   Prn::print(Prn::View02, "GCodePrefixpath  %s",  mWorkSliceFilePrefixPath.c_str());
   Prn::print(Prn::View02, "ScriptFilePath   %s",  mWorkScriptFilePath.c_str());
   Prn::print(Prn::View02, "done");
   Prn::print(Prn::View02, "");

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

