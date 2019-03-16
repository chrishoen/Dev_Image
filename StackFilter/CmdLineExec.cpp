
#include "stdafx.h"

#include "MainPrint.h"
#include "CPrintDir.h"
#include "svSysParms.h"
#include "svImageParms.h"
#include "svSimParms.h"
#include "svStackParms.h"
#include "svParmParms.h"
#include "displayParms.h"
#include "svImageFunctions.h"

#include "displayFunctions.h"
#include "StackGenerate.h"

#include "cxFileManager.h"
#include "cxScriptWriter.h"
#include "cxScriptReader.h"
#include "cxScriptTester.h"
#include "StackEvaluate.h"
#include "StackDisplay.h"
#include "StackFilter.h"
#include "StackShow.h"

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
   if (aCmd->isCmd("Gen"))       executeGen(aCmd);
   if (aCmd->isCmd("DirZ"))      executeDirZip(aCmd);
   if (aCmd->isCmd("LoadZ"))     executeLoadZip(aCmd);
   if (aCmd->isCmd("EvalZ"))     executeEvaluateZip(aCmd);
   if (aCmd->isCmd("EvalW"))     executeEvaluateWork(aCmd);
   if (aCmd->isCmd("DispZ"))     executeDisplayZip(aCmd);
   if (aCmd->isCmd("FiltZ"))     executeFilterZip(aCmd);
   if (aCmd->isCmd("ShowW"))     executeShowWork(aCmd);

   if (aCmd->isCmd("GO1"))       executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))       executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))       executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))       executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))       executeGo5(aCmd);
   if (aCmd->isCmd("Test1"))     executeTest1(aCmd);
   if (aCmd->isCmd("Test2"))     executeTest2(aCmd);
   if (aCmd->isCmd("Parms"))     executeParms(aCmd);
   if (aCmd->isCmd("Parms2"))    executeParms2(aCmd);
   if (aCmd->isCmd("Parms3"))    executeParms3(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTest1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);
   aCmd->setArgDefault(2, 0);

   int tObjectIndex = 0;
   int tObjectReverseIndex = 0;
   int tReverseIndex = aCmd->argInt(1);

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   //   SV::gTestParms.mTileParms.doAdjust(tReverseIndex);
   SV::RCIndex tRoiCenter = SV::gStackParms.getReverseRoiCenter(tObjectIndex,tReverseIndex);
   printf("ReverseRoiCenter %4d $ %4d %4d\n",
      tReverseIndex,
      tRoiCenter.mRow,
      tRoiCenter.mCol);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTest2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);
   aCmd->setArgDefault(2, 0);

   int tObjectIndex = 0;
   int tObjectStackIndex = 0;
   int tStackIndex = aCmd->argInt(1);

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   //   SV::gTestParms.mTileParms.doAdjust(tStackIndex);
   SV::RCIndex tRoiCenter = SV::gStackParms.getStackRoiCenter(tObjectIndex, tStackIndex);
   printf("StackRoiCenter   %4d $ %4d %4d\n",
      tStackIndex,
      tRoiCenter.mRow,
      tRoiCenter.mCol);
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

   // Run.
   StackGenerate tGen;
   tGen.doGenerateStack();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeDirZip(Ris::CmdLineCmd* aCmd)
{
   CX::gFileManager.getZipNameList();
   CX::gFileManager.showZipNameList();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeLoadZip(Ris::CmdLineCmd* aCmd)
{
   bool tPass = false;

   // Load the zip.
   tPass = CX::gFileManager.doLoadZip(aCmd->argInt(1));
   if (!tPass) return;

   // Find the gcode name.
   tPass = CX::gFileManager.doFindWorkGCodeName();
   if (!tPass) return;

   // Write the script.
   CX::ScriptWriter tScriptWriter;
   tPass = tScriptWriter.doWrite(
      CX::gFileManager.mWorkGCodeFilePath,
      CX::gFileManager.mWorkSliceFilePrefixPath,
      CX::gFileManager.mWorkDirPath,
      CX::gFileManager.mWorkScriptFilePath);
   if (!tPass) return;

   // Test the script.
   CX::ScriptTester tScriptTester;
   tPass = tScriptTester.doTestScriptFile(CX::gFileManager.mWorkScriptFilePath);
   if (!tPass) return;

   // Show the test results.
   tScriptTester.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeEvaluateZip(Ris::CmdLineCmd* aCmd)
{
   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

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

void CmdLineExec::executeEvaluateWork(Ris::CmdLineCmd* aCmd)
{
   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   // Test the image stack.
   StackEvaluate tStackEvaluate;

   tStackEvaluate.doTestScriptFile();
   tStackEvaluate.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeDisplayZip(Ris::CmdLineCmd* aCmd)
{
   // Load a zip file
   executeLoadZip(aCmd);

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   // Test the image stack.
   StackDisplay tStackDisplay;
   tStackDisplay.doTestScriptFile(CX::gFileManager.mWorkScriptFilePath);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeFilterZip(Ris::CmdLineCmd* aCmd)
{
   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   // Load a zip file
   executeLoadZip(aCmd);

   // Test the image stack.
   StackFilter tStackFilter;

   tStackFilter.doFilterScriptFile(CX::gFileManager.mZipFilePath);
   tStackFilter.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShowWork(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);
   aCmd->setArgDefault(2, 0);

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   // Test the image stack.
   StackShow tStackShow;

   tStackShow.doShowScriptFile(aCmd->argInt(1), aCmd->argInt(2));
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
   aCmd->setArgDefault(1, 1);

   SV::gSysParms.reset();
   SV::gSysParms.readSection("default");

   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   SV::gStackParms.show(aCmd->argInt(1));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms2(Ris::CmdLineCmd* aCmd)
{
   SV::gSysParms.reset();
   SV::gSysParms.readSection("default");

   Display::gParms.reset();
   Display::gParms.readSection("default");

   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

// SV::gImageParms.show();
   SV::gSimParms.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms3(Ris::CmdLineCmd* aCmd)
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


