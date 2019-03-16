/*==============================================================================
Print utility
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#include "risSystemCalls.h"

#include "CPrintDir.h"

//****************************************************************************
//****************************************************************************
//****************************************************************************

namespace CPrint
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Return the cprint directory path.

const char* getBaseDirectory()
{
   return "/opt/cprint/";
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Set the program working directory to the cprint directory path.

void setProgramDir()
{
   Ris::portableChdir("/opt/cprint");
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return directory paths.

std::string getBaseDirPath() { return std::string("/opt/cprint/"); }
std::string getZipDirPath() { return std::string("./zip/"); }
std::string getGCodeDirPath() { return std::string("./gcode/"); }
std::string getWorkDirPath() { return std::string("./work/"); }
std::string getSpecialDirPath() { return std::string("./special/"); }

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Clean the cprint work directory.

void doCleanWork()
{
   // Clean the work directory.
   Ris::doSystemCommand("rm -rf ./work/*");
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Get a directory listing of the cprint zip directory and return a list of
// filenames of zip files. The filenames do not include the filepath.

void getZipNameList(std::string& aZipDirPath, std::vector<std::string > &aZipNameList)
{
   aZipNameList.clear();
   DIR* dirp = opendir(aZipDirPath.c_str());
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
         if (tExt.compare(".zip") == 0)
         {
            // Push filename to the list.
            aZipNameList.push_back(tFileName);
         }
      }
   }
   closedir(dirp);

   // Exit if the list is empty.
   if (aZipNameList.empty()) return;

   // Sort the list.
   std::sort(aZipNameList.begin(), aZipNameList.end());
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Get a directory listing of the cprint gcode directory and return a list of
// filenames of gcode files. The filenames do not include the filepath.

void getGCodeNameList(std::string& aGCodeDirPath, std::vector<std::string >& aGCodeNameList)
{
   aGCodeNameList.clear();
   DIR* dirp = opendir(aGCodeDirPath.c_str());
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
            // Push filename to the list.
            aGCodeNameList.push_back(tFileName);
         }
      }
   }
   closedir(dirp);

   // Exit if the list is empty.
   if (aGCodeNameList.empty()) return;

   // Sort the list.
   std::sort(aGCodeNameList.begin(), aGCodeNameList.end());
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Find the gcode file in the work directory and return its name.

void doFindWorkGCodeName(std::string& aWorkGCodeName)
{
   aWorkGCodeName.clear();
   DIR* dirp = opendir("./work/");
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
            // Push filename to the list.
            aWorkGCodeName = tFileName;
         }
      }
   }
   closedir(dirp);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Zip a zip file from the work directory to the zip directory.

void doZipFromWork(std::string& aZipFilePath)
{
   char tString[200];

   sprintf(tString, "rm  %s", aZipFilePath.c_str());
   Prn::print(Prn::View02, "doCommand %s", tString);
   Ris::doSystemCommand(tString);

   sprintf(tString, "/usr/bin/zip -r %s ./work", aZipFilePath.c_str());
   Prn::print(Prn::View02, "doCommand %s", tString);
   Ris::doSystemCommand(tString);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Unzip a zip file to the work directory.

void doUnzipToWork(std::string& aZipFilePath)
{
   // Guard.
   if (!Ris::portableFilePathExists(aZipFilePath.c_str()))
   {
      Prn::print(0, "ERROR doUnzipToWork filepath not exist");
      return;
   }

   // Temp.
   int tRet;
   char tString[200];

   // Clean the work directory.
// Ris::doSystemCommand("rm -rf ./work/*");

   // Unzip the zip file into the work directory.
   // Ex. "/usr/bin/unzip ./zip/Test100.zip -d ./work"
   sprintf(tString, "/usr/bin/unzip %s -d ./work", aZipFilePath.c_str());
   Ris::doSystemCommand(tString);
   Ris::doSystemCommand("sudo chmod 666 ./work/*.*");
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Copy a file to the work directory.

void doCopyToWork(std::string& aFilePath)
{
   // Copy the file into the work directory.
   // Ex. "cp ./gcode/Test100.gcode ./work"
   char tString[200];
   sprintf(tString, "cp %s ./work", aFilePath.c_str());
   Ris::doSystemCommand(tString);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Touch a file.

void doTouch(std::string& aFilePath)
{
   char tString[200];
   sprintf(tString, "/usr/bin/touch %s", aFilePath.c_str());
   Ris::doSystemCommand(tString);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
