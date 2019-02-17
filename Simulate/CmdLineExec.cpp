
#include "stdafx.h"

#include "CPrintDir.h"
#include "svSysParms.h"
#include "svImageParms.h"
#include "svSimParms.h"
#include "svParmParms.h"
#include "displayParms.h"
#include "displayFunctions.h"

#include "svSimStackGenerator.h"

#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override. Execute a command line command. It calls one of
// the following specific command execution functions. This is called by
// the owner of this object to pass command line commands to it. 

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("Gen"))       executeGen(aCmd);

   if (aCmd->isCmd("GO1"))       executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))       executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))       executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))       executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))       executeGo5(aCmd);
   if (aCmd->isCmd("Parms"))     executeParms(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGen(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   // Clean the cprint work directory.
   doCleanCPrintWork();

   // Run.
   SV::SimStackGenerator tStackGen(&SV::gSimParms);
   tStackGen.doGenerateImageStack();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   SV::gSysParms.reset();
   SV::gSysParms.readSection("default");
   SV::gSysParms.show();

   Display::gParms.reset();
   Display::gParms.readSection("default");
   Display::gParms.show();

   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   SV::gImageParms.show();
   SV::gSimParms.show();
}

