#pragma once
/*==============================================================================
image stack filter
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <string>
#include <opencv2/core/core.hpp>

#include "pxScriptReader.h"
#include "svImageEvaluator.h"
#include "svImageResults.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encalsulates an image stack filter. It reads from a script file
// to obtain the file paths of images contained in an image stack. It reads
// the stack of image files and filters them.
// reader to .

class StackShow
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   // File paths.
   std::string mScriptFilePath;

   // Images.
   cv::Mat mInputImageS1;
   cv::Mat mInputImageS2;
   cv::Mat mInputImageS3;
   cv::Mat mOutputImageW2;

   // Image file paths.
   std::string mInputPathS1;
   std::string mInputPathS2;
   std::string mInputPathS3;
   std::string mOutputPathW2;

   // Image file paths.
   std::string mSelectPathS1;
   std::string mSelectPathS2;
   std::string mSelectPathS3;

   // Select loop count.
   int mObjectIndex;
   int mStackIndex;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Parameterized functions and variables.
   PX::ScriptReader   mReader;
   SV::ImageEvaluator mEvaluator;
   SV::ImageResults   mResults;

   // Metrics.
   int mReadCount;
   int mRows;
   int mCols;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   StackShow();
   void reset();
   void show();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Show the images pointed to by a script file. Return true if successful.
   bool doShowScriptFile(int aObjectIndex,int aStackIndex);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Loop processing decomposition.
   void doBeforeLoop();
   void doFirstInLoop();
   void doNotFirstInLoop();
   void doAfterLoop();

   // Zip the output work directory to the zip directory.
   void doShow();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************




