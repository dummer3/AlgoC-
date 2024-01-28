#include "head.hpp"

Head::Head(std::string represent) {
  count = 0;
  this->represent = represent;
  cells = std::list<Cell *>();
}

Head::~Head() {
  for (Cell *cell : cells)
  {
    {  std::cout << "delete cell " << cell->rowHead->represent << ":" << cell->colHead->represent << std::endl;
      cell->colHead->cells.remove(cell); 
      delete cell;
    }
  }
}
