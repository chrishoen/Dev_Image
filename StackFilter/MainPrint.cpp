
#include "stdafx.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize print filters.

void set_print_filters(int aCode)
{
   // Set defaults.
   Prn::setFilter(Prn::ThreadInit1, true);
   Prn::setFilter(Prn::ThreadInit2, false);
   Prn::setFilter(Prn::ThreadRun1, true);
   Prn::setFilter(Prn::ThreadRun2, true);
   Prn::setFilter(Prn::ThreadRun3, true);
   Prn::setFilter(Prn::ThreadRun4, true);

   Prn::setFilter(Prn::View01, true);
   Prn::setFilter(Prn::View02, true);
   Prn::setFilter(Prn::View03, true);
   Prn::setFilter(Prn::View04, false);

   Prn::setFilter(Prn::View11, true,  1);
   Prn::setFilter(Prn::View12, true,  1);
   Prn::setFilter(Prn::View21, true,  2);
   Prn::setFilter(Prn::View21, true,  2);

   Prn::setFilter(Prn::Show1, true);

   if (aCode == 0) return;

   if (aCode == 1)
   {
      Prn::setFilter(Prn::View01, true);
      Prn::setFilter(Prn::View02, false);
      Prn::setFilter(Prn::View03, false);
      Prn::setFilter(Prn::View04, true);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
