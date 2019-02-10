/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "svSysParms.h"

#include "svSimImageGenPolygon.h"

namespace SV
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

SimImageGenPolygon::SimImageGenPolygon()
{
   reset();
}

SimImageGenPolygon::SimImageGenPolygon(SimImageGenParms* aParms)
{
   BaseClass::mP = aParms;
   reset();
}

void SimImageGenPolygon::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the image, depending on the parms.

void SimImageGenPolygon::doGenerateImage(
   cv::Mat&       aImage)          // Output
{
   Prn::print(0, "SimImageGenPolygon::doGenerateImage");
   // Create an image filled with all zeros.
   BaseClass::doCreateZeroImage(aImage);

   // Polygon variables. 
   int tNumPoints = mP->mPolygonPoints.mRows;
   cv::Point* tPoints = new cv::Point[tNumPoints];
   for (int i = 0; i < tNumPoints; i++)
   {
      tPoints[i].x = mP->mPolygonPoints[i][1];
      tPoints[i].y = mP->mPolygonPoints[i][0];
   }
   cv::Scalar tColor(255.0);
   int tLineType = 8;
   int tShift = 0;

   // Draw polygon.
   cv::fillConvexPoly(
      aImage,
      tPoints,
      tNumPoints,
      tColor,
      tLineType,
      tShift);

   // Done.
   delete tPoints;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

