//
// compress.cpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Sun Jan 24 04:40:36 2016 Clément Roche
// Last update Thu Jan 28 23:20:49 2016 Clément Roche
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "HCTree.hpp"

static bool checkValidInputFile(std::ifstream &in, const char *out = 0) {
   if (!in.is_open()) {
      std::cout << "Invalid input file." << std::endl;
      return true;
   }
   in.seekg(0, std::ios_base::end);
   unsigned int len = in.tellg();
   if (!len) {
      std::cout << "Warning: The file is empty (output still created)." << std::endl;
      std::ofstream emptyout;
      emptyout.open(out, std::ios::binary | std::ios::trunc);
      emptyout.close();
      return true;
   }
   in.seekg(0, std::ios_base::beg);
   return false;
}

int	main(int ac, char **av) {
   if (ac < 3)
      std::cout << "Usage: ./compress infile outfile" << std::endl;
   else {

      std::ifstream in;
      in.open(av[1], std::ios::binary);

      if (checkValidInputFile(in, av[2]))
	 return -1;

      char nextChar;
      std::vector<int> freq(256, 0);
      int charcount = 0;
      while (in.get(nextChar)) {
	 ++freq[(int)nextChar];
	 ++charcount;
      }
      in.close();

      HCTree tree;
      tree.build(freq);

      std::ofstream out;
      out.open(av[2], std::ios::binary | std::ios::trunc);
      if (!out.is_open()) {
	 std::cout << "Invalid output file." << std::endl;
	 return -1;
      }
      int headercount = 0;
      for (auto i:freq) {
	 if (i)
	    ++headercount;
      }
      // We write the size of header an number of characters
      out.write((char *)&headercount, sizeof(headercount));
      out.write((char *)&charcount, sizeof(charcount));

      // We write the header (just frequencies for each character on 4 bytes)
      for (int i = 0; i < 256; i++) {
	 if (freq[i]) {
	    int val = freq[i];
	    unsigned char c = (unsigned char)i;
	    out.write((char *)&c, sizeof(c));
	    out.write((char *)&val, sizeof(val));
	 }
      }
      // We reopen the input to encode
      in.open(av[1], std::ios::binary);
      if (checkValidInputFile(in))
	 return -1;
      BitOutputStream outbin(out);
      while (in.get(nextChar)) {
	 tree.encode((byte) nextChar, outbin);
	 //tree.encode((byte) nextChar, out);
      }
      outbin.flush();
      out.close();
      in.close();
   }
   return 0;
}
