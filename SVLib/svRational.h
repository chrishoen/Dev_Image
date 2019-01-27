#pragma once

/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Rational number
==============================================================================*/

#include <stdio.h>
#include "risCmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Rational number for integer arithmetic.

struct Rational
{
   // Numerator and denominator.
   int mNumer;
   int mDenom;

   // Constructor
   Rational()
   {
      mNumer = 0;
      mDenom = 1;
   }

   void reset()
   {
      mNumer = 0;
      mDenom = 1;
   }

   // Constructor
   Rational(const int aNumer, const int aDenom)
   {
      mNumer = aNumer;
      mDenom = aDenom;
   }

   // Convert to string for prints.
   char* asString(char* aString);

   // Read command line command arguments.
   void readArgs(Ris::CmdLineCmd* aCmd);
};

// Operator
inline int operator*(const Rational& lhs, const int& rhs)
{
   return (lhs.mNumer*rhs)/lhs.mDenom;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

