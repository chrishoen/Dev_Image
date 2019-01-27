/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "risThreadsPriorities.h"

#include "displayParms.h"

#define  _DISPLAYGRAPHICSTHREAD_CPP_
#include "displayGraphicsThread.h"

namespace Display
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

GraphicsThread::GraphicsThread()
{
   BaseClass::setThreadName("Graphics");
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mNormal);
   BaseClass::setThreadPrintLevel(gParms.mPrintLevel);

   // Set member variables.
   mValidFlag = false;

   mDisplay = gParms.mDisplay;
   mWindow = 0;
   mSurface = 0;
   mImage = 0;
   mRenderer = 0;

   mWindowW = 0;
   mWindowH = 0;
   mRectH = 0;
   mRectW = 0;

   mForeColor[0] = 0;
   mForeColor[1] = 0;
   mForeColor[2] = 0;
   mForeColor[3] = 0;

   mBackColor[0] = 0;
   mBackColor[1] = 0;
   mBackColor[2] = 0;
   mBackColor[3] = 0;

   mRectA.x = 0;
   mRectA.y = 0;
   mRectA.w = 0;
   mRectA.h = 0;

   mRectB.x = 0;
   mRectB.y = 0;
   mRectB.w = 0;
   mRectB.h = 0;

   mDraw0EventType = 0;

   mStartTime = 0.0;
   mStopTime = 0.0;
}

GraphicsThread::~GraphicsThread()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void GraphicsThread::show()
{
   Prn::print(0, "VideoMsgPort");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// after the thread starts running. It initializes SDL and creates the
// thread SDL window and associated resources.

void GraphicsThread::threadInitFunction()
{
   int tRet = 0;

   // Initialize the video subsystem.
   TS::print(1, "SDL_Init");
   tRet = SDL_Init(SDL_INIT_VIDEO);
   if (tRet)
   {
      TS::print(0, "ERROR SDL_Init");
      mValidFlag = false;
      return;
   }

   // Initialize.
   SDL_DisableScreenSaver();

   // Initialize png.
   TS::print(1, "IMG_Init");
   tRet = IMG_Init(IMG_INIT_PNG);
   if (tRet != IMG_INIT_PNG)
   {
      TS::print(0, "ERROR IMG_Init");
      TS::print(0, "IMG_Init SDL_GetError  %s\n", SDL_GetError());
      TS::print(0, "IMG_GetError  %s\n", IMG_GetError());
      mValidFlag = false;
      return;
   }

   mValidFlag = true;

   // Initialize event types.
   mDraw0EventType = SDL_RegisterEvents(1);

   // Create the window and renderer.
   doVideoStart();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread run function. This is called by the base class immediately 
// after the thread init function. It runs a loop that waits on SDL
// events and processes posted events. The loop exits when it receives
// a quit event.

void GraphicsThread::threadRunFunction()
{
   if (!mValidFlag) return;

   // Loop to wait for posted events and process them.
   while (true)
   {
      // Wait for an event.
      SDL_Event tEvent;
      SDL_WaitEvent(&tEvent);

      // Exit the loop if a quit event was posted.
      if (tEvent.type == SDL_QUIT) break;

      // Draw something if a draw event was posted.
      if (tEvent.type == mDraw0EventType) doVideoDraw0(&tEvent);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately
// before the thread is terminated. It releases SDL resources and closes
// the thread SDL window.

void GraphicsThread::threadExitFunction()
{
   // Finish the SDL window.
   doVideoFinish();

   // Finalize the video subsystem.
   SDL_Quit();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread shutdown function. This posts an SDL quit event that causes
// the thread event loop to exit.

void GraphicsThread::shutdownThread()
{
   shutdownThreadPrologue();

   // Post a quit event.
   SDL_Event tEvent;
   SDL_memset(&tEvent, 0, sizeof(tEvent));
   tEvent.type = SDL_QUIT;
   SDL_PushEvent(&tEvent);

   // Wait for the thread to terminate.
   BaseClass::waitForThreadTerminate();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Post an event to draw a test pattern.

void GraphicsThread::postDraw0(int aCode)
{
   // Post the event.
   SDL_Event tEvent;
   SDL_memset(&tEvent, 0, sizeof(tEvent));
   tEvent.type = mDraw0EventType;
   tEvent.user.code = aCode;
   tEvent.user.data1 = 0;
   tEvent.user.data2 = 0;
   SDL_PushEvent(&tEvent);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace