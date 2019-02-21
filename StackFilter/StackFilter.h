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
#include "svNN3dRuleFilter.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encalsulates an image stack filter. It reads from a script file
// to obtain the file paths of images contained in an image stack. It reads
// the stack of image files and filters them.
// reader to .

class StackFilter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   // File paths.
   std::string mScriptFilePath;
   std::string mInputZipFilePath;
   std::string mOutputZipFilePath;

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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Parameterized functions and variables.
   PX::ScriptReader   mReader;
   SV::NN3dRuleFilter mFilter;

   // Metrics.
   int mReadCount;
   int mRows;
   int mCols;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   StackFilter();
   void reset();
   void show();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Filter the images pointed to by a script file. Return true if successful.
   bool doFilterScriptFile(std::string& aInputZipFileName);

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
   void doZipOutput();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************




