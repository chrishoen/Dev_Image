#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Parameters class whose values are read from a command file. 
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineTables.h"
#include "risCmdLineParms.h"
#include "svRCIndex.h"
#include "svRCSize.h"
#include "svRCRect.h"
#include "svRCSector.h"
#include "svRational.h"
#include "svStackObjectParms.h"

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

class StackParms : public Ris::BaseCmdLineParms
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static const int cMaxStringSize = 200;
   static const int cMaxObjects = 8;
   static const int cMaxRafts = 8;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Parameter members.

   // Stack name and size.
   char mStackName[cMaxStringSize];
   int  mStackHeight;
   int  mObjectHeight;
   int  mRaftHeight;

   // Warp rational.
   SV::Rational mWarp;

   // Stack object enable flags.
   Ris::CmdLineTable1D<bool, cMaxObjects>  mObjectEnable;
   Ris::CmdLineTable1D<bool, cMaxRafts>    mRaftEnable;

   // Stack object parms file names.
   Ris::CmdLineTable1D<Ris::TableString, cMaxObjects>  mObjectFileName;
   Ris::CmdLineTable1D<Ris::TableString, cMaxRafts>    mRaftFileName;

   // Stack object major row column positioning.
   RCSize mObjectMajorSize;
   RCSize mRaftMajorSize;
   Ris::CmdLineTable2D<int, 4, cMaxObjects>  mObjectLayout;
   Ris::CmdLineTable2D<int, 4, cMaxRafts>    mRaftLayout;
   RCIndex mObjectMajor[cMaxObjects];
   RCIndex mRaftMajor[cMaxRafts];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Expanded members that are not read from the parms file.

   // Stack object parameters.
   StackObjectParms  mObjectParms[cMaxObjects];
   StackObjectParms  mRaftParms[cMaxRafts];

   // Stack object size.
   RCSize  mObjectSize;
   RCSize  mRaftSize;

   // Stack object sectors.
   RCSector mObjectSector[cMaxObjects];
   RCSector mRaftSector[cMaxRafts];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor,
   typedef Ris::BaseCmdLineParms BaseClass;
   StackParms();
   void reset();

   // Base class override: Execute a command from the command file to set a 
   // member variable. This is called by the associated command file object
   // for each command in the file.
   void execute(Ris::CmdLineCmd* aCmd) override;

   // Simulate expanded member variables. This is called after the entire
   // section of the command file has been processed.
   void expand() override;
   void expandObjects();
   void expandRafts();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Show.
   void show(int aCode);
   void showObjects();
   void showRafts();

   // Return a roi center as a function of the stack index.
   // Reverse index is from top to bottom.
   // Stack index is from bottom to top.
   RCIndex getReverseRoiCenter(int aObjectIndex, int aReverseIndex);
   RCIndex getStackRoiCenter(int aObjectIndex, int aStackIndex);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _SVSTACKPARMS_CPP_
   StackParms gStackParms;
#else
   extern StackParms gStackParms;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace