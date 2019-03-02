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
#include "svRCSize.h"
#include "svRCRect.h"
#include "svStackSimObjectParms.h"

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

class StackSimParms : public Ris::BaseCmdLineParms
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static const int cMaxStringSize = 200;


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Parameter members.

   // Simulated stack objects parms file names.
   char  mObjectFileName1[cMaxStringSize];
   char  mObjectFileName2[cMaxStringSize];
   char  mObjectFileName3[cMaxStringSize];
   char  mObjectFileName4[cMaxStringSize];


   // Simulated stack object major row column positioning.
   RCSize  mMajorSize;
   RCIndex mObject1Major;
   RCIndex mObject2Major;
   RCIndex mObject3Major;
   RCIndex mObject4Major;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Expanded members that are not read from the parms file.

   // Stack objects.
   StackSimObjectParms   mObjectParms1;
   StackSimObjectParms   mObjectParms2;
   StackSimObjectParms   mObjectParms3;
   StackSimObjectParms   mObjectParms4;

   // Stack object rectangles.
   RCRect mObject1Rect;
   RCRect mObject2Rect;
   RCRect mObject3Rect;
   RCRect mObject4Rect;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor,
   typedef Ris::BaseCmdLineParms BaseClass;
   StackSimParms();
   void reset();
   void show();

   // Base class override: Execute a command from the command file to set a 
   // member variable. This is called by the associated command file object
   // for each command in the file.
   void execute(Ris::CmdLineCmd* aCmd) override;

   // Simulate expanded member variables. This is called after the entire
   // section of the command file has been processed.
   void expand() override;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _SVSTACKSIMPARMS_CPP_
   StackSimParms gStackSimParms;
#else
   extern StackSimParms gStackSimParms;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace