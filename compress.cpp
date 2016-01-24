//
// compress.cpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Sun Jan 24 04:40:36 2016 Clément Roche
// Last update Sun Jan 24 07:31:29 2016 Clément Roche
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "HCTree.hpp"

int	main(int ac, char **av) {
   if (ac < 3)
      std::cout << "Usage: ./compress infile outfile" << std::endl;
   else {
      //std::string infile = av[1], outfile = av[2];
      std::cout << "trying to open " << av[1] << std::endl;

      std::ifstream in;
      in.open(av[1], std::ios::binary);

      if (!in.is_open()) {
	 std::cout << "Invalid input file." << std::endl;
	 return -1;
      }
      in.seekg(0, std::ios_base::end);
      unsigned int len = in.tellg();
      if (!len) {
	 std::cout << "The file is empty." << std::endl;
	 return -1;
      }
      in.seekg(0, std::ios_base::beg);
      char nextChar;
      std::vector<int> freq(256, 0);
      while (in.get(nextChar)) {
	 ++freq[(int)nextChar];
      }
      in.close();

      HCTree tree;
      tree.build(freq);
   }
   return 0;
}
