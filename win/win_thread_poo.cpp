// Clase thread para win32 basada en std::thread
#include <iostream>
#include <windows.h>

class thread
{
public:
   typedef HANDLE native_handle_t;
   typedef DWORD native_id_t;
   
   thread() : 
      m_thread_handle((native_handle_t)0),
      m_thread_id((native_id_t)0) {}

   template<typename Callable>
   thread(Callable&& fn) {
      launch_thread(new func_wrapper0<Callable>(std::forward<Callable>(fn)));
   }

   ~thread() {
      if(joinable())
         detach();
   }

   void join() {
      if(joinable()) {
         ::WaitForSingleObject(m_thread_handle, INFINITE);

         detach();
      }
   }
   void detach() {
      if(joinable()) {
         ::CloseHandle(m_thread_handle);
         m_thread_handle = (native_handle_t)0;
      }
   }

   bool joinable() const {
      return m_thread_handle != (native_handle_t)0;
   }
private:
   native_handle_t m_thread_handle;
   native_id_t m_thread_id;

   // WRAPPER: Funciona como una envoltura de otra funcion
   class func_wrapper
   {
   public:
      func_wrapper() {}
      virtual ~func_wrapper() {}

      virtual void operator()() = 0;
   };

   template<typename Callable>
   class func_wrapper0 : public func_wrapper
   {
   public:
      func_wrapper0(Callable&& fn) :
      m_fn(std::forward<Callable>(fn)) {}

      virtual void operator()() override {
         m_fn();
      }

   private:
      Callable&& m_fn;
   };

   void launch_thread(func_wrapper* fn) {
      m_thread_handle = ::CreateThread(NULL,
         0,
         thread_proxy,
         (LPVOID)fn,
         CREATE_SUSPENDED,
         &m_thread_id);

      ::ResumeThread(m_thread_handle);
   }

   // PROXY: Hace de intermedio entre dos funciones
   static DWORD WINAPI thread_proxy(LPVOID data) {
      func_wrapper* fn = reinterpret_cast<func_wrapper*>(data);

      (*fn)();

      delete fn;
      return 0;
   }

};

namespace this_thread
{
   thread::native_id_t get_id() {
      return GetCurrentThreadId();
   }

   void yield() {
      ::Sleep(0);
   }
} // namespace this_thread

class mutex
{
public:
   mutex() {
      InitializeCriticalSection(&m_handle);
   }

   ~mutex() {
      DeleteCriticalSection(&m_handle);
   }

   void lock() {
      EnterCriticalSection(&m_handle);
   }

   bool try_lock() {
      return TryEnterCriticalSection(&m_handle) ? true : false;
   }

   void unlock() {
      LeaveCriticalSection(&m_handle);
   }
private:
   CRITICAL_SECTION m_handle;
};

mutex mt;

void foo()
{
   mt.lock();
   for(int i = 0; i < 50; i++) {
      printf("Thread: %d   %d\n", this_thread::get_id(), i);
   }
   mt.unlock();
}

int main()
{
   thread t(foo);
   thread t2(foo);

   t.join();
   t2.join();

   return 0;
}