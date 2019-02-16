/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "pxScriptTester.h"

namespace PX
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
         Prn::print(Prn::View04, "NONE  $$ %s", mReader.mString);
         mCountNone++;
      }
      break;
      case cScriptCmd_Send:
      {
         Prn::print(Prn::View04, "SEND  $$ %s", mReader.mString);
         mCountSend++;
      }
      break;
      case cScriptCmd_Slice:
      {
         Prn::print(Prn::View04, "SLICE $$ %s", mReader.mString);
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
         Prn::print(Prn::View04, "PWM    $$ %s", mReader.mString);
         mCountPWM++;
      }
      break;
      case cScriptCmd_Test:
      {
         Prn::print(Prn::View04, "TEST   $$ %s", mReader.mString);
         mCountTest++;
      }
      break;
      case cScriptCmd_State1:
      {
         Prn::print(Prn::View04, "STATE1 $$ %s", mReader.mString);
         mCountState1++;
      }
      break;
      case cScriptCmd_State2:
      {
         Prn::print(Prn::View04, "STATE2 $$ %s", mReader.mString);
         mCountState1++;
      }
      break;
      case cScriptCmd_State3:
      {
         Prn::print(Prn::View04, "STATE3 $$ %s", mReader.mString);
         mCountState1++;
      }
      break;
      case cScriptCmd_Info:
      {
         Prn::print(Prn::View04, "INFO  $$ %s", mReader.mString);
         mCountInfo++;
      }
      break;
      case cScriptCmd_Error:
      {
         Prn::print(Prn::View04, "ERROR $$ %s", mReader.mString);
         mCountError++;
      }
      break;
      }
   }

   // Done.
   return true;
}
//bool portableFilePathExists(char* aFilePath)

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show test results.

void ScriptTester::show()
{
   Prn::print(0, "");
   Prn::print(0, "ScriptTester Results****************");
   Prn::print(0, "ReadCount        %5d", mReadCount);
   Prn::print(0, "CountNone        %5d", mCountNone);
   Prn::print(0, "CountSend        %5d", mCountSend);
   Prn::print(0, "CountSlice       %5d", mCountSlice);
   Prn::print(0, "CountSliceExists %5d", mCountSliceExists);
   Prn::print(0, "CountPWM         %5d", mCountPWM);
   Prn::print(0, "CountTest        %5d", mCountTest);
   Prn::print(0, "CountState1      %5d", mCountState1);
   Prn::print(0, "CountState2      %5d", mCountState2);
   Prn::print(0, "CountState3      %5d", mCountState3);
   Prn::print(0, "CountInfo        %5d", mCountInfo);
   Prn::print(0, "CountError       %5d", mCountError);

   Prn::print(0, "");
   if (mCountError == 0)
   {
      Prn::print(0, "ScriptTester PASS");
   }
   else
   {
      Prn::print(0, "ScriptTester FAIL");
   }
   Prn::print(0, "");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

