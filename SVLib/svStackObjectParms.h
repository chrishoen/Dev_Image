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
#include "svRCSector.h"
#include "svTileParms.h"

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

class StackObjectParms : public Ris::BaseCmdLineParms
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static const int cMaxStringSize = 100;
   static const int cMaxTiles = 4;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Object name.
   char mName[cMaxStringSize];

   // If true then valid.
   bool  mValid;

   // Tile enable flags.
   Ris::CmdLineTable1D<bool, cMaxTiles>  mTileEnable;

   // Tile heights.
   Ris::CmdLineTable1D<int, cMaxTiles>  mTileHeight;

   // Tile parameters sections.
   Ris::CmdLineTable1D<Ris::TableString, cMaxTiles>  mTileParmSection;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Expanded members that are not read from the parms file.

   // Tile stack begin and end.
   int mTileBegin[cMaxTiles];
   int mTileEnd[cMaxTiles];

   // Tile parameters.
   TileParms  mTileParms[cMaxTiles];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor,
   typedef Ris::BaseCmdLineParms BaseClass;
   StackObjectParms();
   void reset();
   void show();

   // Base class override: Execute a command from the command file to set a 
   // member variable. This is called by the associated command file object
   // for each command in the file.
   void execute(Ris::CmdLineCmd* aCmd) override;

   // Simulate expanded member variables. This is called after the entire
   // section of the command file has been processed.
   void expand() override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Set the tile sectors.
   void setSector(RCSector& aSector);

   // Return a roi center as a function of a reverse stack index.
   RCIndex getReverseRoiCenter(int aReverseIndex);

   // Return a tile index and a tile stack index as a function of a
   // reverse stack index.
   void getTileIndex(int aReverseIndex,int& aTileIndex, int& aTileReverseIndex);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace