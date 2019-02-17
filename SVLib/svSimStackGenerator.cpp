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
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the image, depending on the parms.

void SimStackGenerator::doGenerateStack()
{
   Prn::print(0, "SimStackGenerator::doGenerateStack");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace