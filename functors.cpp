// =================
//  FUNCTORS
// =================
// Se usa cuando usamos algoritmos que terminan_if (como count_if, find_if)
// 
// ♥ Si NO necesitamos obtener algun valor, se usa LAMBDAS O FUNCIONES
//
// -----------------------------------
//   void is_odd(const int& value);
//                         ......
//   count_if(begin, last, is_odd);
// -----------------------------------
// 
// ♥ Si necesitamos comparar cada elemento con algun valor, USAR ESTRUCTURAS QUE TIENEN
//   UN BOOL OPERATOR()(elemento)
//
// ---------------------------------------------------------------
//   struct greater_that {
//      greater_that(const int& value);
//
//      bool operator()(elemento) {return elemento > value;}
//   };
// ---------------------------------------------------------------
#include <iostream>
#include <algorithm>

using namespace std;

// Functor
struct is_separator {
   const string& separator;

   is_separator(const string& sep) : separator(sep) {}

   bool operator()(const char& chr) {
      for(auto it = separator.begin();
         it != separator.end();
         ++it) {
         if(chr == *it) return true;
      }

      return false;
   }
};

int main()
{
   

   string str = "A";
   size_t size = count_if(str.begin(), str.end(), is_separator("o"));
   printf("%lld\n", size);

   return 0;
}