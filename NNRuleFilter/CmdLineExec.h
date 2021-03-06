#pragma once

/*==============================================================================
Program command line executive.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineExec.h"
#include "ImageSet.h"
#include "svNN2dRuleFilter.h"
#include "svNN3dRuleFilter.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class is the program command line executive. It processes user
// command line inputs and executes them. It inherits from the command line
// command executive base class, which provides an interface for executing
// command line commands. It provides an override execute function that is
// called by a console executive when it receives a console command line input.
// The execute function then executes the command.

class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   ImageSet mImageSet;
   SV::NN2dRuleFilter mFilter2d;
   SV::NN3dRuleFilter mFilter3d;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   CmdLineExec();
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Base class override. Execute a command line command. It calls one of
   // the following specific command execution functions. This is called by
   // the owner of this object to pass command line commands to it. 
   void execute(Ris::CmdLineCmd* aCmd) override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Execute specific commands.
   void executeTile2d      (Ris::CmdLineCmd* aCmd);
   void executeSim2d       (Ris::CmdLineCmd* aCmd);
   void executeSim3d       (Ris::CmdLineCmd* aCmd);
   void executeRun2d       (Ris::CmdLineCmd* aCmd);
   void executeRun3d       (Ris::CmdLineCmd* aCmd);
   void executeShow2d      (Ris::CmdLineCmd* aCmd);
   void executeShow3d      (Ris::CmdLineCmd* aCmd);
   void executeDraw        (Ris::CmdLineCmd* aCmd);
   void executeRead        (Ris::CmdLineCmd* aCmd);
   void executeReadInput   (Ris::CmdLineCmd* aCmd);
   void executeWrite       (Ris::CmdLineCmd* aCmd);
   void executeWriteOutput (Ris::CmdLineCmd* aCmd);

   void executeGo1(Ris::CmdLineCmd* aCmd);
   void executeGo2(Ris::CmdLineCmd* aCmd);
   void executeGo3(Ris::CmdLineCmd* aCmd);
   void executeGo4(Ris::CmdLineCmd* aCmd);
   void executeGo5(Ris::CmdLineCmd* aCmd);
   void executeParms(Ris::CmdLineCmd* aCmd);
   void executeParms2(Ris::CmdLineCmd* aCmd);
   void executeParms3(Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

