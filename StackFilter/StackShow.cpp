/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "CPrintDir.h"
#include "svImageParms.h"
#include "svImageFunctions.h"

#include "StackShow.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

StackShow::StackShow()
{
   reset();
}

void StackShow::reset()
{
   mInputImageS1 = cv::Mat();
   mInputImageS2 = cv::Mat();
   mInputImageS3 = cv::Mat();
   mOutputImageW2 = cv::Mat();

   mInputPathS1.clear();
   mInputPathS2.clear();
   mInputPathS3.clear();
   mOutputPathW2.clear();

   mReadCount = 0;
   mRows = 0;
   mCols = 0;

   mEvaluator.reset();
   mResults.reset();
}

void StackShow::show()
{
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Filter the images pointed to by a script file. Return true if successful.

bool StackShow::doShowScriptFile(int aSelect)
{
   // Do this first.
   reset();

   // File paths.
   mScriptFilePath = CPrint::getWorkDirPath() + "aaaa_script.txt";

   // Open the script file.
   if (!mReader.doOpenFile(mScriptFilePath)) return false;

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

   // Show.
   doShow();

   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Loop processing decomposition.

void StackShow::doBeforeLoop()
{
   Prn::print(0, "STACK FILTER");
   Prn::print(0, "%3d %-25s %-25s %-25s $ %-25s",
      -1, "s1", "s2", "s3", "output");
   Prn::print(0, "");
}

void StackShow::doFirstInLoop()
{
   // Initialize file paths.
   // S1 = empty
   // S2 = zeros
   // S3 = input
   mInputPathS1 = "empty";
   mInputPathS2 = "zeros";
   mInputPathS3 = std::string(mReader.mString);
   mOutputPathW2 = "empty";

   // Initialize images.
   // S1 = empty
   // S2 = zeros
   // S3 = input
   mInputImageS3 = cv::imread(mReader.mString, CV_LOAD_IMAGE_GRAYSCALE);
   mRows = mInputImageS3.rows;
   mCols = mInputImageS3.cols;
   mInputImageS2 = cv::Mat(mRows, mCols, CV_8UC1, cv::Scalar(0));
   mInputImageS1 = cv::Mat();
   mOutputImageW2 = cv::Mat();

   // Show.
   Prn::print(0, "%3d %-25s %-25s %-25s $ %-25s",
      mReadCount, mInputPathS1.c_str(), mInputPathS2.c_str(), mInputPathS3.c_str(), mOutputPathW2.c_str());
}

void StackShow::doNotFirstInLoop()
{
   // Shift file paths.
   // S1 = S2
   // S2 = S3 
   // S3 = input
   mInputPathS1 = mInputPathS2;
   mInputPathS2 = mInputPathS3;
   mInputPathS3 = std::string(mReader.mString);
   mOutputPathW2 = mInputPathS2;

   // Shift images.
   // S1 = S2
   // S2 = S3 
   // S3 = input
   mInputImageS1 = mInputImageS2;
   mInputImageS2 = mInputImageS3;
   mInputImageS3 = cv::imread(mReader.mString, CV_LOAD_IMAGE_GRAYSCALE);

   // Show.
   Prn::print(0, "%3d %-25s %-25s %-25s $ %-25s", 
      mReadCount, mInputPathS1.c_str(), mInputPathS2.c_str(), mInputPathS3.c_str(), mOutputPathW2.c_str());

   // Filter.
}

void StackShow::doAfterLoop()
{
   // Shift file paths.
   // S1 = S2
   // S2 = S3 
   // S3 = ones
   mInputPathS1 = mInputPathS2;
   mInputPathS2 = mInputPathS3;
   mInputPathS3 = std::string("ones");
   mOutputPathW2 = mInputPathS2;

   // Shift images.
   // S1 = S2
   // S2 = S3 
   // S3 = ones
   mInputImageS1 = mInputImageS2;
   mInputImageS2 = mInputImageS3;
   mInputImageS3 = cv::Mat(mRows, mCols, CV_8UC1,cv::Scalar(255));

   // Show.
   Prn::print(0, "%3d %-25s %-25s %-25s $ %-25s",
      -2, mInputPathS1.c_str(), mInputPathS2.c_str(), mInputPathS3.c_str(), mOutputPathW2.c_str());

   // Filter.
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void StackShow::doShow()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
