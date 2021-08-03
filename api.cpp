// __has_attribute
#ifdef __has_attribute
#  define API_HAS_ATTRIBUTE(attribute) __has_attribute(attribute)
#else
#  define API_HAS_ATTRIBUTE(attribute) 0
#endif

// CPP versions
#if __cplusplus >= 199711L
#  define API_IS_CPP98
#elif __cplusplus >= 201103L
#  define API_IS_CPP11
#elif __cplusplus >= 201402L
#  define API_IS_CPP14
#elif __cplusplus >= 201703L
#  define API_IS_CPP17
#endif

#if _MSC_VER
#  define API_NODISCARD [[nodiscard]] 
#else
#  define API_NODISCARD __attribute__((warn_unused_result))
#endif

// =============
// Atributos
// =============
// ♥ Para Visual Studio se usa __declspec
// ♥ Para GNU se usa __attribute__
//
// noreturn   => La función nunca regresa
// deprecated => La función está en desuso, emitirá un mensaje de warning
// nodiscard  => Especifica que el valor de retorno no debe ser descartado 

API_NODISCARD int square(const int& value)
{
   return value*value;
}

int main()
{
   square(12);

   return 0;
}