/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

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
#if 0
   mWorkGCodeName.clear();
   DIR* dirp = opendir("./work");
   struct dirent * dp;
   while ((dp = readdir(dirp)) != NULL)
   {
      if (dp->d_type == DT_REG)
      {
         // Get file name from record.
         std::string tFileName = dp->d_name;

         // Find dot position.
         std::size_t tDotPos = tFileName.find_last_of(".");

         // If dot not found then continue the loop.
         if (tDotPos == std::string::npos) continue;

         // Get file extension substring.
         std::string tExt = tFileName.substr(tDotPos, tFileName.size() - tDotPos);

         // Test the file extension substring.
         if (tExt.compare(".gcode") == 0)
         {
            // Erase file extension substring.
//EXT       tFileName.erase(tDotPos, tFileName.size() - tDotPos);
            mWorkGCodeName = tFileName;
            break;
         }
      }
   }
   closedir(dirp);

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
#endif
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

