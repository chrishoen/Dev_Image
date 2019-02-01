
#include "stdafx.h"

#include "svSysParms.h"
#include "svImageParms.h"
#include "svSimParms.h"
#include "displayParms.h"

#include "Simulate.h"

#include "displayGraphicsThread.h"

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
   if (aCmd->isCmd("Run1"))      executeRun1(aCmd);
   if (aCmd->isCmd("Run2"))      executeRun2(aCmd);
   if (aCmd->isCmd("Show"))      executeShow(aCmd);
   if (aCmd->isCmd("D0"))        executeDraw0(aCmd);
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

void CmdLineExec::executeRun1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   // Read parameters files.
   SV::gImageParms.reset();
   SV::gImageParms.readSection("Default");

   SV::gSimParms.reset();
   SV::gSimParms.readSection("default");

   mSim.doRun1();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   // Read parameters files.
   SV::gImageParms.reset();
   SV::gImageParms.readSection("Default");

   SV::gSimParms.reset();
   SV::gSimParms.readSection("default");

   mSim.doRun2();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   mSim.doShow(aCmd->argInt(1));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeDraw0(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);
   int tCode = aCmd->argInt(1);

   Display::gGraphicsThread->postDraw0(tCode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
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

   SV::gSimParms.reset();
   SV::gSimParms.readSection("default");
   SV::gSimParms.show();

   SV::gImageParms.reset();
   SV::gImageParms.readSection("default");
   SV::gImageParms.show();
}

