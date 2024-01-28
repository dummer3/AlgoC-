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

using head_iterator = std::list<Head*>::iterator;
using head_const_iterator = std::list<Head*>::const_iterator;
struct SparseMatrix {
  std::list<Head*> cols;
  std::list<Head *> rows;
  int nbElement,nbGroup;
  std::list<std::string> solution;

  SparseMatrix(std::string fileName);
  SparseMatrix(const SparseMatrix* from);
  ~SparseMatrix();
  void print() const;
  void resolve();
  void selectCol();
  void removeCol(Head*,Head*);
  void removeRow(Head*);


};

#endif
