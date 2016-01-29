//
// HCTree.cpp for pa2 in /home/roched/Projects/cse100/repo_st_632_3786_10821_pa2_huffman
// 
// Made by Clément Roche
// Login   <roche_d@epitech.net>
// 
// Started on  Sun Jan 24 04:18:23 2016 Clément Roche
// Last update Fri Jan 29 02:41:40 2016 Clément Roche
//

#include <queue>
#include "HCTree.hpp"

HCTree::~HCTree() {
   if (root) {
      deleteAllNodes(root);
      root = 0;
   }
}


// Recursive function to delete all nodes of the tree
void	HCTree::deleteAllNodes(HCNode *node)
{
   if (!node)
      return ;
   deleteAllNodes(node->c0);
   deleteAllNodes(node->c1);
   delete node;
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
   // special case one char
   if (queue.top() && !queue.top()->c0 && !queue.top()->c1) {
      root = new HCNode(queue.top()->count, 0, queue.top(), 0);
   }
   else
      root = queue.top();
   assignParent(root);
}

// Helper function to link the tree upward (assign parent pointers)
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

// Encode a symbol to a BitOutputStream
void HCTree::encode(byte symbol, BitOutputStream &out) const {
   HCNode *leaf = leaves[(int)symbol];
   if (leaf) {
      std::vector<bool> enc;
      getEncodedSymbol(enc, leaf);
      for (auto c:enc) {
	 if (c)
	    out.writeBit(1);
	 else
	    out.writeBit(0);
      }
   }
}

// Encode a symbol to an ofstream
void HCTree::encode(byte symbol, ofstream &out) const {
   HCNode *leaf = leaves[(int)symbol];
   if (leaf) {
      std::string encstring = "";
      std::vector<bool> enc;
      getEncodedSymbol(enc, leaf);
      for (auto c:enc) {
	 if (c)
	    encstring += "1";
	 else
	    encstring += "0";
      }
      out << encstring;
   }
}


// This is a recursive function that retrieve the code word for a byte
void HCTree::getEncodedSymbol(std::vector<bool> &enc, HCNode *leaf) const {
   if (!leaf)
      return ;
   getEncodedSymbol(enc, leaf->p);
   if (leaf->p && leaf->p->c0 == leaf)
      enc.push_back(false);
   else if (leaf->p && leaf->p->c1 == leaf)
      enc.push_back(true);
}

// Recursive function that gets the symbol from an input stream
void HCTree::getDecodedSymbol(int &dec, ifstream &in, HCNode *leaf) const {
   if (!leaf)
      return ;
   if (!leaf->c0 && !leaf->c1) {
      dec = leaf->symbol;
      return ;
   }
   char nextChar = 0;
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

// Decode a symbol from a BitInputStream
void HCTree::getDecodedSymbol(int &dec, BitInputStream &in, HCNode *leaf) const {
   if (!leaf)
      return ;
   if (!leaf->c0 && !leaf->c1) {
      dec = leaf->symbol;
      return ;
   }
   int nextBit = in.readBit();
   if (nextBit == 0)
      getDecodedSymbol(dec, in, leaf->c0);
   else if (nextBit == 1)
      getDecodedSymbol(dec, in, leaf->c1);
}

int HCTree::decode(BitInputStream &in) const {
   int dec = 0;
   getDecodedSymbol(dec, in, root);
   return dec;
}
