
#include "stdafx.h"

#include "svSysParms.h"
#include "svImageParms.h"
#include "svSimParms.h"
#include "displayParms.h"
#include "displayFunctions.h"

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
   mImageSet.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override. Execute a command line command. It calls one of
// the following specific command execution functions. This is called by
// the owner of this object to pass command line commands to it. 

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("Run"))       executeRun(aCmd);
   if (aCmd->isCmd("Show2d"))    executeShow2d(aCmd);
   if (aCmd->isCmd("Draw"))      executeDraw(aCmd);
   if (aCmd->isCmd("Read"))      executeRead(aCmd);
   if (aCmd->isCmd("ReadIn"))    executeReadInput(aCmd);
   if (aCmd->isCmd("Write"))     executeWrite(aCmd);
   if (aCmd->isCmd("WriteOut"))  executeWriteOutput(aCmd);

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

void CmdLineExec::executeRun(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   // Read parameters files.
   SV::gSimParms.reset();
   SV::gSimParms.readSection("default");
   SV::gImageParms.reset();
   SV::gImageParms.readSection("default");
   SV::gImageParms.readOverrides(&SV::gSimParms);

   // Run.
   mImageSet.doSimInput();
   mFilter2d.initialize(&SV::gImageParms.mNN2dRuleFilterParms);
   mFilter2d.doFilterImage(mImageSet.mInputImageC, mImageSet.mOutputImage);

   Prn::print(0, "done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow2d(Ris::CmdLineCmd* aCmd)
{
   // Read parameters files.
   SV::gSimParms.reset();
   SV::gSimParms.readSection("default");
   SV::gImageParms.reset();
   SV::gImageParms.readSection("default");
   SV::gImageParms.readOverrides(&SV::gSimParms);

   aCmd->setArgDefault(1, 1);
   mImageSet.doShow2d(aCmd->argInt(1));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeDraw(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   mImageSet.doDraw(aCmd->argInt(1));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRead(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   // Read parameters files.
   SV::gSimParms.reset();
   SV::gSimParms.readSection("default");
   SV::gImageParms.reset();
   SV::gImageParms.readSection("default");
   SV::gImageParms.readOverrides(&SV::gSimParms);

   // Run.
   mImageSet.doReadInput();
   mImageSet.doReadOutput();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeReadInput(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   // Read parameters files.
   SV::gSimParms.reset();
   SV::gSimParms.readSection("default");
   SV::gImageParms.reset();
   SV::gImageParms.readSection("default");
   SV::gImageParms.readOverrides(&SV::gSimParms);

   // Run.
   mImageSet.doReadInput();
   mFilter2d.initialize(&SV::gImageParms.mNN2dRuleFilterParms);
   mFilter2d.doFilterImage(mImageSet.mInputImageC, mImageSet.mOutputImage);
   Prn::print(0, "done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeWrite(Ris::CmdLineCmd* aCmd)
{
   mImageSet.doWriteInput();
   mImageSet.doWriteOutput();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeWriteOutput(Ris::CmdLineCmd* aCmd)
{
   mImageSet.doWriteOutput();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   // Read parameters files.
   SV::gSimParms.reset();
   SV::gSimParms.readSection("default");
   SV::gImageParms.reset();
   SV::gImageParms.readSection("default");
   SV::gImageParms.readOverrides(&SV::gSimParms);

   // Run.
   mImageSet.doSimInput();
   mImageSet.doWriteInput();
   mImageSet.doDraw(12);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   std::vector<int> tList(10);
   tList.clear();
   tList.reserve(10);
   Prn::print(0, "size %d", tList.size());
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

   SV::gImageParms.reset();
   SV::gImageParms.readSection("default");
   SV::gImageParms.readOverrides(&SV::gSimParms);
   SV::gImageParms.show();

   SV::gSimParms.reset();
   SV::gSimParms.readSection("default");
   SV::gSimParms.show();
}

