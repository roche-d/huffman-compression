//
// uncompress.cpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Mon Jan 25 02:48:04 2016 Clément Roche
// Last update Mon Jan 25 03:02:09 2016 Clément Roche
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "HCTree.hpp"

static bool checkValidInputFile(std::ifstream &in) {
   if (!in.is_open()) {
      std::cout << "Invalid input file." << std::endl;
      return true;
   }
   in.seekg(0, std::ios_base::end);
   unsigned int len = in.tellg();
   if (!len) {
      std::cout << "The file is empty." << std::endl;
      return true;
   }
   if (len < 1024) {
      std::cout << "The header is corrupted." << std::endl;
      return true;
   }
   in.seekg(0, std::ios_base::beg);
   return false;
}

int	main(int ac, char **av) {
   if (ac < 3)
      std::cout << "Usage: ./uncompress infile outfile" << std::endl;
   else {

      std::ifstream in;
      in.open(av[1], std::ios::binary);

      if (checkValidInputFile(in))
	 return -1;

      int nextByte;
      std::vector<int> freq(256, 0);
      int i = 0;
      bool headerFailed = false;
      while (i < 256 && !headerFailed) {
	 in.read((char *)&nextByte, sizeof(nextByte));
	 if (nextByte) {
	    std::cout << i << " : " << nextByte << std::endl;
	    freq[i] = nextByte;
	 }
	 ++i;
      }

      // We build the tree
      HCTree tree;
      tree.build(freq);

      in.close();

      return -1;

      char nextChar;



      std::ofstream out;
      out.open(av[2], std::ios::binary | std::ios::trunc);
      if (!out.is_open()) {
	 std::cout << "Invalid output file." << std::endl;
	 return -1;
      }
      // We write the header (just frequencies for each character on 4 bytes)
      for (auto i:freq) {
	 int val = i;
	 out.write((char *)&val, sizeof(val));
      }
      // We reopen the input to encode
      in.open(av[1], std::ios::binary);
      if (checkValidInputFile(in))
	 return -1;
      while (in.get(nextChar)) {
	 tree.encode((byte) nextChar, out);
      }
      out.close();
      in.close();
   }
   return 0;
}
