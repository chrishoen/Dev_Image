
#include "stdafx.h"

#include "risPortableCalls.h"
#include "risSystemCalls.h"
#include "CPrintDir.h"

#include "pxFileManager.h"
#include "pxScriptWriter.h"
#include "pxScriptReader.h"
#include "pxScriptTester.h"

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
// This class is the program command line executive. It processes user
// command line inputs and executes them. It inherits from the command line
// command executive base class, which provides an interface for executing
// command line commands. It provides an override execute function that is
// called by a console executive when it receives a console command line input.
// The execute function then executes the command.

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("DirZ"))    executeDirZip(aCmd);
   if (aCmd->isCmd("LoadZ"))   executeLoadZip(aCmd);

   if (aCmd->isCmd("DirG"))    executeDirGCode(aCmd);
   if (aCmd->isCmd("LoadG"))   executeLoadGCode(aCmd);

   if (aCmd->isCmd("SetZ"))    executeSetZip(aCmd);
   if (aCmd->isCmd("SetG"))    executeSetGCode(aCmd);
   if (aCmd->isCmd("FindG"))  executeFindWorkGCode(aCmd);
   if (aCmd->isCmd("Slice"))  executeWorkSlice(aCmd);

   if (aCmd->isCmd("Gen"))    executeGen(aCmd);
   if (aCmd->isCmd("Test"))   executeTest(aCmd);
   if (aCmd->isCmd("Clean"))  executeClean(aCmd);

   if (aCmd->isCmd("GO1"))    executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))    executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))    executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))    executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))    executeGo5(aCmd);
   if (aCmd->isCmd("GO6"))    executeGo6(aCmd);
   if (aCmd->isCmd("GO7"))    executeGo7(aCmd);
   if (aCmd->isCmd("GO8"))    executeGo8(aCmd);
   if (aCmd->isCmd("GO9"))    executeGo9(aCmd);
   if (aCmd->isCmd("Show"))   executeShow(aCmd);
   if (aCmd->isCmd("Parms"))  executeParms(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

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

void CmdLineExec::executeDirGCode(Ris::CmdLineCmd* aCmd)
{
   PX::gFileManager.getGCodeNameList();
   PX::gFileManager.showGCodeNameList();
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

void CmdLineExec::executeLoadGCode(Ris::CmdLineCmd* aCmd)
{
   bool tPass = false;

   // Load the zip.
   if (aCmd->isArgNumber(1))
   {
      tPass = PX::gFileManager.doLoadGCode(aCmd->argInt(1));
   }
   else
   {
      tPass = PX::gFileManager.doLoadGCode(aCmd->argString(1));
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

void CmdLineExec::executeSetZip(Ris::CmdLineCmd* aCmd)
{
   bool tPass = false;

   if (aCmd->isArgNumber(1))
   {
      tPass = PX::gFileManager.setZipName(aCmd->argInt(1));
   }
   else
   {
      tPass = PX::gFileManager.setZipName(aCmd->argString(1));
   }

   if (tPass)
   {
      PX::gFileManager.show2();
   }
   Prn::print(0, "done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeSetGCode(Ris::CmdLineCmd* aCmd)
{
   bool tPass = false;

   if (aCmd->isArgNumber(1))
   {
      tPass = PX::gFileManager.setGCodeName(aCmd->argInt(1));
   }
   else
   {
      tPass = PX::gFileManager.setGCodeName(aCmd->argString(1));
   }

   if (tPass)
   {
      PX::gFileManager.show2();
   }
   Prn::print(0, "done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeFindWorkGCode(Ris::CmdLineCmd* aCmd)
{
   PX::gFileManager.doFindWorkGCodeName();
   Prn::print(0, "done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeWorkSlice(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   std::string tString =  PX::gFileManager.getWorkSliceFilePath(aCmd->argInt(1));
   Prn::print(0, "%s",tString.c_str());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGen(Ris::CmdLineCmd* aCmd)
{
   PX::ScriptWriter tWriter;
   tWriter.doWrite(
      PX::gFileManager.mWorkGCodeFilePath,
      PX::gFileManager.mWorkSliceFilePrefixPath,
      PX::gFileManager.mWorkDirPath,
      PX::gFileManager.mWorkScriptFilePath);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTest(Ris::CmdLineCmd* aCmd)
{
   PX::ScriptTester tTester;
   if (tTester.doTestScriptFile(PX::gFileManager.mWorkScriptFilePath))
   {
      tTester.show();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeClean(Ris::CmdLineCmd* aCmd)
{
   CPrint::doCleanWork();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "%d", sizeof(std::string));
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

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo7(Ris::CmdLineCmd* aCmd)
{
   int tRet = 0;
   tRet = Ris::doSystemCommand("pwd");
   Prn::print(0, "doSystemCommand %d", tRet);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo8(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "program dir %s", Ris::portableGetProgramDir());
   Prn::print(0, "current dir %s", Ris::portableGetCurrentDir());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo9(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   PX::gFileManager.show1();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
}

