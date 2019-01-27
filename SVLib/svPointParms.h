#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Parameters class whose values are read from a command file. 
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineParms.h"
#include "svRCIndex.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class that contains parameter member variables. The values of
// the parameters are set by reading a text file that contains command lines.
// Each command line is of the form "command argument1 argument2 ...".
// 
// The command files are partitioned into different sections and only one
// section can be read at a time to set member variables that are specified
// in it.
//
// The command files are managed by a CmdLineFile object. This opens the 
// file, reads each line in it, parses the line into a CmdLineCmd command 
// object, passes the command object to this object for command execution,
// and then closes the file. 
//
// This class inherits from BaseCmdLineParms, which inherits from 
// BaseCmdLineExec. BaseCmdLineParms provides a method that uses a
// CmdLineFile object to read and process the file. BaseCmdLineExec provides
// an abstract execute(cmd) method to which inheritors provide an overload
// that is called by the CmdLineFile object for each command in the file.
// This execute method then sets a member variables, according to the
// command.
// 
// This class can contain member variables that also inherit from
// BaseCmdLineExec. This provides for command files that have a nested
// structure. If so, then this class is the root.
// 

class PointParms : public Ris::BaseCmdLineParms
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members that are read from the parms file.

   // Grid parms.
   RCSize   mMajorGridSize;
   RCSize   mGridSize;
   RCSize   mSubGridSize;

   // PGrid search neighborhood.
   int mNeighborhoodSize;

   // If true then use the noise floor for thresholding.
   bool mNoiseFloorFlag;

   // Thresholds.
   double mSearchThreshold;
   double mTrackThresholdScale;
   double mTrackThresholdMin;

   // If the number of pixels that are above the threshold are within
   // these numbers then there are enough pixels to calculate a
   // point estimate. 
   int mThresholdAboveMin;
   int mThresholdAboveMax;

   // If true then the search four limit will be calculated automatically.
   bool mSearch4AutoFlag;

   // Search four variables.
   double mSearch4Scale;
   int    mSearch4Limit;

   // Slant alpha filter alpha.
   double mSlantFilterAlpha;

   // Estimator.
   int mPointEstimatorLimit;

   // If true then throw an exception if stage4 isn't reached.
   bool mStage4ThrowFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members that are read from the parms file.
   // Image guassian blur variables.

   bool mGaussBlurFlag;
   int  mGaussBlur;

   // Image alpha filter variables.
   bool    mAlphaFilterFlag;
   double  mAlpha;

   // Image directory.
   char mImageDir [cMaxStringSize];

   // Image file save flags.
   bool mImageSaveFlag;

   // Log enable flag.
   bool mLogEnable;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Expanded members that are not read from the parms file.

   // Image file names,these are based at the image directory.
   char mCapturedImageFileName          [cMaxStringSize];
   char mFilteredImageFileName          [cMaxStringSize];
   char mNoiseFloorFileName             [cMaxStringSize];
  
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infrastucture.

   // Constructor,
   typedef Ris::BaseCmdLineParms BaseClass;
   PointParms();
   void reset();
   void show();

   // Base class override: Execute a command from the command file to set a 
   // member variable. This is called by the associated command file object
   // for each command in the file.
   void execute(Ris::CmdLineCmd* aCmd) override;

   // Calculate expanded member variables. This is called after the entire
   // section of the command file has been processed.
   void expand() override;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _POINTPARMS_CPP_
   PointParms gPointParms;
#else
   extern PointParms gPointParms;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace