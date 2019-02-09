#pragma once
/*==============================================================================
SV namespace: sixdofs that are measured by a computer vision based system.
Two dimensional array class template.
==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <atomic>
#include "string.h"
#include "svRCIndex.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace SV
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Memory control. An instance of this is allocated on the heap when 
// data memory is allocated. It contains a resource count. It used so that
// separate instances of the main class can point to the same allocated data
// memory.

class RCArrayMemoryControl
{
public:

   // Resource count.
   std::atomic<int> mResourceCount;
   // Constructor.
   RCArrayMemoryControl()
   {
      mResourceCount = 0;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class template for a two dimensional array of elements. Memory
// for the array is dynamically allocated.

template <class Element>
class RCArray
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Memory management control pointer.
   RCArrayMemoryControl* mMemoryControl;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Number of array rows and columns.
   int mRows;
   int mCols;

   // RCArray of elements, this is dynamically allocated memory.
   // Size is rows*cols.
   // Index range is 0..rows-1, 0..cols-1.
   Element* mElements;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   RCArray()
   {
      mElements = 0;
      mMemoryControl = 0;
      resetVariables();
   }

   // Constructor.
   RCArray(int aRows,int aCols)
   {
      mElements = 0;
      mMemoryControl = 0;
      initialize(aRows,aCols);
   }
   
   // Constructor.
   RCArray(RCSize aSize)
   {
      mElements = 0;
      mMemoryControl = 0;
      initialize(aSize.mRows,aSize.mCols);
   }
   
   // Reset variables for inheriting classes.
   virtual void RCArray::resetVariables()
   {
      mRows = 0;
      mCols = 0;
   }

   // Destructor.
   ~RCArray()
   {
      // If memory has already been allocated then deallocate it.
      decrementResourceCount();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Initialize.
   virtual void initialize(int aRows,int aCols)
   {
      // If memory has already been allocated then deallocate it.
      decrementResourceCount();

      // Reset member variables to defaults.
      resetVariables();

      // Store variables.
      mRows = aRows;
      mCols = aCols;

      // Allocate memory.
      if (mMemoryControl == 0)
      {
         mElements = new Element[mRows*mCols];
         mMemoryControl = new RCArrayMemoryControl;
      }

      // Increment the resource counter.
      incrementResourceCount();
   }

   // Initialize.
   virtual void initialize(RCSize aSize)
   {
      initialize(aSize.mRows,aSize.mCols);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Finalize.
   void finalize()
   {
      // If memory was allocated then deallocate it.
      if (mMemoryControl)
      {
         delete mElements;
         delete mMemoryControl;
         mMemoryControl = 0;
         mElements = 0;
         mRows = 0;
         mCols = 0;
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Increment the resource count.
   void incrementResourceCount()
   {
      // Guard.
      if (mMemoryControl==0) return;
      // Increment the resource count.
      mMemoryControl->mResourceCount++;
   }

   // Decrement the resource count. If it is zero then deallocate memory.
   void decrementResourceCount()
   {
      // Guard.
      if (mMemoryControl==0) return;
      // If there is no memory allocated then return.
      if (mMemoryControl->mResourceCount==0) return;

      // Decrement the resource count. If it is zero then deallocate memory.
      if (--mMemoryControl->mResourceCount == 0)
      {
         finalize();
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Copy constructor. Copy variables and data pointers. Do not copy
   // data. This makes a copy of a variable that points to the same allocated
   // memory.
   RCArray(const RCArray& aRhs)
   {
      memcpy(this, &aRhs, sizeof(*this));
      incrementResourceCount();
   }

   // Assignment operator. Copy variables and data pointers. Do not copy
   // data. This makes a copy of a variable that points to the same allocated
   // memory.
   RCArray& operator= (const RCArray& aRhs)
   {
      decrementResourceCount();
      memcpy(this, &aRhs, sizeof(*this));
      incrementResourceCount();
      return *this;
   }

   // Clone an array into another array.
   void RCArray::cloneTo(RCArray& aDestin)
   {
      aDestin.initialize(this->mRows, this->mCols);
      memcpy(aDestin.mBytes, this->mBytes, this->mNumBytes);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Return true if memory has been allocated.
   bool isValid()
   {
      return mMemoryControl != 0;
   }

   // Return resource count. If memory has not been allocated return -1.
   int  getResourceCount()
   {
      if (mMemoryControl == 0) return -1;
      return mMemoryControl->mResourceCount;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // RCArray element access.
   Element& at(int aRow,int aCol)
   {
      return mElements[aRow*mCols + aCol];
   }

   // RCArray element access.
   Element& operator()(int aRow, int aCol)
   {
      return mElements[aRow*mCols + aCol];
   }

   // RCArray element access.
   Element& at(RCIndex aIndex)
   {
      return mElements[aIndex.mRow*mCols + aIndex.mCol];
   }

   // RCArray element access.
   Element& operator()(RCIndex aIndex)
   {
      return mElements[aIndex.mRow*mCols + aIndex.mCol];
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Return size.
   RCSize rcSize()
   {
      return Size(mRows,mCols);
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

