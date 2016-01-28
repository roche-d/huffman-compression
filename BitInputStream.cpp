//
// BitInputStream.cpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Sun Jan 24 04:41:40 2016 Clément Roche
// Last update Thu Jan 28 23:14:48 2016 Clément Roche
//

#include "BitInputStream.hpp"

int BitInputStream::readBit() {
   if (nbits >= 8) {
      in.get(buf);
      if (!buf)
	 eof = true;
      nbits = 0;
   }
   int ret = buf >> nbits++;
   return ret & 1;
}

bool BitInputStream::end() const {
   return eof;
}
