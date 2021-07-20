#include <iostream>
#include <windows.h>
#include <ShlObj_core.h>

int main()
{
   std::string desktopPath(MAX_PATH, '\0'); 

   SHGetFolderPath(NULL,
      CSIDL_DESKTOPDIRECTORY,
      NULL,
      0, &desktopPath[0]);

   desktopPath += TEXT("das");
   wprintf(L"%s\n", desktopPath.c_str());

   SHCreateDirectory(NULL, desktopPath.c_str());

   return 0;
}