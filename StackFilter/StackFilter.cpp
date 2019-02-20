/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svImageFunctions.h"

#include "StackFilter.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

StackFilter::StackFilter()
{
   reset();
}

void StackFilter::reset()
{
   mInputImageD.release();
   mInputImageC.release();
   mInputImageU.release();
   mOutputImage.release();

   mInputPathD.clear();
   mInputPathC.clear();
   mInputPathU.clear();
   mOutputPath.clear();

   mEvaluator.reset();
   mResults.reset();
   mReadCount = 0;
}

void StackFilter::show()
{
   return;
   Prn::print(0, "");
   Prn::print(0, "StackFilter Results****************");
   Prn::print(0, "ReadCount        %5d", mReadCount);
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the images pointed to by a script file. Return true if successful.

bool StackFilter::doFilterScriptFile(std::string& aScriptFilePath)
{
   // Do this first.
   reset();

   // Open the script file.
   if (!mReader.doOpenFile(aScriptFilePath)) return false;

   // Loop through the script file and process all of the slice
   // commands, which contain the stack image file paths. This
   // loops through the image stack from top to bottom.

   // Filter.
   doBeforeLoop();
   while (true)
   {
      // Read from the file. Exit if end of file.
      if (!mReader.doRead()) break;

      // Test the command code for a slice command.
      if (mReader.mCmdCode == PX::cScriptCmd_Slice)
      {
         // Filter.
         doProcessLoop();
         mReadCount++;
      }
   }
   // Filter.
   doAfterLoop();

   // Done.
   mReader.doCloseFile();
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Loop processing decomposition.

void StackFilter::doBeforeLoop()
{
   SV::createZeroImage(mInputImageD, mInputImageU);
   mInputPathD = std::string("zeros");

   Prn::print(0, "%3d %-25s %-25s %-25s $ %-25s",
      0, "up", "current", "down", "output");
}

void StackFilter::doProcessLoop()
{
   // Shift images.
   mInputImageU = mInputImageC;
   mInputImageC = mInputImageD;
   mInputImageD = cv::imread(mReader.mString, CV_LOAD_IMAGE_GRAYSCALE);

   // Shift file paths.
   mInputPathU = mInputPathC;
   mInputPathC = mInputPathD;
   mInputPathD = std::string(mReader.mString);
   mOutputPath = mInputPathC;

   // Exit if first.
   if (mReadCount == 0) return;

   // Show.
   Prn::print(0, "%3d %-25s %-25s %-25s $ %-25s", 
      mReadCount, mInputPathU.c_str(), mInputPathC.c_str(), mInputPathD.c_str(), mOutputPath.c_str());
}

void StackFilter::doAfterLoop()
{
   // Shift images.
   mInputImageU = mInputImageC;
   mInputImageC = mInputImageD;
   mInputImageD = cv::imread(mReader.mString, CV_LOAD_IMAGE_GRAYSCALE);

   // Shift file paths.
   mInputPathU = mInputPathC;
   mInputPathC = mInputPathD;
   mInputPathD = std::string("ones");
   mOutputPath = mInputPathC;

   // Show.
   Prn::print(0, "%3d %-25s %-25s %-25s $ %-25s",
      mReadCount, mInputPathU.c_str(), mInputPathC.c_str(), mInputPathD.c_str(), mOutputPath.c_str());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

