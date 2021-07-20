#include <iostream>
#include <memory>

#define DUMP_COUNT(shared_ptr) printf("use_count: %ld\n", shared_ptr.use_count())

template<typename T>
class SharedPtr
{
public:
   SharedPtr() : m_ptr(nullptr), m_refCounter(nullptr) {}
   SharedPtr(T* ptr) : m_ptr(ptr) , m_refCounter(new RefCounter()) {}
   SharedPtr(const SharedPtr& that) {
      m_ptr = that.m_ptr;
      m_refCounter = that.m_refCounter;

      if(m_refCounter)
         m_refCounter->add();
   }

   SharedPtr(SharedPtr&& that) {
      m_ptr = that.m_ptr;
      m_refCounter = that.m_refCounter;

      that.m_ptr = nullptr;
      that.m_refCounter = nullptr;
   }

   ~SharedPtr() {
      unref();
   }

   int use_count() const {return m_refCounter ? m_refCounter->get() : 0;}

   SharedPtr& operator=(const SharedPtr& that) {
      if(m_ptr != that.m_ptr) {
         SharedPtr(that).swap(*this);
      }

      return *this;
   }

   SharedPtr& operator=(SharedPtr&& that) {
      if(m_ptr != that.m_ptr) {
         SharedPtr(std::move(that)).swap(*this);
      }

      return *this;
   }
private:
   class RefCounter
   {
   public:
      RefCounter() : m_refCount(1) {}

      int add() {return m_refCount++;}
      int sub() {return m_refCount--;}
      int get() const {return m_refCount;}
   private:
      int m_refCount;
   };

   void ref() {
      if(m_refCounter)
         (void)m_refCounter->add();
   }

   void unref() {
      if(m_refCounter) {
         if(m_refCounter->sub() == 1) {
            delete m_ptr;
            delete m_refCounter;

            m_ptr = nullptr;
            m_refCounter = nullptr;
            puts("UNREF");
         }
      }
   }

   void swap(SharedPtr& other) {
      std::swap(m_ptr, other.m_ptr);
      std::swap(m_refCounter, other.m_refCounter);
   }

   RefCounter* m_refCounter;
   T* m_ptr;
};

int main()
{
   SharedPtr<int> d;

   {
   SharedPtr<int> a(new int(0));
   SharedPtr<int> b = a;
   d = a;
   DUMP_COUNT(a);
   DUMP_COUNT(b);
   DUMP_COUNT(a);
   DUMP_COUNT(b);
   //DUMP_COUNT(c);
   }

   puts("------LIB-------");
   std::shared_ptr<int> a(new int(0));
   std::shared_ptr<int> b = a;
   DUMP_COUNT(a); // 2
   DUMP_COUNT(b); // 2
   std::shared_ptr<int> c = std::move(a);
   DUMP_COUNT(a); // 0
   DUMP_COUNT(b); // 2
   DUMP_COUNT(c); // 2

   return 0;
}