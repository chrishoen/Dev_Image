
#include "stdafx.h"

#include "tsThreadServices.h"
#include "risThreadsProcess.h"

#include "displayParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program resources.

void main_initialize(int argc,char** argv)
{
   printf("DisplayTest Program********************************************BEGIN\n");
   printf("DisplayTest Program********************************************BEGIN\n");
   printf("DisplayTest Program********************************************BEGIN\n\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize thread services.

   TS::reset();
   TS::setProgramName("DisplayTest");
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
   // Initialize print facility.

   // Initialize print.
   Prn::resetPrint();
   Prn::initializePrint();

   // Initialize print filters.
   Prn::setFilter(Prn::ThreadInit1, true);
   Prn::setFilter(Prn::ThreadInit2, false);
   Prn::setFilter(Prn::ThreadRun1, true);
   Prn::setFilter(Prn::ThreadRun2, true);
   Prn::setFilter(Prn::ThreadRun3, true);
   Prn::setFilter(Prn::ThreadRun4, true);

   Prn::setFilter(Prn::View01,          true);
   Prn::setFilter(Prn::View02,          true);
   Prn::setFilter(Prn::View11,          true,  1);
   Prn::setFilter(Prn::View12,          true,  1);
   Prn::setFilter(Prn::View21,          true,  2);
   Prn::setFilter(Prn::View21,          true,  2);

   Prn::setFilter(Prn::Show1, true);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read parameters files.

   // Read parameters files.
   Display::gParms.reset();
   Display::gParms.readSection("Default");
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
   printf("DisplayTest Program********************************************END\n\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
