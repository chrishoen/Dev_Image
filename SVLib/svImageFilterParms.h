#pragma once

/*==============================================================================
Parameters class whose values are read from a command file. 
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineExec.h"
#include "risCmdLineTables.h"
#include "svRCIndex.h"
#include "svRCRect.h"
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

class ImageFilterParms : public Ris::BaseCmdLineExec
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   // None.
   static const int cNone              = 0;

   // Filter types.
   static const int cFilterGaussBlur = 1;
   static const int cFilterCharacter    = 2;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members that are read from the parms file.

   // Filter type.
   int mFilterType;

   // Gaussian blur parameter.
   int  mGaussBlurCode;

   // Character  parameter.
   int  mCharacterCode;

   // Character table, indexed by neighbor sum.
   Ris::CmdLineTable2D<int, 2, 9>  mCharacterTable;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor,
   typedef Ris::BaseCmdLineExec BaseClass;
   ImageFilterParms();
   void reset();
   void show();

   // Base class override: Execute a command from the command file to set a 
   // member variable. This is called by the associated command file object
   // for each command in the file.
   void execute(Ris::CmdLineCmd* aCmd) override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Helpers.

   static char* asStringFilterType (int aX);
   char* asStringFilterType ();

   bool isGaussBlur() { return mFilterType == cFilterGaussBlur; }
   bool isCharacter() { return mFilterType == cFilterCharacter; }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _SVIMAGEFILTERPARMS_CPP_
   ImageFilterParms gImageFilterParms;
#else
   extern ImageFilterParms gImageFilterParms;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace