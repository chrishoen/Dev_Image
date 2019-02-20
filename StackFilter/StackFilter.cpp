/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

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

   mEvaluator.reset();
   mResults.reset();
   mReadCount = 0;
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

   // Loop to test the script file.
   while (true)
   {
      // Read from the file. Exit if end of file.
      if (!mReader.doRead()) break;

      // Test the command code.
      if (mReader.mCmdCode == PX::cScriptCmd_Slice)
      {
         mReadCount++;
         // Read image.
         cv::Mat tImage = cv::imread(mReader.mString, CV_LOAD_IMAGE_GRAYSCALE);

         // Evaluate image.
         mResults.reset();
         mEvaluator.doEvaluateImage(tImage, mResults);
         mResults.show(0, mReader.mString);
      }
   }

   // Done.
   mReader.doCloseFile();
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show test results.

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

