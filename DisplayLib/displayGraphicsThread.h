#pragma once

/*==============================================================================
Display video thread class.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <string>
#include "risThreadsThreads.h"
#include "risThreadsNotify.h"
#include "SDL.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Display
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is an example SDL2 video thread that creates a window and renderer and
// draws a filled rectangle.
//   
// It creates a window and a renderer and enters a loop that waits for posted
// events. If it receives a draw event then it draws a filled rectangle. If it
// receives a quit event then it exits the loop and the thread terminates.
//
// It inherits from BaseThread to obtain a basic thread functionality.

class GraphicsThread : public Ris::Threads::BaseThread
{
public:

   typedef Ris::Threads::BaseThread BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // If true then the thread SDL window was created successfully.
   bool mValidFlag;

   // SDL window resources.
   int              mDisplay;
   SDL_DisplayMode  mDisplayMode;
   SDL_Window*      mWindow;
   SDL_Surface*     mSurface;
   SDL_Surface*     mImage;
   SDL_Renderer*    mRenderer;
   SDL_RendererInfo mRenderInfo;
   SDL_Rect         mRectA;
   SDL_Rect         mRectB;

   // Widths and heights.
   int mWindowW;
   int mWindowH;
   int mRectW;
   int mRectH;

   // Window colors.
   int mForeColor[4];
   int mBackColor[4];

   // Thread window specific event types.
   unsigned int mDraw0EventType;
   
   // Metrics.
   double mStartTime;
   double mStopTime;


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   GraphicsThread();
  ~GraphicsThread();
  void show();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Thread base class overloads.

   // Thread init function. This is called by the base class immediately 
   // after the thread starts running. It initializes SDL and creates the
   // thread SDL window and associated resources.
   void threadInitFunction() override;

   // Thread run function. This is called by the base class immediately 
   // after the thread init function. It runs a loop that waits on SDL
   // events and processes posted events. The loop exits when it receives
   // a quit event.
   void threadRunFunction() override;

   // Thread exit function. This is called by the base class immediately
   // before the thread is terminated. It releases SDL resources and closes
   // the thread SDL window.
   void threadExitFunction() override;

   // Thread shutdown function. This posts an SDL quit event that causes
   // the thread event loop to exit.
   void shutdownThread() override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Start and finish the video subsystem.
   void doVideoStart();
   void doVideoFinish();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. 

   // Post an event to draw a blank screen.
   void postDraw0(int aCode);

   // Post an event to load a png file into the lcd hdmi graphics. Pass in
   // the png filepath and a completion notification. 
   void postDraw1(const char* aFilePath, Ris::Threads::NotifyWrapper* mCompletionNotify = 0);

   // Post an event to draw a test pattern.
   void postDraw2(int aCode);

   // Post an event to draw a test pattern.
   void postDraw3(int aCode);

   // Load the png file and notify the completion. This is called for the 
   // posted event.
   void doVideoDraw0(SDL_Event* aEvent);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Utilities.
   void showWindowInfo(SDL_Window* aWindow);
   void showRenderInfo(const char* aLabel, SDL_RendererInfo* aInfo);
   void showRendererInfo(SDL_Renderer* aRenderer);
   void showDisplayInfo(int tDisplayIndex);
   void showGLInfo();
   void showError();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global singular instance.

#ifdef _DISPLAYGRAPHICSTHREAD_CPP_
         GraphicsThread* gGraphicsThread = 0;
#else
extern   GraphicsThread* gGraphicsThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
