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
         if (mReadCount == 0)
         {
            doFirstInLoop();
         }
         else
         {
            doNotFirstInLoop();
         }
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
   Prn::print(0, "STACK FILTER");
   Prn::print(0, "%3d %-25s %-25s %-25s $ %-25s",
      -1, "up", "current", "down", "output");
   Prn::print(0, "");
}

void StackFilter::doFirstInLoop()
{
   // Initialize images.
   // D = input
   // C = zeros
   // U = clear
   mInputImageD = cv::imread(mReader.mString, CV_LOAD_IMAGE_GRAYSCALE);
   SV::fillImage(false, mInputImageD, mInputImageC);
   mInputImageU.release();

   // Initialize file paths.
   // D = input
   // C = zeros
   // U = clear
   mInputPathD = std::string(mReader.mString);
   mInputPathC = "zeros";
   mInputPathU = "empty";
   mOutputPath = "empty";

   // Show.
   Prn::print(0, "%3d %-25s %-25s %-25s $ %-25s",
      mReadCount, mInputPathU.c_str(), mInputPathC.c_str(), mInputPathD.c_str(), mOutputPath.c_str());
}

void StackFilter::doNotFirstInLoop()
{
   // Shift images.
   // U = C
   // C = D
   // D = input
   mInputImageU = mInputImageC;
   mInputImageC = mInputImageD;
   mInputImageD = cv::imread(mReader.mString, CV_LOAD_IMAGE_GRAYSCALE);

   // Shift file paths.
   // U = C
   // C = D
   // D = input
   mInputPathU = mInputPathC;
   mInputPathC = mInputPathD;
   mInputPathD = std::string(mReader.mString);
   mOutputPath = mInputPathC;

   // Show.
   Prn::print(0, "%3d %-25s %-25s %-25s $ %-25s", 
      mReadCount, mInputPathU.c_str(), mInputPathC.c_str(), mInputPathD.c_str(), mOutputPath.c_str());
}

void StackFilter::doAfterLoop()
{
   // Shift images.
   // U = C
   // C = D
   // D = ones
   mInputImageU = mInputImageC;
   mInputImageC = mInputImageD;
   SV::fillImage(true, mInputImageC, mInputImageD);

   // Shift file paths.
   // U = C
   // C = D
   // D = ones
   mInputPathU = mInputPathC;
   mInputPathC = mInputPathD;
   mInputPathD = std::string("ones");
   mOutputPath = mInputPathC;

   // Show.
   Prn::print(0, "%3d %-25s %-25s %-25s $ %-25s",
      -2, mInputPathU.c_str(), mInputPathC.c_str(), mInputPathD.c_str(), mOutputPath.c_str());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

