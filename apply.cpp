//============
// std::apply
//============
// ♥ Invoca a una Callable con una tupla de argumentos
// ♥ Se usa, por ejemplo, para llamar una funcion con argumentos, pero como void(void)

#include <iostream>
#include <tuple>
#include <utility>

template<typename Callable, typename... Args>
class func_wrapper
{
public:
   func_wrapper(Callable&& fn, Args&&... args) :
      m_fn(std::forward<Callable>(fn)),            // Con std::forward guardamos una plantilla como variable
      m_args(std::forward<Args>(args)...) {}

   void operator()() {
      std::apply(m_fn, m_args); // Así es como usamos std::apply
   }
private:
   Callable&& m_fn;
   std::tuple<Args...> m_args; // Aquí almacenaremos todos nuestros argumentos
};

void foo(int a)
{
   printf("FOO: %d\n", a);
}

int main()
{
   func_wrapper fw(foo, 122);

   fw();

   return 0;
}