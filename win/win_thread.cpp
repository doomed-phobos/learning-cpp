#include <iostream>
#include <windows.h>

DWORD my_thread_func(LPVOID data);

int main()
{
   // Funcion que create el thread, devuelve el identificador
   HANDLE thread_handle = ::CreateThread(NULL,
      0,                // Usará el tamaño por defecto de la pila de threads

      my_thread_func,   // DWORD(*my_function)(void* argument)

      (LPVOID)"Hola",   // El argumento

      CREATE_SUSPENDED, // Aqui debería ir 0, pero no es seguro,
                        // ya que eso hará que el thread se ejecute antes de que regrese la funcion.

      (LPDWORD)0);      // Hace que no devuelve el id del thread   

   ::ResumeThread(thread_handle); // Se usa cuando el thread se creo con CREATE_SUSPENDED

   ::WaitForSingleObject(thread_handle, INFINITE); // Esperamos a que se termine de ejecutar el thread

   ::CloseHandle(thread_handle);

   return 0;
}

DWORD my_thread_func(LPVOID data)
{
   puts((const char*)data);

   return 0;
}