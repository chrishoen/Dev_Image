/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svImageParms.h"

#include "svContourShow.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show record list.

void showRecordList(
   int                  aPF,           // Input
   const char*          aLabel,        // Input
   ContourRecordList&   aRecordList)   // Input
{
   Prn::print(aPF, "RecordList %-12s %4d", aLabel, aRecordList.size());
   for (int i = 0; i < aRecordList.size(); i++)
   {
      Prn::print(aPF, "Record %4d $ %4d %4d",
         i,
         aRecordList[i].mXX.mRow,
         aRecordList[i].mXX.mCol);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
