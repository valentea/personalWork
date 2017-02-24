#include <string>
#include <vector>
#include <stdexcept>

// importing a whole namespace in a header is frowned upon
// this will at least let us write 'string'/'vector' below
using std::string;
using std::vector;

class BigInt {
   public:
      BigInt(string s);   // convert string to BigInt
      BigInt(string s,int b);   //not default consturctor
      string to_string(); // get string representation
      void add(BigInt b); // add another BigInt to this one
   private:
      vector<int> bigint; // whatever you need
      int base;		 
};
