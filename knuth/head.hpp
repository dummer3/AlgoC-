#ifndef HEAD_HPP
#define HEAD_HPP

#include "cell.hpp"
#include <list>
#include <stdlib.h>
#include <iostream>

// Represent a row or col
struct Head {
  int count; // Useful to compare and to decide which col choose 
  std::list<Cell> cells;
  std::string represent; // group or element name 

  Head(std::string represent);
};

#endif
