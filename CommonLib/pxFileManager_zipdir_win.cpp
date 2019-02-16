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
// Get the zip name list from the zip directory.

void FileManager::getZipNameList()
{
   mZipNameList.clear();
   std::string pattern = mZipDirPath + "\\*.zip";
   WIN32_FIND_DATA data;
   HANDLE hFind;
   if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE)
   {
      do
      {
         mZipNameList.push_back(data.cFileName);
      } while (FindNextFile(hFind, &data) != 0);
      FindClose(hFind);
   }

   // Exit if the list is empty.
   if (mZipNameList.empty()) return;

   // Sort the list.
   std::sort(mZipNameList.begin(), mZipNameList.end());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get the zip name list from the zip directory.

void FileManager::showZipNameList()
{
   for (int i = 0; i < mZipNameList.size(); i++)
   {
      Prn::print(0, "%3d %s", i, mZipNameList[i].c_str());
   }
   Prn::print(0, "done");
   Prn::print(0, "");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Select a zip name from the zip name list. Return true if successful.

bool FileManager::setZipName(int aZipNum)
{
   // Do this first.
   mZipName.clear();
   mZipFilePath.clear();

   // Guard.
   if (mZipNameList.empty())
   {
      Prn::print(0, "ERROR Zip name list does not exist");
      return false;
   }

   // Guard.
   if (aZipNum <0 || aZipNum >= mZipNameList.size())
   {
      mError = "ERROR Zip number out of bounds";
      Prn::print(0, mError.c_str());
      mZipName = "NULL";
      mZipFilePath = "NULL FILE";
      return false;
   }

   // Set zip name and file path.
   mZipName = mZipNameList[aZipNum];
   //EXT mZipFilePath = "./zip/" + mZipName + ".zip";
   mZipFilePath = "./zip/" + mZipName;

   // Test if the zip file exists.
   if (!exists(mZipFilePath))
   {
      mError = "ERROR Zip File does not exist " + mZipFilePath;
      Prn::print(0, mError.c_str());
      mZipName.clear();
      mZipFilePath.clear();
      return false;
   }

   // Done.
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set the zip name. Return true if successful.

bool FileManager::setZipName(const char* aZipName)
{
   // Set zip name and file path.
   mZipName = aZipName;
//EXT mZipFilePath = "./zip/" + mZipName + ".zip";
   mZipFilePath = "./zip/" + mZipName;

   // Test if the zip file exists.
   if (!exists(mZipFilePath))
   {
      mError = "ERROR Zip File does not exist " + mZipFilePath;
      Prn::print(0, mError.c_str());
      mZipName.clear();
      mZipFilePath.clear();
      return false;
   }

   // Done.
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Unzip the zip file from the zip directory into the work directory.
// Return true if successful.

bool FileManager::doLoadZip(int aZipNum)
{
   mError.clear();
   // Try to set the zip name.
   if (!setZipName(aZipNum)) return false;

   // Load the zip.
   return doLoadZip();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Unzip the zip file from the zip directory into the work directory.
// Return true if successful.

bool FileManager::doLoadZip(const char* aZipName)
{
   mError.clear();
   // Try to set the zip name.
   if (!setZipName(aZipName)) return false;

   // Load the zip.
   return doLoadZip();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Unzip the zip file from the zip directory into the work directory.
// Return true if successful.

bool FileManager::doLoadZip()
{
   // Guard.
   if (!exists(mZipFilePath))
   {
      mError = "ERROR Zip File does not exist " + mZipFilePath;
      Prn::print(0, mError.c_str());
      return false;
   }

   // Temp.
//   int tRet;
   char tString[200];

   // Clean the work directory.
   Ris::doSystemCommand("rm -rf ./work/*");

   // Unzip the zip file into the work directory.
   // Ex. "/usr/bin/unzip ./zip/Test100.zip -d ./work"
   sprintf(tString, "/usr/bin/unzip %s -d ./work", mZipFilePath.c_str());
   Ris::doSystemCommand(tString);
   Ris::doSystemCommand("sudo chmod 666 ./work/*.*");

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

