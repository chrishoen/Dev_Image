
#include "stdafx.h"

#include "CPrintDir.h"
#include "svSysParms.h"
#include "svImageParms.h"
#include "svSimParms.h"
#include "svParmParms.h"
#include "displayParms.h"
#include "displayFunctions.h"
#include "Simulate.h"

#include "pxFileManager.h"
#include "pxScriptWriter.h"
#include "pxScriptReader.h"
#include "pxScriptTester.h"

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
   if (aCmd->isCmd("Sim"))       executeSim(aCmd);
   if (aCmd->isCmd("DirZ"))      executeDirZip(aCmd);
   if (aCmd->isCmd("LoadZ"))     executeLoadZip(aCmd);

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

void CmdLineExec::executeSim(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   // Run.
   Simulate tSim;
   tSim.doSimStack();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeDirZip(Ris::CmdLineCmd* aCmd)
{
   PX::gFileManager.getZipNameList();
   PX::gFileManager.showZipNameList();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeLoadZip(Ris::CmdLineCmd* aCmd)
{
   bool tPass = false;

   // Load the zip.
   if (aCmd->isArgNumber(1))
   {
      tPass = PX::gFileManager.doLoadZip(aCmd->argInt(1));
   }
   else
   {
      tPass = PX::gFileManager.doLoadZip(aCmd->argString(1));
   }
   if (!tPass) return;

   // Find the gcode name.
   tPass = PX::gFileManager.doFindWorkGCodeName();
   if (!tPass) return;

   // Write the script.
   PX::ScriptWriter tScriptWriter;
   tPass = tScriptWriter.doWrite(
      PX::gFileManager.mWorkGCodeFilePath,
      PX::gFileManager.mWorkSliceFilePrefixPath,
      PX::gFileManager.mWorkDirPath,
      PX::gFileManager.mWorkScriptFilePath);
   if (!tPass) return;

   // Test the script.
   PX::ScriptTester tScriptTester;
   tPass = tScriptTester.doTestScriptFile(PX::gFileManager.mWorkScriptFilePath);
   if (!tPass) return;

   // Show the test results.
   tScriptTester.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   aCmd->setArgDefault(2, 1);

   int tMod = aCmd->argInt(1);
   int tDelta = aCmd->argInt(2);
   int tValue = 0;

   for (int i = 0; i < 10; i++)
   {
      Prn::print(0, "%3d %3d ", i, tValue);
      if ((i + tMod - 1) % tMod == 0) tValue += tDelta;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   // Clean the cprint work directory.
   CPrint::doCleanWork();
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

