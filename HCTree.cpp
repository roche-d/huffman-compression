//
// HCTree.cpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Sun Jan 24 04:18:23 2016 Clément Roche
// Last update Sun Jan 24 07:25:45 2016 Clément Roche
//

#include <queue>
#include "HCTree.hpp"

HCTree::~HCTree() {
}

void HCTree::build(const vector<int> &freqs) {
   std::priority_queue<HCNode *, std::vector<HCNode *>, HCNodePtrComp> queue;
   byte b = 0;

   for (auto i:freqs) {
      if (i) {
	 leaves[i] = new HCNode(i, b);
	 queue.push(leaves[i]);
      }
      ++b;
   }

   std::cout << "size: " << queue.size() << std::endl;
   std::cout << *queue.top() << std::endl;
   while (queue.size() > 1)
   {
      HCNode *left, *right;
      right = queue.top();
      queue.pop();
      left = queue.top();
      queue.pop();
      HCNode *n = new HCNode(left->count + right->count, 0, left, right);
      queue.push(n);
   }
   std::cout << "final tree " << *queue.top() << " left " << *(queue.top()->c0) << std::endl;
}

void HCTree::encode(byte symbol, BitOutputStream &out) const {
}
