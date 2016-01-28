//
// BitInputStream.hpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Sat Jan 23 21:58:56 2016 Clément Roche
// Last update Thu Jan 28 23:14:28 2016 Clément Roche
//

#include <iostream>

class BitInputStream {
private:
   std::istream &in;
   char buf;
   int nbits;
   bool eof;

public:
   BitInputStream(std::istream &is) : in(is), buf(0), nbits(0), eof(false) {
      in.get(buf);
      //std::cout << "first input " << (int)buf << std::endl;
      if (!buf)
	 eof = true;
   }

   ~BitInputStream() {
   }

   int readBit();
   bool end() const;
};
