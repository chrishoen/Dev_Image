
#include "stdafx.h"

#include "MainPrint.h"
#include "CPrintDir.h"
#include "svSysParms.h"
#include "svImageParms.h"
#include "svImageFunctions.h"
#include "svSimParms.h"
#include "svParmParms.h"
#include "displayParms.h"
#include "displayFunctions.h"
#include "StackSimulate.h"

#include "pxFileManager.h"
#include "pxScriptWriter.h"
#include "pxScriptReader.h"
#include "pxScriptTester.h"
#include "StackEvaluate.h"
#include "StackDisplay.h"
#include "StackFilter.h"
#include "StackShow.h"

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
   if (aCmd->isCmd("Prn"))       set_print_filters(aCmd->argInt(1));
   if (aCmd->isCmd("Sim"))       executeSim(aCmd);
   if (aCmd->isCmd("DirZ"))      executeDirZip(aCmd);
   if (aCmd->isCmd("LoadZ"))     executeLoadZip(aCmd);
   if (aCmd->isCmd("Eval"))      executeEvaluate(aCmd);
   if (aCmd->isCmd("Eval2"))     executeEvaluate2(aCmd);
   if (aCmd->isCmd("Disp"))      executeDisplay(aCmd);
   if (aCmd->isCmd("Filt"))      executeFilter(aCmd);
   if (aCmd->isCmd("Show"))      executeShow(aCmd);

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
   StackSimulate tSim;
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
   tPass = PX::gFileManager.doLoadZip(aCmd->argInt(1));
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

void CmdLineExec::executeEvaluate(Ris::CmdLineCmd* aCmd)
{
   // Load a zip file
   executeLoadZip(aCmd);

   // Test the image stack.
   StackEvaluate tStackEvaluate;

   tStackEvaluate.doTestScriptFile();
   tStackEvaluate.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeEvaluate2(Ris::CmdLineCmd* aCmd)
{
   // Test the image stack.
   StackEvaluate tStackEvaluate;

   tStackEvaluate.doTestScriptFile();
   tStackEvaluate.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeDisplay(Ris::CmdLineCmd* aCmd)
{
   // Load a zip file
   executeLoadZip(aCmd);

   // Test the image stack.
   StackDisplay tStackDisplay;
   tStackDisplay.doTestScriptFile(PX::gFileManager.mWorkScriptFilePath);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeFilter(Ris::CmdLineCmd* aCmd)
{
   // Load a zip file
   executeLoadZip(aCmd);

   // Test the image stack.
   StackFilter tStackFilter;

   tStackFilter.doFilterScriptFile(PX::gFileManager.mZipFilePath);
   tStackFilter.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);

   // Test the image stack.
   StackShow tStackShow;

   tStackShow.doShowScriptFile(aCmd->argInt(1));
   tStackShow.show();
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

