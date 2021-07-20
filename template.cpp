#include <iostream>
#include <type_traits>
#include <functional>

/// Convierte del tipo T a U
/// Se habilita si T se puede convertir en U
template<typename T, typename U>
inline typename std::enable_if<std::is_convertible<T, U>::value, U>::type convert_to(const T& t)
{
   return static_cast<U>(t);
}

// =======================
// std::underlying_type
// =======================
// enum Name : <underlying_type> {...}

// =======================
// Especializacion de
//          plantillas
// =======================
// Declaracion inicial: Esto será por defecto. void se usa porque es el tipo que da enable_if si es falso
template<typename T, typename = void>
struct sk_strip_enum
{
   using type = T;
};

// Especialización: Si enable_if es falso, no retornará un tipo y por ende no servirá esta especialización
//                  Pero si es true, se usará esto
template<typename T>
struct sk_strip_enum<T, typename std::enable_if<std::is_enum<T>::value>::type> // Si es un enum, no va a retornar void y por
                                                                               // ende, no llama a la primer 
{
   using type = typename std::underlying_type<T>::type;
};
// ♥ Usar eso cuando quieres saber si el tipo es un enum y a la vez usar el tipo

template<bool Bool, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T>
{
   using type = T;
};

template<typename T>
constexpr bool is_negative(const T& n)
{
   return n < T(0);
}

template<size_t n, typename Enable = void>
struct Factorial
{
   static constexpr const size_t value = n * Factorial<n-1>::value;
};

template<size_t n>
struct Factorial<n, typename std::enable_if<is_negative(n)>::type>
{
   static constexpr const size_t value = 0;
};

template<>
struct Factorial<0>
{
   static constexpr const size_t value = 1;
};

// template<int n>
// struct Factorial<n, (n < 0)>
// {
// 
// };

template<typename T>
class function
{};

template<typename R, typename... Args>
class function<R(Args...)>
{
public:
   // TODO:             Esto significa un typename anonimo (aunque realmente es opcional colocar un nombre)
   template<typename F, typename = typename std::enable_if<std::is_convertible<F, std::function<R(Args...)>>::value>::type>
   function(F&& f) : m_f(std::forward<F>(f)) {}
private:
   std::function<R(Args...)> m_f;
};

int main()
{
   // function<void()> foo([a](){printf("%d\n", a);}); => Correcto
   // function<void()> foo(nullptr);
   // convert_to<int, std::string>(12);
   /*enum A {};
   enum B : int {};
   enum C : unsigned int {};
   enum D : std::uint8_t {
      a = -1,
      b = 23,
      c = 256
   };

   sk_strip_enum<A>::type;
   sk_strip_enum<std::string>::type;*/

   function<int()> f();
   // function<int()> f([&]()->int{return 0;});

   // Factorial<5>::value; // 5 * 4 * 3 * 2 * 1

   // get_Nth_type<2, int, int>::type;

   // Calcula: 1 + 2 + 3 + ... + n
   // Suma<-1>::value;

   return 0;
}