/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "CPrintDir.h"
#include "pxZipWriter.h"

namespace PX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

ZipWriter::ZipWriter()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Zip the work directory to the zip directory with a zip filename
// that is a name plus a postfix.

void ZipWriter::doZipWork(
   const char* aZipName,
   const char* aPostFix)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // File paths.

   mWorkDirPath = CPrint::getWorkDirPath();
   mZipDirPath = CPrint::getZipDirPath();
   mZipFilePath = mZipDirPath + aZipName + aPostFix + ".zip";

   std::cout << "mWorkDirPath  " << mWorkDirPath << std::endl;
   std::cout << "mZipFilePath  " << mZipFilePath << std::endl;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Zip.

   CPrint::doZipFromWork(mZipFilePath);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

