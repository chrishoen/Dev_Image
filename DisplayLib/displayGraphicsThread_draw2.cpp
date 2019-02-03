/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"


#include "SDL.h"
#include "SDL_image.h"

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

void GraphicsThread::doVideoDraw2(SDL_Event* aEvent)
{
   // Metrics.
   mStartTime = Ris::getCurrentProgramTime();

   int tRet = 0;
   int tCode = aEvent->user.code;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Image png file path and completion notification.

   // Copy the event png filepath into a local.
   std::string* tEventFilePath = (std::string*)aEvent->user.data1;
   char tFilePath[200];
   strncpy(tFilePath, tEventFilePath->c_str(), 200);

   // Delete the event png filepath.
   delete tEventFilePath;

   // Copy the event completion notification into a local.
   Ris::Threads::NotifyWrapper* tCompletionNotify = (Ris::Threads::NotifyWrapper*)aEvent->user.data2;

   Prn::print(Prn::Show1, "doVideoDraw2 %s", tFilePath);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Draw the image.
   try
   {
      // Load the texture from the png file.
      SDL_Texture* tTexture = IMG_LoadTexture(mRenderer, tFilePath);
      if (!tTexture) throw "IMG_LoadTexture";

      int tWidth, tHeight;
      SDL_QueryTexture(tTexture, NULL, NULL, &tWidth, &tHeight);
      Prn::print(Prn::Show1, "LoadTexture %4d %4d", tWidth,tHeight);

      // Render the texture.
      SDL_RenderCopy(mRenderer, tTexture, NULL, NULL);
      SDL_DestroyTexture(tTexture);

      // Display the renderer changes.
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

   // Notify a completion.
   if (tCompletionNotify)
   {
      tCompletionNotify->notify();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace