#include <iostream>
#include <memory>

// Clase simple que servirá de ejemplo
class SimpleClass
{
public:
   SimpleClass() {puts("SimpleClass constructor!");}
   ~SimpleClass() {puts("SimpleClass destructor!");}

   void foo() {puts("SimpleClass function!");}
};

void foo(std::shared_ptr<SimpleClass> simple)
{
   printf("%d\n", simple.use_count());
}

int main()
{
   /* SimpleClass* simple = new SimpleClass;
      Esto es un puntero "desnudo". 
      Siempre hay que encontrar una manera de no usar punteros desnudos.
   
      Es muy inseguro crear un puntero desnudo destinado a ser compartido con
      otros (ya que otros programados o usted sin querer elimine o haga algo indeseado
      a su puntero).

      Ejemplo:
         void foo(SimpleClass* simple)
         {
            delete simple;
         }

         SimpleClass* simpleA = new SimpleClass;
         foo(simpleA);
         delete simpleA; // Provocará un error


      Aunque si es usado como algo que se eliminará en el mismo contexto.
      Creo que se puede usar std::unique_ptr.

      ♥ Pero si se quiere usar para compartir con otros, usar std::shared_ptr.

      ♥ Para crear un puntero inteligente, usar su corresponiente creador (std::make_unique, std::make_shared, etc);
   */
   
   std::shared_ptr<SimpleClass> simple = std::make_shared<SimpleClass>();

   foo(simple);

   return 0;
}
