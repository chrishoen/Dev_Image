/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"


#include "risProgramTime.h"
#include "risAlphaDir.h"

#include "displayParms.h"
#include "displayGraphicsThread.h"

namespace Display
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Load the png file and notify the completion. This is called for the 
// posted event.

void GraphicsThread::doVideoDraw1(SDL_Event* aEvent)
{
   // Metrics.
   mStartTime = Ris::getCurrentProgramTime();

   int tRet = 0;
   cv::Mat* tImage = (cv::Mat*)aEvent->user.data1;

   Prn::print(Prn::Show1, "doVideoDraw1  %4d %4d", tImage->rows, tImage->cols);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Draw the image.

   try
   {
      //***************************************************************************
      //***************************************************************************
      //***************************************************************************
      // Draw the window.

      // Create an intel image structure from the opencv image matrix.
      IplImage tIntelImage(*tImage);

      Prn::print(Prn::Show2, "height        %4d", tIntelImage.height);
      Prn::print(Prn::Show2, "width         %4d", tIntelImage.width);
      Prn::print(Prn::Show2, "depth         %4d", tIntelImage.depth);
      Prn::print(Prn::Show2, "nChannels     %4d", tIntelImage.nChannels);
      Prn::print(Prn::Show2, "widthStep     %4d", tIntelImage.widthStep);

      // Create a surface from the intel image.
      SDL_Surface* tSurface = SDL_CreateRGBSurfaceFrom(
         tIntelImage.imageData,
         tIntelImage.width,
         tIntelImage.height,
         tIntelImage.depth*tIntelImage.nChannels,
         tIntelImage.widthStep,
         0xff0000, 0x00ff00, 0x0000ff, 0);
      if (tSurface==0) throw "SDL_SDL_CreateRGBSurfaceFrom";

      // Create a texture from the surface.
      SDL_Texture* tTexture = SDL_CreateTextureFromSurface(
         mRenderer,
         tSurface);
      if (tTexture == 0) throw "SDL_SDL_SDL_CreateTextureFromSurface";

      // Clear the renderer.
      tRet = SDL_RenderClear(mRenderer);
      if (tRet) throw "SDL_RenderClear";

      // Copy the texture to the renderer.
      tRet = SDL_RenderCopy(mRenderer, tTexture, NULL, NULL);
      if (tRet) throw "SDL_RenderCopy";

      // Render the changes above.
      SDL_RenderPresent(mRenderer);

      // Free
      SDL_FreeSurface(tSurface);
      SDL_DestroyTexture(tTexture);
   }
   catch (const char* aString)
   {
      Prn::print(Prn::ThreadRun1, "EXCEPTION %s", aString, SDL_GetError());
      mValidFlag = false;
   }
   // Metrics.
   mStopTime = Ris::getCurrentProgramTime();
   // Print the draw latency.
   if (gParms.mShowCode != 0)
   {
      Prn::print(Prn::Show1, "Latency %6.3f", mStopTime - mStartTime);
   }

   // Done.
   delete tImage;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//name;space