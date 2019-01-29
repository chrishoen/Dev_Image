/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSimImageGenCircle.h"
//#include "svSimImageGenSquare.h"

#include "svSimImageGenerator.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Infastruccture.

SimImageGenerator::SimImageGenerator()
{
   mSimImageGen = 0;
}

SimImageGenerator::~SimImageGenerator()
{
   finalize();
}

SimImageGenerator::SimImageGenerator(SimImageGenParms* aParms)
{
   initialize(mP);
}

void SimImageGenerator::finalize()
{
   if (mSimImageGen)
   {
      delete mSimImageGen;
      mSimImageGen = 0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SimImageGenerator::initialize(SimImageGenParms* aParms)
{
   // Deallocate memory, if already allocated.
   finalize();

   // Store parms.
   mP = aParms;

   // Instantiate specific image generator type selected from the parms.
   switch (mP->mImageType)
   {
   case SimImageGenParms::cImageCircle :   mSimImageGen = new SimImageGenCircle(mP); return;
// case SimImageGenParms::cImageSquare :   mSimImageGen = new SimImageGenSquare(mP); return;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the image, depending on the parms.

void SimImageGenerator::doGenerateImage(
   cv::Mat&       aImage)     // Output
{
   mSimImageGen->doGenerateImage(
      aImage);                // Output
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace