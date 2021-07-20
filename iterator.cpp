#include <iostream>
#include <algorithm>
#include <iterator>

template<typename T>
class MyIterator
{
public:
   using iterator_category = std::forward_iterator_tag;
   using difference_type   = std::ptrdiff_t;
   using value_type        = T;
   using pointer           = T*;
   using reference         = T&;

   
private:
   pointer m_it;
};

int main()
{

   return 0;
}