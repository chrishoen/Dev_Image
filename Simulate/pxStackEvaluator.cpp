/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "pxStackEvaluator.h"

namespace PX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

StackEvaluator::StackEvaluator()
{
   reset();
}

void StackEvaluator::reset()
{
   mEvaluator.reset();
   mResults.reset();
   mReadCount = 0;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test a script file. Return true if successful.

bool StackEvaluator::doTestScriptFile(std::string& aScriptFilePath)
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
      mReadCount++;

      // Test the command code.
      if (mReader.mCmdCode == cScriptCmd_Slice)
      {
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

void StackEvaluator::show()
{
   return;
   Prn::print(0, "");
   Prn::print(0, "StackEvaluator Results****************");
   Prn::print(0, "ReadCount        %5d", mReadCount);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

