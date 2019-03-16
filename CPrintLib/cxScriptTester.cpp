/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cxScriptTester.h"

namespace CX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

ScriptTester::ScriptTester()
{
   reset();
}

void ScriptTester::reset()
{
   mReadCount = 0;
   mCountNone = 0;
   mCountSend = 0;
   mCountSlice = 0;
   mCountSliceExists = 0;
   mCountPWM = 0;
   mCountTest = 0;
   mCountState1 = 0;
   mCountState2 = 0;
   mCountState3 = 0;
   mCountInfo = 0;
   mCountError = 0;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Test a script file. Return true if successful.

bool ScriptTester::doTestScriptFile(std::string& aScriptFilePath)
{
   // Do this first.
   reset();

   // Open the script file.
   if (!mReader.doOpenFile(aScriptFilePath)) return false;

   // Loop to test the script file.
   while (true)
   {
      // Read from the file. Exit if end of file.
      if (!mReader.doRead()) break;
      mReadCount++;

      // Test the command code.
      switch (mReader.mCmdCode)
      {
      case cScriptCmd_None:
      {
         mCountNone++;
      }
      break;
      case cScriptCmd_Send:
      {
         mCountSend++;
      }
      break;
      case cScriptCmd_Slice:
      {
         mCountSlice++;
         if (Ris::portableFilePathExists(mReader.mString))
         {
            mCountSliceExists++;
         }
         else
         {
            mCountError++;
            Prn::print(0, "ERROR slice file does not exist $$ %s", mReader.mString);
         }
      }
      break;
      case cScriptCmd_PWM:
      {
         mCountPWM++;
      }
      break;
      case cScriptCmd_Test:
      {
         mCountTest++;
      }
      break;
      case cScriptCmd_State1:
      {
         mCountState1++;
      }
      break;
      case cScriptCmd_State2:
      {
         mCountState1++;
      }
      break;
      case cScriptCmd_State3:
      {
         mCountState1++;
      }
      break;
      case cScriptCmd_Info:
      {
         mCountInfo++;
      }
      break;
      case cScriptCmd_Error:
      {
         mCountError++;
      }
      break;
      }
   }

   // Done.
   mReader.doCloseFile();
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show test results.

void ScriptTester::show()
{
   Prn::print(Prn::View02, "");
   Prn::print(Prn::View02, "ScriptTester Results****************");
   Prn::print(Prn::View02, "ReadCount        %5d", mReadCount);
   Prn::print(Prn::View02, "CountNone        %5d", mCountNone);
   Prn::print(Prn::View02, "CountSend        %5d", mCountSend);
   Prn::print(Prn::View02, "CountSlice       %5d", mCountSlice);
   Prn::print(Prn::View02, "CountSliceExists %5d", mCountSliceExists);
   Prn::print(Prn::View02, "CountPWM         %5d", mCountPWM);
   Prn::print(Prn::View02, "CountTest        %5d", mCountTest);
   Prn::print(Prn::View02, "CountState1      %5d", mCountState1);
   Prn::print(Prn::View02, "CountState2      %5d", mCountState2);
   Prn::print(Prn::View02, "CountState3      %5d", mCountState3);
   Prn::print(Prn::View02, "CountInfo        %5d", mCountInfo);
   Prn::print(Prn::View02, "CountError       %5d", mCountError);

   Prn::print(Prn::View02, "");
   if (mCountError == 0)
   {
      Prn::print(Prn::View02, "ScriptTester PASS");
   }
   else
   {
      Prn::print(0, "ScriptTester FAIL");
   }
   Prn::print(Prn::View02, "");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

