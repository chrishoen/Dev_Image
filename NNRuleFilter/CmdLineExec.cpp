
#include "stdafx.h"

#include "svSysParms.h"
#include "svImageParms.h"
#include "svTestParms.h"
#include "svSimParms.h"
#include "svStackParms.h"
#include "svParmParms.h"
#include "displayParms.h"

#include "displayFunctions.h"

#include "displayGraphicsThread.h"

#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}

void CmdLineExec::reset()
{
   mImageSet.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override. Execute a command line command. It calls one of
// the following specific command execution functions. This is called by
// the owner of this object to pass command line commands to it. 

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("Tile"))      executeTile2d(aCmd);
   if (aCmd->isCmd("Show"))    
      executeShow2d(aCmd);

   if (aCmd->isCmd("Tile2d"))    executeTile2d(aCmd);
   if (aCmd->isCmd("Sim2d"))     executeSim2d(aCmd);
   if (aCmd->isCmd("Sim3d"))     executeSim3d(aCmd);
   if (aCmd->isCmd("Run2d"))     executeRun2d(aCmd);
   if (aCmd->isCmd("Run3d"))     executeRun3d(aCmd);
   if (aCmd->isCmd("Show2d"))    executeShow2d(aCmd);
   if (aCmd->isCmd("Show3d"))    executeShow3d(aCmd);
   if (aCmd->isCmd("Draw"))      executeDraw(aCmd);
   if (aCmd->isCmd("Read"))      executeRead(aCmd);
   if (aCmd->isCmd("ReadIn"))    executeReadInput(aCmd);
   if (aCmd->isCmd("Write"))     executeWrite(aCmd);
   if (aCmd->isCmd("WriteOut"))  executeWriteOutput(aCmd);

   if (aCmd->isCmd("GO1"))       executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))       executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))       executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))       executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))       executeGo5(aCmd);
   if (aCmd->isCmd("Parms"))     executeParms(aCmd);
   if (aCmd->isCmd("Parms2"))    executeParms2(aCmd);
   if (aCmd->isCmd("Parms3"))    executeParms3(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 2);
   aCmd->setArgDefault(2, 3);
   aCmd->setArgDefault(3, 5);

   int tLoopRow = aCmd->argInt(1);
   int tNumRow = aCmd->argInt(2);
   int tNumCol = aCmd->argInt(3);

   int tRowCount = tLoopRow * tNumRow - tNumRow / 2;
   int tColCount = tLoopRow * tNumCol - tNumCol / 2;

   for (int tRow = 0; tRow < tRowCount; tRow++)
   {
      int tRowIndex = (tRow + tNumRow / 2) / tNumRow;
      printf("Row %3d\n", tRowIndex);
      printf("           ");
      for (int tCol = 0; tCol < tColCount; tCol++)
      {
         int tColIndex = (tCol + tNumCol / 2) / tNumCol;
         bool tFlag = tColIndex <= tLoopRow - tRowIndex - 1;
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

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTile2d(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   int tReverseIndex = aCmd->argInt(1);
   // Run.
   SV::gTestParms.mTileParms.doAdjust(tReverseIndex);
   mImageSet.doSimInputTile2d();

   SV::gImageParms.mRoiCenter = SV::gTestParms.mTileParms.getReverseRoiCenter(tReverseIndex);
   mImageSet.doShow2d(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeSim2d(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   // Run.
   mImageSet.doSimInput2d();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeSim3d(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   // Run.
   mImageSet.doSimInput3d();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun2d(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   // Run.
   mImageSet.doSimInput2d();
   mFilter2d.initialize(&SV::gImageParms.mNN2dRuleFilterParms);
   mFilter2d.doFilterImage(mImageSet.mInputS2, mImageSet.mOutput);

   Prn::print(0, "done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun3d(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   // Run.
   mImageSet.doSimInput3d();
   mFilter3d.initialize(&SV::gImageParms.mNN3dRuleFilterParms);
   mFilter3d.doFilterImage(
      mImageSet.mInputS1,
      mImageSet.mInputS2, 
      mImageSet.mInputS3, 
      mImageSet.mOutput);

   mFilter3d.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow2d(Ris::CmdLineCmd* aCmd)
{
   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   aCmd->setArgDefault(1, 1);
   mImageSet.doShow2d(aCmd->argInt(1));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow3d(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0);
   int tCode = aCmd->argInt(1);

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   switch (tCode)
   {
   case 0:
      mImageSet.doShow3d(1);
      mImageSet.doShow3d(2);
      break;
   case 1:
      mImageSet.doShow3d(1);
      break;
   case 2:
      mImageSet.doShow3d(2);
      break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeDraw(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);
   mImageSet.doDraw(aCmd->argInt(1));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRead(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   // Run.
   mImageSet.doReadInput();
   mImageSet.doReadOutput();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeReadInput(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 1);

   // Read parameters files.
   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   // Run.
   mImageSet.doReadInput();
   mFilter2d.initialize(&SV::gImageParms.mNN2dRuleFilterParms);
   mFilter2d.doFilterImage(mImageSet.mInputS2, mImageSet.mOutput);
   Prn::print(0, "done");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeWrite(Ris::CmdLineCmd* aCmd)
{
   mImageSet.doWriteInput();
   mImageSet.doWriteOutput();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeWriteOutput(Ris::CmdLineCmd* aCmd)
{
   mImageSet.doWriteOutput();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
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

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   SV::gSysParms.reset();
   SV::gSysParms.readSection("default");
   SV::gSysParms.show();

   Display::gParms.reset();
   Display::gParms.readSection("default");
   Display::gParms.show();

   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   SV::gImageParms.show();
   SV::gSimParms.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms2(Ris::CmdLineCmd* aCmd)
{
   SV::gSysParms.reset();
   SV::gSysParms.readSection("default");

   Display::gParms.reset();
   Display::gParms.readSection("default");

   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   // SV::gImageParms.show();
   SV::gSimParms.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms3(Ris::CmdLineCmd* aCmd)
{
   SV::gSysParms.reset();
   SV::gSysParms.readSection("default");

   SV::gParmParms.reset();
   SV::gParmParms.readSection("default");
   SV::gParmParms.readMoreParms("default");

   SV::gTestParms.show();
}

