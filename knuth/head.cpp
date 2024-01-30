#include "head.hpp"

Head::Head(std::string represent) {
  count = 0;
  this->represent = represent;
  cells = std::list<Cell>();
}