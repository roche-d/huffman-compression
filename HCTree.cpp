//
// HCTree.cpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Sun Jan 24 04:18:23 2016 Clément Roche
// Last update Mon Jan 25 03:29:44 2016 Clément Roche
//

#include <queue>
#include "HCTree.hpp"

HCTree::~HCTree() {
}

void HCTree::build(const vector<int> &freqs) {
   std::priority_queue<HCNode *, std::vector<HCNode *>, HCNodePtrComp> queue;
   byte b = 0;

   // Push all the leaves in vector but also in the priority queue
   for (auto i:freqs) {
      if (i) {
	 leaves[(int) b] = new HCNode(i, b);
	 queue.push(leaves[(int) b]);
      }
      ++b;
   }

   // We build the tree
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
   root = queue.top();
   assignParent(root);
}

void HCTree::assignParent(HCNode *node) {
   if (!node)
      return ;
   if (node->c0) {
      node->c0->p = node;
      assignParent(node->c0);
   }
   if (node->c1) {
      node->c1->p = node;
      assignParent(node->c1);
   }
}

void HCTree::encode(byte symbol, BitOutputStream &out) const {
}

void HCTree::encode(byte symbol, ofstream &out) const {
   HCNode *leaf = leaves[(int)symbol];
   if (leaf) {
      std::string enc = "";
      getEncodedSymbol(enc, leaf);
      out << enc;
   }
}

void HCTree::getEncodedSymbol(std::string &enc, HCNode *leaf) const {
   if (!leaf)
      return ;
   getEncodedSymbol(enc, leaf->p);
   if (leaf->p && leaf->p->c0 == leaf)
      enc += "0";
   else if (leaf->p && leaf->p->c1 == leaf)
      enc += "1";
}

void HCTree::getDecodedSymbol(int &dec, ifstream &in, HCNode *leaf) const {
   if (!leaf)
      return ;
   if (!leaf->c0 && !leaf->c1) {
      dec = leaf->symbol;
      return ;
   }
   char nextChar;
   in.get(nextChar);
   if (nextChar == '0')
      getDecodedSymbol(dec, in, leaf->c0);
   else if (nextChar == '1')
      getDecodedSymbol(dec, in, leaf->c1);
}

int HCTree::decode(ifstream &in) const {
   int dec = 0;
   getDecodedSymbol(dec, in, root);
   return dec;
}
