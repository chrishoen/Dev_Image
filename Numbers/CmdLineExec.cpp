
#include "stdafx.h"

#include "svPixelFunctions.h"
#include "svRCIndex.h"
#include "svRCLoop.h"
#include "CmdLineExec.h"

using namespace std;

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("GO1"))   executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))   executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))   executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))   executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))   executeGo5(aCmd);
   if (aCmd->isCmd("GO6"))   executeGo6(aCmd);
   if (aCmd->isCmd("GO7"))   executeGo7(aCmd);
   if (aCmd->isCmd("GO8"))   executeGo8(aCmd);
   if (aCmd->isCmd("GO9"))   executeGo9(aCmd);
   if (aCmd->isCmd("GO11"))  executeGo11(aCmd);
   if (aCmd->isCmd("GO12"))  executeGo12(aCmd);
   if (aCmd->isCmd("GO13"))  executeGo13(aCmd);
   if (aCmd->isCmd("GO14"))  executeGo14(aCmd);
   if (aCmd->isCmd("GO21"))  executeGo21(aCmd);
   if (aCmd->isCmd("GO22"))  executeGo22(aCmd);
   if (aCmd->isCmd("GO23"))  executeGo23(aCmd);
   if (aCmd->isCmd("GO24"))  executeGo24(aCmd);
   if (aCmd->isCmd("GO31"))  executeGo31(aCmd);
   if (aCmd->isCmd("GO32"))  executeGo32(aCmd);
   if (aCmd->isCmd("GO33"))  executeGo33(aCmd);
   if (aCmd->isCmd("GO34"))  executeGo34(aCmd);

   if(aCmd->isCmd("Parms"  ))  executeParms(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, true);
   aCmd->setArgDefault(2, true);

   SV::RCIndexLoop tLoop(4, 4);
   tLoop.mRowForward = aCmd->argBool(1);
   tLoop.mColForward = aCmd->argBool(2);
   for (tLoop.first(); tLoop.test(); tLoop.next())
   {
      Prn::print(0, "Loop %3d %3d", tLoop.mRow, tLoop.mCol);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, true);

   SV::RCIndexLoop tLoop(4, 4);
   tLoop.mRowForward = aCmd->argBool(1);
   for (tLoop.firstRow(); tLoop.testRow(); tLoop.nextRow())
   {
      Prn::print(0, "Loop %3d %3d", tLoop.mRow, tLoop.mCol);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, true);

   SV::RCIndexLoop tLoop(4, 4);
   tLoop.mColForward = aCmd->argBool(1);
   for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
   {
      Prn::print(0, "Loop %3d %3d", tLoop.mRow, tLoop.mCol);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, true);
   aCmd->setArgDefault(2, true);

   SV::RCIndexLoop tLoop(4, 4);
   tLoop.mRowForward = aCmd->argBool(1);
   tLoop.mColForward = aCmd->argBool(2);
   for (tLoop.firstRow(); tLoop.testRow(); tLoop.nextRow())
   {
      for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
      {
         Prn::print(0, "Loop %3d %3d", tLoop.mRow, tLoop.mCol);
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, true);
   aCmd->setArgDefault(2, true);

   SV::RCIndexLoop tLoop(4, 4);
   tLoop.mColForward = aCmd->argBool(1);
   tLoop.mRowForward = aCmd->argBool(2);
   for (tLoop.firstCol(); tLoop.testCol(); tLoop.nextCol())
   {
      for (tLoop.firstRow(); tLoop.testRow(); tLoop.nextRow())
      {
         Prn::print(0, "Loop %3d %3d", tLoop.mRow, tLoop.mCol);
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
   SV::RCIndexLoop tLoop(4, 4);
   do
   {
      Prn::print(0, "Loop %3d %3d", tLoop.mRow, tLoop.mCol);
   } while (tLoop.advance());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo7(Ris::CmdLineCmd* aCmd)
{
   SV::RCIndexLoop tLoop(4, 4);
   while (tLoop.loop())
   {
      Prn::print(0, "Loop %3d %3d", tLoop.mRow, tLoop.mCol);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo8(Ris::CmdLineCmd* aCmd)
{
   SV::RCIndexLoop tLoop(4, 4);
   for (; tLoop.test(); tLoop.next())
   {
      Prn::print(0, "Loop %3d %3d", tLoop.mRow, tLoop.mCol);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo9(Ris::CmdLineCmd* aCmd)
{
   SV::RCIndexLoop tLoop(4, 4);
   for (; tLoop.testRow(); tLoop.nextRow())
   {
      Prn::print(0, "");
      Prn::print(0, "LoopRow %3d %3d", tLoop.mRow, tLoop.mCol);
      for (; tLoop.testCol(); tLoop.nextCol())
      {
         Prn::print(0, "Loop    %3d %3d", tLoop.mRow, tLoop.mCol);
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo11(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);
   aCmd->setArgDefault(2,1);

   SV::RCDitherLoop1 tDitherLoop(aCmd->argInt(1),aCmd->argInt(2));
   do
   {
      Prn::print(0,"DitherLoop1 %3d %3d",tDitherLoop.mRow,tDitherLoop.mCol);
   } while(tDitherLoop.advance());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo12(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);
   aCmd->setArgDefault(2,1);

   SV::RCDitherLoop2 tDitherLoop(aCmd->argInt(1),aCmd->argInt(2));
   do
   {
      Prn::print(0,"DitherLoop2 %3d %3d",tDitherLoop.mRow,tDitherLoop.mCol);
   } while(tDitherLoop.advance());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo13(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   aCmd->setArgDefault(2, 1);

   SV::RCDitherLoop1 tDitherLoop(aCmd->argInt(1), aCmd->argInt(2));
   while (tDitherLoop.loop())
   {
      Prn::print(0, "DitherLoop1 %3d %3d", tDitherLoop.mRow, tDitherLoop.mCol);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo14(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   aCmd->setArgDefault(2, 1);

   SV::RCDitherLoop2 tDitherLoop(aCmd->argInt(1), aCmd->argInt(2));
   while (tDitherLoop.loop())
   {
      Prn::print(0, "DitherLoop2 %3d %3d", tDitherLoop.mRow, tDitherLoop.mCol);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo21(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   aCmd->setArgDefault(2, 1);

   SV::RCDitherLoop1 tDitherLoop(aCmd->argInt(1), aCmd->argInt(2));
   for (tDitherLoop.first(); tDitherLoop.test(); tDitherLoop.next())
   {
      Prn::print(0, "DitherLoop1 %3d %3d", tDitherLoop.mRow, tDitherLoop.mCol);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo22(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   aCmd->setArgDefault(2, 1);

   SV::RCDitherLoop2 tDitherLoop(aCmd->argInt(1), aCmd->argInt(2));
   for (tDitherLoop.first(); tDitherLoop.test(); tDitherLoop.next())
   {
      Prn::print(0, "DitherLoop2 %3d %3d", tDitherLoop.mRow, tDitherLoop.mCol);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo23(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo24(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo31(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   int tCount = 0;

   SV::RCCircuitLoop tCircuitLoop(SV::RCIndex(100, 200), aCmd->argInt(1));
   do
   {
      Prn::print(0, "CircuitLoop %3d %3d $$ %3d %3d", tCount++, tCircuitLoop.mSide, tCircuitLoop.mRow, tCircuitLoop.mCol);
   } while (tCircuitLoop.advance());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo32(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   int tCount = 0;

   SV::RCCircuitLoop tCircuitLoop(SV::RCIndex(100,200),aCmd->argInt(1));
   while (tCircuitLoop.loop())
   {
      Prn::print(0, "CircuitLoop %3d %3d $$ %3d %3d", tCount++, tCircuitLoop.mSide, tCircuitLoop.mRow, tCircuitLoop.mCol);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo33(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   int tCount = 0;

   SV::RCCircuitLoop tCircuitLoop(aCmd->argInt(1));
   for (tCircuitLoop.first(); tCircuitLoop.test(); tCircuitLoop.next())
   {
      Prn::print(0, "CircuitLoop %3d %3d $$ %3d %3d", tCount++, tCircuitLoop.mSide, tCircuitLoop.mRow, tCircuitLoop.mCol);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo34(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,"NumberGrid");
}

