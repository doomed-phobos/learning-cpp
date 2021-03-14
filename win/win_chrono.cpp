#include <iostream>
#include <windows.h>

LARGE_INTEGER g_start;
LARGE_INTEGER g_freq;

void start_counter()
{
   // Debemos obtener la frecuencia inicial
   QueryPerformanceFrequency(&g_freq);

   // Guardamos un punto del sistema, para luego obtener la hora actual
   QueryPerformanceCounter(&g_start);
}

double get_counter()
{
   // Obtenemos AHORA el contador actual
   LARGE_INTEGER li;
   QueryPerformanceCounter(&li);

   return static_cast<double>((li.QuadPart - g_start.QuadPart)) / 
          static_cast<double>(g_freq.QuadPart);
}

int main()
{
   start_counter();
   printf("%f\n", get_counter());

   return 0;
};