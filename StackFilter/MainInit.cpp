
#include "stdafx.h"

#include "tsThreadServices.h"
#include "risThreadsProcess.h"
#include "MainPrint.h"

#include "CPrintDir.h"
#include "cxFileManager.h"

#include "svSysParms.h"
#include "displayParms.h"
#include "svParmParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program resources.

void main_initialize(int argc,char** argv)
{
   printf("StackFilter Program********************************************BEGIN\n");
   printf("StackFilter Program********************************************BEGIN\n");
   printf("StackFilter Program********************************************BEGIN\n\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize thread services.

   TS::reset();
   TS::setProgramName("StackFilter");
   TS::setProgramPrintLevel(TS::PrintLevel(0, 3));
   TS::initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Enter process.

   // Set program process for high priority.
   Ris::Threads::enterProcessHigh();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Enter process.

   // Set the program working directory to the cprint directory path.
   CPrint::setProgramDir();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize print facility.

   // Initialize print.
   Prn::resetPrint();
// Prn::useConsole(1);
   Prn::initializePrint();

   // Initialize print filters.
   set_print_filters(1);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read parameters files.

   // Read parameters files.
   SV::gSysParms.reset();
   SV::gSysParms.readSection("default");

   // Read parameters files.
   Display::gParms.reset();
   Display::gParms.readSection("default");

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize program resources.

   // Initialize the file manager.
   CX::gFileManager.initialize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize.

void main_finalize()
{
   // Finalize print facility.
   Prn::finalizePrint();

   // Exit process.
   Ris::Threads::exitProcess();

   // Finalize thread services.
   TS::finalize();

   // Done.
   printf("\n");
   printf("StackFilter Program********************************************END\n\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
