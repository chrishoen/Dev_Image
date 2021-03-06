
#pragma once

/*==============================================================================
Parameters class whose values are read from a command file. 
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineExec.h"
#include "svRCIndex.h"
#include "svRCSize.h"

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

class MorphParms : public Ris::BaseCmdLineExec
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static const int cMaxStringSize = 40;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   // None.
   static const int cNone = 0;

   // SimImage types.
   static const int cModeSquare  = 1;
   static const int cModeDiamond = 2;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members that are read from the parms file.

   // True if valid.
   bool mValid;

   // True if valid.
   char mName[cMaxStringSize];

   // Sim generated image size.
   RCSize mImageSize;

   // If true then generate and write a first image.
   bool mGenerateFirst;
   bool mWriteFirst;

   // Iterations.
   int mRepeatNum;
   int mMorphNum;
   int mWriteNum;

   // Mode 1=square 2=diagonal.
   int mMode;
   
   // If true then add delta. If false then subtract delta.
   bool mAddFlag;

   // Row column deltas.
   SV::RCSize mDelta;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor,
   typedef Ris::BaseCmdLineExec BaseClass;
   MorphParms();
   void reset();
   void show(const char* aLabel);

   // Base class override: Execute a command from the command file to set a 
   // member variable. This is called by the associated command file object
   // for each command in the file.
   void execute(Ris::CmdLineCmd* aCmd) override;

   // Calculate expanded member variables. This is called after the entire
   // section of the command file has been processed.
   void expand();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Helpers.

   static char* asStringMode(int aX);
   char* asStringMode();

   bool isSquare() { return mMode == cModeSquare; }
   bool isDiamond() { return mMode == cModeDiamond; }

   // Helpers.
   void setName(const char* aName);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace