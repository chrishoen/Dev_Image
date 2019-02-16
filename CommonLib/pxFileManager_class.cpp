/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <iostream>
#include <algorithm>

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
   mBaseDirPath = std::string(getCPrintDirectory());
   mZipDirPath = mBaseDirPath + "/zip";
   mGCodeDirPath = mBaseDirPath + "/gcode";
   mWorkDirPath = mBaseDirPath + "/work";
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void FileManager::show1()
{
   std::cout << "BaseDirPath " << mBaseDirPath << std::endl;
   std::cout << "ZipDirPath " << mZipDirPath << std::endl;
   std::cout << "GCodeDirPath " << mGCodeDirPath << std::endl;
   std::cout << "WorkDirPath " << mWorkDirPath << std::endl;
   std::cout << std::endl;
   std::cout << "ZipName     " << mZipName << std::endl;
   std::cout << "ZipFilePath " << mZipFilePath << std::endl;
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

