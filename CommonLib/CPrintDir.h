#pragma once

/*==============================================================================
This unit provides a set of functions that provide management of a
relocatable cprint directory to be used by programs that use cprint.
==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <string>
#include <vector>

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CPrint
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// cprint directory management functions.
//

// Return the cprint directory path.
const char* getBaseDirectory();

// Set the program working directory to the cprint directory path.
void setProgramDir();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return directory paths.

std::string getBaseDirPath();
std::string getZipDirPath();
std::string getGCodeDirPath();
std::string getWorkDirPath();
std::string getSpecialDirPath();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// cprint directory management functions.

// Clean the cprint work directory.
void doCleanWork();

// Get a directory listing of the cprint zip directory and return a list of
// filenames of zip files. The filenames do not include the filepath.
void getZipNameList(std::string& aZipDirPath, std::vector<std::string > &aZipNameList);

// Get a directory listing of the cprint gcode directory and return a list of
// filenames of gcode files. The filenames do not include the filepath.
void getGCodeNameList(std::string& aGCodeDirPath, std::vector<std::string > &aGCodeNameList);

// Find the gcode file in the work directory and return its filename.
void doFindWorkGCodeName(std::string& aGCodeDirPath);

// Unzip a zip file from the zip directory to the work directory.
void doUnzipToWork(std::string& aZipFilePath);

// Zip a zip file from the work directory to the zip directory.
void doZipFromWork(std::string& aZipFilePath);

// Copy a file to the work directory..
void doCopyToWork(std::string& aFilePath);




//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
