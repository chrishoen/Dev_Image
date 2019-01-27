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
// Draw some video.

void GraphicsThread::doVideoStart()
{
   TS::print(2, "GraphicsThread::doVideoStart");

   try
   {
      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Copy variables.

      mForeColor[0] = gParms.mForeColor[0];
      mForeColor[1] = gParms.mForeColor[1];
      mForeColor[2] = gParms.mForeColor[2];
      mForeColor[3] = gParms.mForeColor[3];

      mBackColor[0] = gParms.mBackColor[0];
      mBackColor[1] = gParms.mBackColor[1];
      mBackColor[2] = gParms.mBackColor[2];
      mBackColor[3] = gParms.mBackColor[3];

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Show SDL info.

      TS::print(2, "");
      TS::print(2, "VideoDrivers***************************************************");
      int tNumVideoDrivers = SDL_GetNumVideoDrivers();
      TS::print(2, "NumVideoDrivers        %1d", tNumVideoDrivers);
      for (int i = 0; i < tNumVideoDrivers; i++)
      {
         TS::print(2, "VideoDriver            %s", SDL_GetVideoDriver(i));
      }

      TS::print(2, "");
      TS::print(2, "VideoDisplays***************************************************");
      int tNumVideoDisplays = SDL_GetNumVideoDisplays();
      TS::print(2, "NumVideoDisplays       %1d", tNumVideoDisplays);
      for (int i = 0; i < tNumVideoDisplays; i++)
      {
         showDisplayInfo(i);
      }

      TS::print(2, "");
      TS::print(2, "RendererDrivers************************************************");
      int tNumRenderDrivers = SDL_GetNumRenderDrivers();
      TS::print(2, "NumRenderDrivers       %1d", tNumRenderDrivers);
      for (int i = 0; i < tNumRenderDrivers; i++)
      {
         SDL_GetRenderDriverInfo(i, &mRenderInfo);
         showRenderInfo("RenderDriver", &mRenderInfo);
      }

      TS::print(2, "");
      TS::print(2, "GL info*********************************************************");
      showGLInfo();

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Calculate variables.

      if (mDisplay == -1)
      {
         mDisplay = tNumVideoDisplays - 1;
      }

      int tRet = SDL_GetCurrentDisplayMode(mDisplay, &mDisplayMode);
      mWindowW = mDisplayMode.w;
      mWindowH = mDisplayMode.h;
      mRectW = mDisplayMode.w/8;
      mRectH = mDisplayMode.w/8;

      mRectA.x = mWindowW/4 - mRectW/2;
      mRectA.y = mWindowH/2 - mRectH/2;
      mRectA.w = mRectW;
      mRectA.h = mRectH;

      mRectB.x = (3*mWindowW)/4 - mRectW/2;
      mRectB.y = mWindowH/2 - mRectH/2;
      mRectB.w = mRectW;
      mRectB.h = mRectH;

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Create window.

      TS::print(2, "");
      TS::print(2, "CreateWindow***************************************************");

      unsigned int tWindowFlags = 0;
      if (false)
      {
         tWindowFlags |= SDL_WINDOW_SHOWN;
         tWindowFlags |= SDL_WINDOW_FULLSCREEN;
         tWindowFlags |= SDL_WINDOW_OPENGL;
      }
      else
      {
         tWindowFlags |= SDL_WINDOW_SHOWN;
         tWindowFlags |= SDL_WINDOW_BORDERLESS;
         tWindowFlags |= SDL_WINDOW_MAXIMIZED;
         tWindowFlags |= SDL_WINDOW_OPENGL;
      }

      mWindow = SDL_CreateWindow("GraphicsThread",
         SDL_WINDOWPOS_CENTERED_DISPLAY(mDisplay), SDL_WINDOWPOS_CENTERED_DISPLAY(mDisplay),
         mWindowW, mWindowH, tWindowFlags);
      if (mWindow == 0) throw "SDL_CreateWindow";

      showWindowInfo(mWindow);

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Create renderer.

      TS::print(2, "CreateRenderer*************************************************");

      int tRenderDriverIndex = -1;
      tRenderDriverIndex = 0;
      unsigned int tRenderFlags = 0;
      tRenderFlags |= SDL_RENDERER_ACCELERATED;
      tRenderFlags |= SDL_RENDERER_PRESENTVSYNC;

      mRenderer = SDL_CreateRenderer(mWindow, tRenderDriverIndex, tRenderFlags);
      if (mRenderer == 0) throw "SDL_CreateRenderer";

      // Set renderer to the same size as the window.
      SDL_RenderSetLogicalSize(mRenderer, mWindowW, mWindowH);

      // Show.
      showRendererInfo(mRenderer);

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Draw the window.

      TS::print(2, "DrawWindow*****************************************************");

      // Disable the mouse.
      SDL_ShowCursor(SDL_DISABLE);

      // Set renderer to the background color.
      SDL_SetRenderDrawColor(mRenderer, mBackColor[0], mBackColor[1], mBackColor[2], mBackColor[3]);

      // Clear the window and make it all background color.
      SDL_RenderClear(mRenderer);

      // Render the changes above.
      SDL_RenderPresent(mRenderer);
   }
   catch (const char* aString)
   {
      TS::print(2, "EXCEPTION %s", aString, SDL_GetError());
      mValidFlag = false;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw some video.

void GraphicsThread::doVideoFinish()
{
   TS::print(2, "GraphicsThread::doVideoFinish BEGIN");

   if (mRenderer) SDL_DestroyRenderer(mRenderer);
   if (mWindow)   SDL_DestroyWindow(mWindow);
   mRenderer = 0;
   mWindow = 0;

   TS::print(2, "GraphicsThread::doVideoFinish END");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//name;space