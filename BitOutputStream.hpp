//
// BitOutputStream.hpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roched@epitech.net>
// 
// Started on  Sat Jan 23 21:59:27 2016 Clément Roche
// Last update Thu Jan 28 22:48:23 2016 Clément Roche
//

#include <iostream>

class BitOutputStream {
private:
   std::ostream &out;
   char buf;
   int nbits;

public:
   BitOutputStream(std::ostream &os) : out(os), buf(0), nbits(0) {
   }

   ~BitOutputStream() {
   }

   void flush();
   void writeBit(int i);
   char setBit(char b, int bit, int n);
};
