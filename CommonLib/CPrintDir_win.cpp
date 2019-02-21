/*==============================================================================
Print utility
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <windows.h>

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
   return "C:\\aaa_cprint\\";
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Set the program working directory to the cprint directory path.

void setProgramDir()
{
   Ris::portableChdir("C:\\aaa_cprint");
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return directory paths.

std::string getBaseDirPath()    { return std::string("C:\\aaa_cprint\\"); }
std::string getZipDirPath()     { return std::string(".\\zip\\"); }
std::string getGCodeDirPath()   { return std::string(".\\gcode\\"); }
std::string getWorkDirPath()    { return std::string(".\\work\\"); }
std::string getSpecialDirPath() { return std::string(".\\special\\"); }

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Clean the cprint work directory.

void doCleanWork()
{
   // Clean the work directory.
// Ris::doSystemCommand("del /s /q .\\work\\*.*");
   Ris::doSystemCommand("rmdir /s /q .\\work");
   Ris::doSystemCommand("mkdir .\\work");
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Get a directory listing of the cprint zip directory and return a list of
// filenames of zip files. The filenames do not include the filepath.

void getZipNameList(std::string& aZipDirPath, std::vector<std::string > &aZipNameList)
{
   aZipNameList.clear();
   std::string pattern = aZipDirPath + "\\*.zip";
   WIN32_FIND_DATA data;
   HANDLE hFind;
   if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE)
   {
      do
      {
         aZipNameList.push_back(data.cFileName);
      } while (FindNextFile(hFind, &data) != 0);
      FindClose(hFind);
   }

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

void getGCodeNameList(std::string& aGCodeDirPath, std::vector<std::string > &aGCodeNameList)
{
   aGCodeNameList.clear();
   std::string pattern = aGCodeDirPath + "\\*.gcode";
   WIN32_FIND_DATA data;
   HANDLE hFind;
   if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE)
   {
      do
      {
         aGCodeNameList.push_back(data.cFileName);
      } while (FindNextFile(hFind, &data) != 0);
      FindClose(hFind);
   }

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
   std::string pattern = ".\\work\\*.gcode";
   WIN32_FIND_DATA data;
   HANDLE hFind;
   if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE)
   {
      do
      {
         aWorkGCodeName = data.cFileName;
      } while (FindNextFile(hFind, &data) != 0);
      FindClose(hFind);
   }
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Zip a zip file from the work directory to the zip directory.

void doZipFromWork(std::string& aZipFilePath)
{
   char tString[200];

   sprintf(tString, "del /q %s", aZipFilePath.c_str());
   printf("doCommand %s\n", tString);
   Ris::doSystemCommand(tString);

   sprintf(tString, "C:\\MyPrograms\\7-Zip\\7z.exe a -r %s -w .\\work\\*", aZipFilePath.c_str());
   printf("doCommand %s\n", tString);
   Ris::doSystemCommand(tString);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Unzip a zip file to the work directory.

void doUnzipToWork(std::string& aZipFilePath)
{
   // Unzip the zip file into the work directory.
   // Ex. "/usr/bin/unzip ./zip/Test100.zip -d ./work"
   char tString[200];
   sprintf(tString, "C:\\MyPrograms\\7-Zip\\7z.exe x %s -o.\\work -y -r", aZipFilePath.c_str());
   printf("doCommand %s\n", tString);
   Ris::doSystemCommand(tString);
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
   sprintf(tString, "copy %s .\\work", aFilePath.c_str());
   Ris::doSystemCommand(tString);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Touch a file.

void doTouch(std::string& aFilePath)
{
   char tString[200];
   sprintf(tString, "C:\\MyPrograms\\bin\\touch.exe %s",aFilePath.c_str());
   Ris::doSystemCommand(tString);
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace