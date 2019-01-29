#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Simulator synthetic image generator.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "svSimImageGenParms.h"
#include "svSimImageGenBase.h"

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a simulator synthetic image generator.

class SimImageGenerator
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Parameters.
   SimImageGenParms* mP;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Pointer to a specific grid generator.
   SimImageGenBase* mSimImageGen;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infrastructure.
   // Instantiate specific grid generator selected from the parms.

   // Constructor.
   SimImageGenerator();
  ~SimImageGenerator();
   SimImageGenerator(SimImageGenParms* aParms);
   void initialize(SimImageGenParms* aParms);
   void finalize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Generate the image, depending on the parms.
   void doGenerateImage(
      cv::Mat&       aImage);          // Output
};

//******************************************************************************
}//namespace


