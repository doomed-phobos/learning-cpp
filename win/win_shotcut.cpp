#include <iostream>
#include <windows.h>
#include <ShObjIdl.h>

int main()
{
   if(FAILED(CoInitialize(NULL))) {
      puts("CoInitialize failed!");
      return 1;
   }

   IShellLink* pShellLnk = nullptr;
   IPersistFile* pPersistFile = nullptr;
   
   HRESULT hr = CoCreateInstance(CLSID_ShellLink,
                  nullptr,
                  CLSCTX_INPROC_SERVER,
                  IID_IShellLinkA,
                  reinterpret_cast<LPVOID*>(&pShellLnk)
               );

   if(SUCCEEDED(hr)) {
      pShellLnk->SetPath(TEXT("C:\\Windows\\regedit.exe"));
      pShellLnk->SetIconLocation(TEXT("C:\\Users\\Usuario\\Desktop\\chrome.ico"), 0);

      hr = pShellLnk->QueryInterface(IID_IPersistFile,
               reinterpret_cast<LPVOID*>(&pPersistFile)
            );

      if(SUCCEEDED(hr)) {
         pPersistFile->Save(TEXT("C:\\Users\\Usuario\\Desktop\\shotcut.lnk"), TRUE);
         pPersistFile->Release();
      }

      pShellLnk->Release();
   }
   
   CoUninitialize();
   return 0;
}