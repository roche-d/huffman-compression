//
// compress.cpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Sun Jan 24 04:40:36 2016 Clément Roche
// Last update Fri Jan 29 03:24:30 2016 Clément Roche
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

// Function that reads the input and prepare the header values
static void prepareHeader(std::vector<int> &freq, std::ifstream &in, int &charcount, int &headercount) {
   char nextChar;

   while (in.get(nextChar)) {
      int nextIndex = (int)nextChar + 128;
      ++freq[nextIndex];
      ++charcount;
   }
   for (auto i:freq) {
      if (i)
	 ++headercount;
   }
}

static void writeHeader(std::vector<int> &freq, std::ofstream &out, int charcount, int headercount) {
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
}

int	main(int ac, char **av) {
   if (ac < 3)
      std::cout << "Usage: ./compress infile outfile" << std::endl;
   else {

      std::ifstream in;
      in.open(av[1], std::ios::binary);

      if (checkValidInputFile(in, av[2]))
	 return -1;

      std::vector<int> freq(256, 0);
      int headercount = 0, charcount = 0;

      prepareHeader(freq, in, charcount, headercount);
      in.close();

      // Build the tree
      HCTree tree;
      tree.build(freq);

      // Open the output file
      std::ofstream out;
      out.open(av[2], std::ios::binary | std::ios::trunc);
      if (!out.is_open()) {
	 std::cout << "Invalid output file." << std::endl;
	 return -1;
      }

      // Write the header
      writeHeader(freq, out, charcount, headercount);

      // We reopen the input to encode
      in.open(av[1], std::ios::binary);
      if (checkValidInputFile(in))
	 return -1;

      // Output the result
      BitOutputStream outbin(out);
      char nextChar = 0;
      while (in.get(nextChar)) {
	 tree.encode((byte) nextChar + 128, outbin);
      }
      outbin.flush();
      out.close();
      in.close();
   }
   return 0;
}
