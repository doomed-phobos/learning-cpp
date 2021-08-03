// =============
// MEMORY
// =============
// ♥  shared_ptr, unique_ptr, weak_ptr

#include <iostream>
#include <memory>

// Clase simple que servirá de ejemplo
class DumpClass
{
public:
   DumpClass() {printf("DumpClass constructor! %p\n", this);}
   ~DumpClass() {printf("DumpClass destructor! %p\n", this);}

   void dump() {printf("DumpClass function! %p\n", this);}
};

int main()
{
   // ===================
   // std::unique_ptr
   // ===================
   {
      std::unique_ptr<DumpClass> u0;
      {
         std::unique_ptr<DumpClass> u1 = std::make_unique<DumpClass>();
         /// DumpClass constructor!
         u1->dump();
         /// DumpClass function!
         // u0 = u1; => No se puede "compartir la propiedad" (puntero). 
         // ♥ Se puede mover el puntero que está conteniendo
         u0 = std::move(u1);

         /// Como u1 ya no tiene el puntero, no eliminará nada
      }
      if(u0)
         u0->dump();
      else
         puts("u0 is nullptr!");
      /// DumpClass function!
      /// DumpClass destructor!
   }

   // ====================
   // std::shared_ptr
   // ====================
   {
      auto dump_shared_ptr = 
         [](const std::shared_ptr<DumpClass>& s) {
            printf("use_count: %lld\n", s.use_count());
         };

      std::shared_ptr<DumpClass> s0;
      dump_shared_ptr(s0);
      {
         std::shared_ptr<DumpClass> s1 = std::make_shared<DumpClass>();
         dump_shared_ptr(s1);
         s0 = s1;
         dump_shared_ptr(s0);
         s1 = std::move(s0);
         dump_shared_ptr(s0);
         dump_shared_ptr(s1);
      }

      dump_shared_ptr(s0);
   }

   // ==================
   // std::weak_ptr
   // ==================
   

   
   return 0;
}
