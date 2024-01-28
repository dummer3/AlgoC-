#ifndef CELL_HPP
#define CELL_HPP

struct Head;

struct Cell {
  Head *rowHead,*colHead;
  Cell(Head* rowHead,Head* colHead): rowHead(rowHead), colHead(colHead) {};
};

#endif
