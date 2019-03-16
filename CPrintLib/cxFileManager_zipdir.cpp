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
// Get the zip name list from the zip directory.

void FileManager::getZipNameList()
{
   CPrint::getZipNameList(mZipDirPath, mZipNameList);
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
   mZipFilePath = mZipDirPath + mZipName;

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
   mZipFilePath = mZipDirPath + mZipName;

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

   // Clean the work directory.
   CPrint::doCleanWork();

   // Unzip the zip file into the work directory.
   CPrint::doUnzipToWork(mZipFilePath);

   // Done.
   mError = "PASS";
   Prn::print(Prn::View01, "LoadZip %s",mZipName.c_str());
   Prn::print(Prn::View02, "done");
   Prn::print(Prn::View02, "");
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

