
#pragma once

/*==============================================================================
Parameters class whose values are read from a command file. 
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineExec.h"
#include "svRCIndex.h"
#include "svRCSector.h"

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

class TileParms : public Ris::BaseCmdLineExec
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
   static const int cShapeSquare         = 1;
   static const int cShapeDiamond        = 2;
   static const int cShapeQuarterSquare  = 3;
   static const int cShapeQuarterDiamond = 4;


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members that are read from the parms file.

   // True if valid.
   bool mValid;

   // Name string.
   char mName[cMaxStringSize];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members that are read from the parms file.

   // Shape 1=square 2=diagonal.
   int mShape;
   
   // Horizontal iterations.
   int mNumLoop;
   int mNumRow;
   int mNumCol;

   // Vertical iterations.
   int mStepH;
   int mStepV;
   int mStepL;

   // Row column center.
   SV::RCSector mSector;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor,
   typedef Ris::BaseCmdLineExec BaseClass;
   TileParms();
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

   static char* asStringShape(int aX);
   char* asStringShape();

   bool isSquare() { return mShape == cShapeSquare; }
   bool isDiamond() { return mShape == cShapeDiamond; }
   bool isQuarterSquare() { return mShape == cShapeQuarterSquare; }
   bool isQuarterDiamond() { return mShape == cShapeQuarterDiamond; }

   void setName(const char* aName);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Adjust the loop number according to the reverse stack index.
   void doAdjust(int aReverseIndex);

   // Return a roi center as a function of the reverse stack index.
   RCIndex getReverseRoiCenter(int aReverseIndex);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace