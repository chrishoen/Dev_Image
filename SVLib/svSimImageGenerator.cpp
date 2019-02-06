/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSimImageGenCircle.h"
#include "svSimImageGenSquare.h"
#include "svSimImageGenImpulse.h"
#include "svSimImageGenGaussian.h"
#include "svSimImageGenPolygon.h"
#include "svSimImageGenBitMap.h"

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
   mSimImageGen = 0;
   initialize(aParms);
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

   // Create specific image generator.
   mSimImageGen = 0;
   switch (mP->mImageType)
   {
   case SimImageGenParms::cImageCircle :   mSimImageGen = new SimImageGenCircle(mP); return;
   case SimImageGenParms::cImageSquare:    mSimImageGen = new SimImageGenSquare(mP); return;
   case SimImageGenParms::cImageImpulse:   mSimImageGen = new SimImageGenImpulse(mP); return;
   case SimImageGenParms::cImageGaussian:  mSimImageGen = new SimImageGenGaussian(mP); return;
   case SimImageGenParms::cImagePolygon:   mSimImageGen = new SimImageGenPolygon(mP); return;
   case SimImageGenParms::cImageBitMap:    mSimImageGen = new SimImageGenBitMap(mP); return;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the image, depending on the parms.

void SimImageGenerator::doGenerateImage(
   cv::Mat&       aImage)     // Output
{
   // Guard.
   if (mSimImageGen == 0)
   {
      Prn::print(0, "SimImageGenerator::doGenerateImage ERROR 101");
      return;
   }

   // Generate an image using the specific image generator.
   mSimImageGen->doGenerateImage(
      aImage);                // Output
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace