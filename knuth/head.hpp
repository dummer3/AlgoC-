#ifndef HEAD_HPP
#define HEAD_HPP

#include "cell.hpp"
#include <list>
#include <stdlib.h>
#include <iostream>

struct Head {
  int count;
  std::list<Cell*> cells; 
  std::string represent;

  Head(std::string represent);
  ~Head();
  void deleteCol();
};

#endif
