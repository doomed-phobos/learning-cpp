#include <iostream>
#include <type_traits>
#include <functional>

/// Convierte del tipo T a U
/// Se habilita si T se puede convertir en U
template<typename T, typename U>
inline std::enable_if<std::is_convertible<T, U>::value>::type convert_to(const T& t)
{
   return static_cast<U>(t);
}

struct B;

struct A
{
   explicit A(int a) {}

   operator B() const;
};

struct B
{
   B(int b) {}
};

int main()
{
   int a = 0xff;
   // function<void()> foo([a](){printf("%d\n", a);}); => Correcto
   // function<void()> foo(nullptr);
   convert_to<A, B>(A(12));

   return 0;
}