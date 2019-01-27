/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"


#include "SDL.h"

#include "displayGraphicsThread.h"

namespace Display
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

void GraphicsThread::showWindowInfo(SDL_Window* aWindow)
{
   unsigned int tFlags = SDL_GetWindowFlags(aWindow);
   int tWidth, tHeight;
   SDL_GetWindowSize(aWindow, &tWidth, &tHeight);

   char tString[100] = "";
   if (tFlags & SDL_WINDOW_SHOWN)      strcat(tString, "shown ");
   if (tFlags & SDL_WINDOW_HIDDEN)     strcat(tString, "hidden ");
   if (tFlags & SDL_WINDOW_FULLSCREEN) strcat(tString, "fullscreen ");
   if (tFlags & SDL_WINDOW_OPENGL)     strcat(tString, "opengl ");

   TS::print(2, "WindowFlags     %8X  %s  %4d %4d", tFlags, tString,tWidth,tHeight);
}

void GraphicsThread::showRenderInfo(const char* aLabel, SDL_RendererInfo* aInfo)
{

   char tString[100] = "";
   if (aInfo->flags & SDL_RENDERER_SOFTWARE)      strcat(tString, "software ");
   if (aInfo->flags & SDL_RENDERER_ACCELERATED)   strcat(tString, "accelerated ");
   if (aInfo->flags & SDL_RENDERER_PRESENTVSYNC)  strcat(tString, "presentvsync ");
   if (aInfo->flags & SDL_RENDERER_TARGETTEXTURE) strcat(tString, "targettexture ");

   TS::print(2, "RenderInfo  %-16s %-10s %5X %s", aLabel, aInfo->name, aInfo->flags, tString);
}

void GraphicsThread::showRendererInfo(SDL_Renderer* aRenderer)
{
   SDL_RendererInfo tInfo;
   SDL_GetRendererInfo(aRenderer, &tInfo);
   int tWidth, tHeight;
   SDL_GetRendererOutputSize(aRenderer, &tWidth,&tHeight);

   char tString[100] = "";
   if (tInfo.flags & SDL_RENDERER_SOFTWARE)      strcat(tString, "software ");
   if (tInfo.flags & SDL_RENDERER_ACCELERATED)   strcat(tString, "accelerated ");
   if (tInfo.flags & SDL_RENDERER_PRESENTVSYNC)  strcat(tString, "presentvsync ");
   if (tInfo.flags & SDL_RENDERER_TARGETTEXTURE) strcat(tString, "targettexture ");

   TS::print(2, "Renderer Info  %-10s %5X %s", tInfo.name, tInfo.flags, tString);
   TS::print(2, "Renderer OutSize  %4d %4d", tWidth,tHeight);
}

void GraphicsThread::showDisplayInfo(int tDisplayIndex)
{
   SDL_DisplayMode  tDisplayMode;
   int tRet = SDL_GetCurrentDisplayMode(tDisplayIndex, &tDisplayMode);
   if (tRet) throw "SDL_GetCurrentDisplayMode";

   TS::print(2, "Display                %4d %4d %4d",
      tDisplayMode.w, tDisplayMode.h, tDisplayMode.refresh_rate);
}

void GraphicsThread::showGLInfo()
{
   int tRet;
   int tValue;
   char tString[100] = "";

   tRet = SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &tValue);
   if (tRet == 0)
   {
      TS::print(2, "GL PRESENT");
   }
   else
   {
      TS::print(2, "GL NOT PRESENT %s", SDL_GetError());
      return;
   }

   SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &tValue);
   if (tValue == SDL_GL_CONTEXT_PROFILE_ES) strcpy(tString, "GLES");
   else                                     strcpy(tString, "NOT GLES");
   TS::print(2, "GL_CONTEXT_PROFILE_MASK      %5d %s", tValue, tString);

   SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &tValue);
   TS::print(2, "GL_CONTEXT_MAJOR_VERSION     %5d", tValue);

   SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &tValue);
   TS::print(2, "GL_CONTEXT_MINOR_VERSION     %5d", tValue);

   SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &tValue);
   TS::print(2, "GL_DOUBLEBUFFER              %5d", tValue);

   SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &tValue);
   TS::print(2, "GL_ACCELERATED_VISUAL        %5d", tValue);
}

void GraphicsThread::showError()
{
   TS::print(2, "ERROR %s", SDL_GetError());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace