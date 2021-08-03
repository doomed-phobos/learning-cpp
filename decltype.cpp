#include <iostream>

// ♥ Se usa para obtener algun tipo en función de otros.
template<typename T1, typename T2>
auto plus(T1&& t1, T2&& t2) -> decltype(std::forward<T1>(t1) + std::forward<T2>(t2))
{
   return std::forward<T1>(t1) + std::forward<T2>(t2);
}

int main()
{
   plus(12.f, 23);

   return 0;
}