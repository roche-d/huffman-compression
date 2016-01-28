//
// BitOutputStream.cpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Sun Jan 24 04:42:03 2016 Clément Roche
// Last update Thu Jan 28 23:20:15 2016 Clément Roche
//

#include "BitOutputStream.hpp"

void BitOutputStream::flush() {
   out.put(buf);
   out.flush();
   buf = 0;
   nbits = 0;
}

static void debug_byte(char c) {
   std::cout << "debug" << std::endl;
   for (int i =0; i < 8; i++) {
      int v = c >> (7 - i);
      std::cout << (v & 1);
   }
   std::cout << std::endl;
}

void BitOutputStream::writeBit(int i) {
   if (nbits >= 8)
      flush();
   buf = setBit(buf, i, nbits);
   ++nbits;
}

char BitOutputStream::setBit(char b, int bit, int n) {
   b &= ~(1 << n);
   return b | (char) (bit << n);
}
