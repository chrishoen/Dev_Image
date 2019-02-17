/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSimImageGenPolygon.h"
#include "svSimStackGenerator.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Infastruccture.

SimStackGenerator::SimStackGenerator()
{
}

SimStackGenerator::~SimStackGenerator()
{
   finalize();
}

SimStackGenerator::SimStackGenerator(SimParms* aParms)
{
   initialize(aParms);
}

void SimStackGenerator::finalize()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SimStackGenerator::initialize(SimParms* aParms)
{
   // Deallocate memory, if already allocated.
   finalize();

   // Store parms.
   mP = aParms;

   // Initialize variables.
   mStackSize = 0;
   mImageFilePaths.clear();

   mGenParms.reset();
   mGenPolygon.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate an image stack, depending on the parms.

void SimStackGenerator::doGenerateImageStack()
{
   Prn::print(0, "SimStackGenerator::doGenerateStack");
   // Set the stack size.
   mStackSize = mP->mStackSize;

   // Initialize the file paths.
   doSetImageFilePaths();

   // Initialize the polygon image generator.
   mGenParms.reset();
   mGenParms.mPolygonPoints = mP->mStackPolygonBottom;

   // Loop for each generated image, from bottom to top.
   for (int tLoopIndex = 0; tLoopIndex < mStackSize; tLoopIndex++)
   {
      // File index from top to bottom.
      int tFileIndex = mStackSize - tLoopIndex - 1;

      // Print the polygon points.
      Prn::print(Prn::View01, "%3d $ %4d  %4d $ %4d  %4d $ %4d  %4d $ %4d  %4d",
         tFileIndex,
         mGenParms.mPolygonPoints[0][0], mGenParms.mPolygonPoints[0][1],
         mGenParms.mPolygonPoints[1][0], mGenParms.mPolygonPoints[1][1],
         mGenParms.mPolygonPoints[2][0], mGenParms.mPolygonPoints[2][1],
         mGenParms.mPolygonPoints[3][0], mGenParms.mPolygonPoints[3][1]);

      // Draw the polygon to an image.
      cv::Mat tOutputImage;
      mGenPolygon.initialize(&mGenParms);
      mGenPolygon.doGenerateImage(tOutputImage);

      // Write the image to a file.
      cv::imwrite(mImageFilePaths[tFileIndex].c_str(), tOutputImage);

      // Advance the polygon points.
      for (int n = 0; n < mP->mStackPolygonBottom.mRows; n++)
      {
         mGenParms.mPolygonPoints[n][0] += mP->mStackPolygonDelta[n][0];
         mGenParms.mPolygonPoints[n][1] += mP->mStackPolygonDelta[n][1];
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set the image file paths.

void SimStackGenerator::doSetImageFilePaths()
{
   // Set the stack size.
   mStackSize = mP->mStackSize;
   mImageFilePaths.clear();

   // Set the image file path.
   for (int i = 0; i < mStackSize; i++)
   {
      char tFilePath[200];
      sprintf(tFilePath, ".\\work\\%s%04d.png", mP->mStackName,i);
      Prn::print(Prn::View11,"FilePath %s", tFilePath);
      mImageFilePaths.push_back(tFilePath);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace