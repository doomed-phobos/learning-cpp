////////////////////////////
////    CONCURRENCIA    ////
////////////////////////////
// 
// ======================
// Threads
// ======================
// Se llaman automaticamente despues de instanciarlo
// join() => Bloque el hilo actual hasta que finalize el hilo
// 
// ======================
// Mutex
// ======================
// Evita que varios subprocesos accedan al <mismo bloque>, bloqueandolos.
// Recursivo: Cuando queremos usar un mutex dentro de una funcion <recursiva>
// 
// ======================
// Condition Variable
// ======================
// Se usa para bloquear otros hilos (::wait), hasta que otro hilo modifique una variable compartida (la condicion) y
// notifique a condition_variable (::notify_one).
// wait(Predicate) => Espera hasta que predicate sea true
// 
// ======================
// Atomic Type
// ======================
// ♥ Orden de memoria:
//    Cuando un hilo lee un valor de una ubicación de memoria, puede ver el valor inicial,
//    el valor escrito en el mismo hilo o el valor escrito en otro hilo.
//    Consulte std::memory_order para obtener detalles sobre el orden en el que
//    las escrituras realizadas a partir de subprocesos se vuelven visibles para otros subprocesos.

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

static mutex mtx;
void say_n_times(const string& text, int n)
{
   // lock_guard lock(mtx);
   for(int i = 0; i < n; ++i)
      cout << text << endl;
}

int main()
{
   thread t1(&say_n_times, "thread 1", 10);
   thread t2(&say_n_times, "thread 2", 10);

   t1.join();
   t2.join();

   return 0;
}