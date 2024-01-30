#ifndef CELL_HPP
#define CELL_HPP

struct Head;

// Represent a existing element in our sparseMatrix
struct Cell {
  Head *rowHead,*colHead; // each cell know its row and col
  Cell(Head* rowHead,Head* colHead): rowHead(rowHead), colHead(colHead) {};
};

// Operator to compare cell (for the std::find)
bool operator==(const Cell& a, const Cell& b);

#endif
