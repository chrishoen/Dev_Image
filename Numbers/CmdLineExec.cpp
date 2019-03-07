
#include "stdafx.h"

#include "svSysParms.h"
#include "svTestParms.h"
#include "svRCSector.h"

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
// Base class override. Execute a command line command. It calls one of
// the following specific command execution functions. This is called by
// the owner of this object to pass command line commands to it. 

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("GO1"))       executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))       executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))       executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))       executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))       executeGo5(aCmd);
   if (aCmd->isCmd("Dia"))       executeDiamond(aCmd);
   if (aCmd->isCmd("Parms"))     executeParms(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   aCmd->setArgDefault(2, 1);

   int tNumLoop = 10;
   int tH = aCmd->argInt(1);
   int tV = aCmd->argInt(2);

   for (int tN = 0; tN < tNumLoop; tN++)
   {
      int tP1 = tH * (tN / tV);

      printf("%3d   %3d\n", tN,tP1);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   SV::gTestParms.reset();
   SV::gTestParms.readSection("default");

   aCmd->setArgDefault(1, 1);
   for (int tN = 0; tN < 10; tN++)
   {
      SV::gTestParms.mTileParms.adjust(tN);
      printf("NumLoop   %3d %3d $ %3d\n", tN,
         SV::gTestParms.mTileParms.mNumLoop,
         SV::gTestParms.mTileParms.mB);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   SV::RCSector tSector(SV::gTestParms.mCorner, SV::gTestParms.mCenter);
   tSector.show1(0, "MySector");
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

void CmdLineExec::executeDiamond(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 2);
   aCmd->setArgDefault(2, 3);
   aCmd->setArgDefault(3, 5);

   int tNumLoop = aCmd->argInt(1);
   int tNumRow = aCmd->argInt(2);
   int tNumCol = aCmd->argInt(3);

   int tRowCount = tNumLoop * tNumRow - tNumRow / 2;
   int tColCount = tNumLoop * tNumCol - tNumCol / 2;

   for (int tRow = 0; tRow < tRowCount; tRow++)
   {
      int tRowIndex = (tRow + tNumRow / 2) / tNumRow;
      printf("Row %3d\n", tRowIndex);
      printf("           ");
      for (int tCol = 0; tCol < tColCount; tCol++)
      {
         int tColIndex = (tCol + tNumCol / 2) / tNumCol;
         bool tFlag = tColIndex <= tNumLoop - tRowIndex - 1;
         if (tFlag)
         {
            printf("Col  %3d  ", tColIndex);
         }
         else
         {
            printf("...  %3d  ", tColIndex);
         }
      }
      printf("\n");
   }
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   SV::gSysParms.reset();
   SV::gSysParms.readSection("default");
   SV::gSysParms.show();

   SV::gTestParms.reset();
   SV::gTestParms.readSection("default");
   SV::gTestParms.show();
}

