#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

int main()
{
   setlocale(LC_ALL, "\0");

   string a = "áéíóú. aeiou";
   wstring b = L"áéíóú. aeiou";

   printf(a.c_str());
   wprintf(b.c_str());

   return 0;
}