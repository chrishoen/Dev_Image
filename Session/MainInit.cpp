#include "stdafx.h"
#include "risPortableCalls.h"
#include "CPrintDir.h"
#include "cxFileManager.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void main_initialize(int argc,char** argv)
{
   printf("Session Program**************************************BEGIN\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Program arguments.

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

   // Initialize print facility.
   Prn::resetPrint();
   Prn::initializePrint();

   // Initialize print filters
   Prn::setFilter(Prn::ThreadRun1,  true);
   Prn::setFilter(Prn::ThreadRun2,  false);
   Prn::setFilter(Prn::ThreadRun3,  true);
   Prn::setFilter(Prn::ThreadRun4,  true);

   Prn::setFilter(Prn::ProcRun1,    true);
   Prn::setFilter(Prn::ProcRun2,    true);
   Prn::setFilter(Prn::ProcRun3,    false);
   Prn::setFilter(Prn::ProcRun4,    true);

   Prn::setFilter(Prn::View01,      true);
   Prn::setFilter(Prn::View02,      true);


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read parameters files.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize program resources.

   // Initialize the file manager.
   CX::gFileManager.initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize.

void main_finalize()
{
   // Close print facility.
   Prn::finalizePrint();

   printf("Session Program**************************************END\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

