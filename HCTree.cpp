//
// HCTree.cpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Sun Jan 24 04:18:23 2016 Clément Roche
// Last update Sun Jan 24 04:39:16 2016 Clément Roche
//

#include <queue>
#include "HCTree.hpp"

void HCTree::build(const vector<int> &freqs) {
   std::priority_queue<HCNode *> queue;
   byte b = 0;

   for (auto i:freqs) {
      std::cout << i << std::endl;
      queue.push(new HCNode(i, b++));
   }
}

void HCTree::encode(byte symbol, BitOutputStream &out) const {
}
