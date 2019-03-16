#pragma once
/*==============================================================================
Session file manager.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <string>
#include <vector>

namespace CX
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encalsulates a session file manager.

class FileManager
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static const int cMaxStringSize = 200;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // If true then a print zip is in progress and some file operations will
   // not be executed.
   bool mZipInProgress;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Program directory paths.
   std::string mBaseDirPath;
   std::string mZipDirPath;
   std::string mGCodeDirPath;
   std::string mWorkDirPath;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. These pertain to the zip dirctory.

   // Zip directory name list.
   std::vector<std::string> mZipNameList;

   // Selected zip name.
   std::string mZipName;

   // Selected zip file path.
   std::string mZipFilePath;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. These pertain to the gcode dirctory.

   // Zip directory name list.
   std::vector<std::string> mGCodeNameList;

   // Selected gcode name.
   std::string mGCodeName;

   // Selected gcode file path.
   std::string mGCodeFilePath;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. These pertain to the work dirctory.

   // Gcode name.
   std::string mWorkGCodeName;

   // GCode file path.
   std::string mWorkGCodeFilePath;

   // GCode prefix file path.
   std::string mWorkSliceFilePrefixPath;

   // Script file path.
   std::string mWorkScriptFilePath;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. Status.

   // Last error.
   std::string mError;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   FileManager();
   void initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. These pertain to the zip dirctory.

   // Get the zip name list from the zip directory.
   void getZipNameList();

   // Show the zip name list.
   void showZipNameList();

   // Select a zip name from the zip name list. Return true if successful.
   bool setZipName(int aZipNum);

   // Set the zip name. Return true if successful.
   bool setZipName(const char* aZipName);

   // Unzip the zip file from the zip directory into the work directory.
   // Return true if successful.
   bool doLoadZip();
   bool doLoadZip(int aZipNum);
   bool doLoadZip(const char* aZipName);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. These pertain to the gcode dirctory.

   // Get the gcode name list from the gcode directory.
   void getGCodeNameList();

   // Show the gcode name list.
   void showGCodeNameList();

   // Select a gcode name from the gcode name list. Return true if successful.
   bool setGCodeName(int aGCodeNum);

   // Set the gcode name. Return true if successful.
   bool setGCodeName(const char* aGCodeName);

   // Copy the gcode file from the gcode directory into the work directory.
   // Return true if successful.
   bool doLoadGCode();
   bool doLoadGCode(int aGCodeNum);
   bool doLoadGCode(const char* aGCodeName);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. These pertain to the work dirctory.

   // Find the name of the gcode file in the work directory, no file 
   // extension.
   bool doFindWorkGCodeName();

   // Return the file path to the gcode file.
   std::string getWorkGCodeFilePath();

   // Return the file path to a slice file.
   std::string getWorkSliceFilePath(int aSliceNumber);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Show.
   void show1();
   void show2();

   // Return true if the file exists,
   bool exists(std::string aFilePath);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _CXFILEMANAGER_CPP_
FileManager gFileManager;
#else
extern FileManager gFileManager;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace




