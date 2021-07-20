#include <iostream>
#include <fstream>
#include <algorithm>
   using namespace std;

string get_directory_from_filename(const string& filename)
{
   string res;
   string::const_reverse_iterator rit = find_if(filename.rbegin(), filename.rend(), [](const char& chr){
      return chr == '\\' || chr == '/';
   });
   
   if(rit != filename.rend())
      copy(filename.begin(), --rit.base(), back_inserter(res));

   return res;
}

int main(int argc, char* argv[])
{
   string filename = get_directory_from_filename(argv[0]) + "\\file.txt";
   
   ifstream file(filename);
   if(file) {
      cout << file.rdbuf() << endl;
   }else {
      cout << "Error to reading file!" << endl;
   }

   system("pause");
   return 0;
}