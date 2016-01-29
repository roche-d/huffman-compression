//
// BitInputStream.cpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Sun Jan 24 04:41:40 2016 Clément Roche
// Last update Fri Jan 29 03:11:02 2016 Clément Roche
//

#include "BitInputStream.hpp"

int BitInputStream::readBit() {
   if (nbits >= 8) {
      in.get(buf);
       nbits = 0;
   }
   int ret = buf >> nbits++;
   return ret & 1;
}
