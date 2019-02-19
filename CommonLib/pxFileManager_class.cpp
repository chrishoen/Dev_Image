/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "CPrintDir.h"
#include "risSystemCalls.h"

#define _PXFILEMANAGER_CPP_
#include "pxFileManager.h"

namespace PX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

FileManager::FileManager()
{
   mZipInProgress = false;
}

void FileManager::initialize()
{
   mBaseDirPath  = CPrint::getBaseDirPath();
   mZipDirPath   = CPrint::getZipDirPath();
   mGCodeDirPath = CPrint::getGCodeDirPath();
   mWorkDirPath  = CPrint::getWorkDirPath();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void FileManager::show1()
{
   std::cout << "BaseDirPath  " << mBaseDirPath << std::endl;
   std::cout << "ZipDirPath   " << mZipDirPath << std::endl;
   std::cout << "GCodeDirPath " << mGCodeDirPath << std::endl;
   std::cout << "WorkDirPath  " << mWorkDirPath << std::endl;
   std::cout << std::endl;
   std::cout << "ZipName      " << mZipName << std::endl;
   std::cout << "ZipFilePath  " << mZipFilePath << std::endl;
}

void FileManager::show2()
{
   std::cout << std::endl;
   std::cout << "ZipName     " << mZipName << std::endl;
   std::cout << "ZipFilePath " << mZipFilePath << std::endl;
}

// Return true if the file exists,
bool FileManager::exists(std::string aFilePath)
{
   return Ris::portableFilePathExists(aFilePath.c_str());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

