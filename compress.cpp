//
// compress.cpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Sun Jan 24 04:40:36 2016 Clément Roche
// Last update Mon Jan 25 03:42:24 2016 Clément Roche
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
   in.seekg(0, std::ios_base::beg);
   return false;
}

int	main(int ac, char **av) {
   if (ac < 3)
      std::cout << "Usage: ./compress infile outfile" << std::endl;
   else {

      std::ifstream in;
      in.open(av[1], std::ios::binary);

      if (checkValidInputFile(in))
	 return -1;

      char nextChar;
      std::vector<int> freq(256, 0);
      while (in.get(nextChar)) {
	 ++freq[(int)nextChar];
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
      // We write the header (just frequencies for each character on 4 bytes)
      for (auto i:freq) {
	 int val = i;
	 //out.write((char *)&val, sizeof(val));

	 // Stupid header
	 out << val << std::endl;
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
