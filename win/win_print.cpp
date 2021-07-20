#include <iostream>
#include <windows.h>

int main()
{
   PRINTDLG dlg = {0};
   TCHAR printer[256] = TEXT("\0");
   HDC hDC = CreateDC(TEXT("WINSPOOL"), printer, NULL, NULL);
   DOCINFO di = {0};
   di.cbSize = sizeof(DOCINFO);
   di.lpszDocName = TEXT("Prueba");
   
   StartDoc(hDC, &di);
   StartPage(hDC);
   RECT rc = {10, 10, 100, 100};
   FillRect(hDC, &rc, CreateSolidBrush(RGB(0, 0, 0)));
   EndPage(hDC);
   EndDoc(hDC);

   dlg.lStructSize = sizeof(PRINTDLG);
   dlg.hwndOwner = nullptr;
   dlg.Flags = PD_ALLPAGES;
   dlg.hDC = hDC;
   dlg.nFromPage = 1;
   dlg.nToPage = 1;
   dlg.nMaxPage = 1;
   dlg.nMinPage = 1;
   dlg.nCopies = 1;

   if(PrintDlg(&dlg) == TRUE) {
      puts("Print successfully!");
   }

   Sleep(5000);

   DeleteDC(hDC);

   return 0;
}