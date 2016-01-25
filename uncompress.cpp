//
// uncompress.cpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Mon Jan 25 02:48:04 2016 Clément Roche
// Last update Mon Jan 25 04:11:24 2016 Clément Roche
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "HCTree.hpp"

static bool checkValidInputFile(std::ifstream &in, const char *out) {
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
   if (len < 512) {
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

      if (checkValidInputFile(in, av[2]))
	 return -1;

      //int nextByte;
      std::vector<int> freq(256, 0);
      int i = 0;
      while (i < 256) {
	 /*in.read((char *)&nextByte, sizeof(nextByte));
	 if (nextByte) {
	    freq[i] = nextByte;
	    }*/

	 // Stupid header
	 int frequency;
	 in >> frequency;
	 if (frequency)
	    freq[i] = frequency;
	 ++i;
      }
      // \n
      in.get();

      // We build the tree
      HCTree tree;
      tree.build(freq);

      // Prepare the output
      std::ofstream out;
      out.open(av[2], std::ios::binary | std::ios::trunc);
      if (!out.is_open()) {
	 std::cout << "Invalid output file." << std::endl;
	 return -1;
      }

      int decoded;
      while ((decoded = tree.decode(in))) {
	 out << (char)decoded;
      }
      in.close();
      out.close();
   }
   return 0;
}
