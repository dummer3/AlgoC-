#ifndef SPARSEMATRIX_HPP
#define SPARSEMATRIX_HPP

#include "cell.hpp"
#include "head.hpp"
#include <fstream>
#include <sstream>
#include <list>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <stack>


using head_iterator = std::list<Head*>::iterator;
using head_const_iterator = std::list<Head*>::const_iterator;

// Struct to store the information in our stack
struct StackElement
{
    Head * element; // the row/col we store
    std::list<Head*> *listToAdd; // In which list we add our element (rols or cols)
    int index; // should have been used to insert the element at the same index, but no only use to mark when to stop the reverse process
};

struct SparseMatrixStack {
  std::list<Head*> cols; 
  std::list<Head *> rows;
  int nbElement,nbGroup;
  std::list<std::string> solution;
  std::stack<StackElement> stack; // stack to undo the change done to our matrix


  SparseMatrixStack(std::string fileName);
  ~SparseMatrixStack();
  
  void print() const;
  void resolve();
  void selectCol();
  void removeCol(Head*);
  void removeRow(Head*);
};

#endif
