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
   int tCode = aEvent->user.code;

   Prn::print(Prn::Show1, "doVideoDraw1 %d", tCode);

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

      // Set renderer to blue.
      tRet = SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
      if (tRet) throw "SDL_SetRenderDrawColor";

      // Clear the window and make it all blue.
      tRet = SDL_RenderClear(mRenderer);
      if (tRet) throw "SDL_RenderClear";

      // Set renderer to red.
      tRet = SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
      if (tRet) throw "SDL_SetRenderDrawColor";

      // Render the rectangle.
      SDL_Rect tRect = mRectA;
      if (tCode == 0) tRect = mRectA;
      if (tCode == 1) tRect = mRectB;
      SDL_RenderFillRect(mRenderer, &tRect);

      // Render the changes above.
      SDL_RenderPresent(mRenderer);
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
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//name;space