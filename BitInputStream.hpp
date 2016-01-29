//
// BitInputStream.hpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Sat Jan 23 21:58:56 2016 Clément Roche
// Last update Fri Jan 29 03:10:58 2016 Clément Roche
//

#include <iostream>

class BitInputStream {
private:
   std::istream &in;
   char buf;
   int nbits;

public:
   BitInputStream(std::istream &is) : in(is), buf(0), nbits(0) {
      in.get(buf);
   }

   ~BitInputStream() {
   }

   int readBit();
};
