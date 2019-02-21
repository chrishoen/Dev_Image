/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svImageParms.h"
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
   mInputImageS3.release();
   mInputImageS2.release();
   mInputImageS1.release();
   mOutputImageW2.release();

   mInputPathS3.clear();
   mInputPathS2.clear();
   mInputPathS1.clear();
   mOutputPathW2.clear();

   mReadCount = 0;
   mRows = 0;
   mCols = 0;

   mFilter.initialize(&SV::gImageParms.mNN3dRuleFilterParms);
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
      -1, "s1", "s2", "s3", "output");
   Prn::print(0, "");
}

void StackFilter::doFirstInLoop()
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

void StackFilter::doNotFirstInLoop()
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

   // Filter and write output.
   mFilter.doFilterImage(
      mInputImageS3,
      mInputImageS2,
      mInputImageS1,
      mOutputImageW2);
   cv::imwrite(mOutputPathW2.c_str(), mOutputImageW2);
}

void StackFilter::doAfterLoop()
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

   // Filter and write output.
   mFilter.doFilterImage(
      mInputImageS3,
      mInputImageS2,
      mInputImageS1,
      mOutputImageW2);

   cv::imwrite(mOutputPathW2.c_str(), mOutputImageW2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

#if 0
Prn::print(0, "DataU %x", mInputImageS1.data);
Prn::print(0, "DataC %x", mInputImageS2.data);
Prn::print(0, "DataD %x", mInputImageS3.data);
#endif

