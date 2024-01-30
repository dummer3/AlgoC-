#include "cell.hpp"



bool operator==(const Cell& a, const Cell& b)
{
  return a.rowHead == b.rowHead && a.colHead == b.colHead;
}