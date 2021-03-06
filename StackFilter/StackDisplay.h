#pragma once
/*==============================================================================
printer executive - script file tester.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <string>

#include "cxScriptReader.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encalsulates a script file tester. It uses the script file
// reader to test a script file.

class StackDisplay
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Parameterized functions and variables.
   CX::ScriptReader   mReader;

   // Metrics.
   int mReadCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   StackDisplay();
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Test a script file. Return true if successful.
   bool doTestScriptFile(std::string& aScriptFilePath);

   // Show test results.
   void show();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************




