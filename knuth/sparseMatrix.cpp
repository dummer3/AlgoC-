#include "sparseMatrix.hpp"
#include <unistd.h>

SparseMatrix::SparseMatrix(std::string fileName) {
  std::fstream my_file;
  my_file.open(fileName, std::ios::in);

  if (my_file) {
    my_file >> nbGroup >> nbElement;
    std::cout << "GROUP: " << nbGroup << " ELEMENT: " << nbElement << std::endl;
    rows = std::list<Head *>();
    cols = std::list<Head *>();
    solution = std::list<std::string>();
    std::string line;
    int element;

    // List == LinkedList, so don't care if we push front or back
    for (int i = 0; i < nbElement; i++) {
      cols.push_back(new Head(std::to_string(i)));
    }

    std::getline(my_file, line);
    int i = 0;
    while (std::getline(my_file, line)) {
      char c = 'A' + i;
      std::cout << "read Group " << c << std::endl;

      Head *row = new Head(std::string(1, c));
      rows.push_back(row);

      std::stringstream ss(line);
      while (ss >> element) {
        std::cout << "    readElement " << element << std::endl;
        head_const_iterator it = cols.cbegin();
        std::advance(it, element);
        Head *col = *it;
        Cell *temp = new Cell(row, col);
        row->cells.push_back(temp);
        col->cells.push_back(temp);
        col->count++;
      }
      i++;
    }
  }
  std::cout << std::endl;
}

SparseMatrix::SparseMatrix(const SparseMatrix *from) {
  this->rows = std::list<Head *>();
  this->cols = std::list<Head *>();
  this->solution = std::list<std::string>(from->solution);

  for (Head *colFrom : from->cols) {
    cols.push_back(new Head(colFrom->represent));
  }

  for (Head *rowFrom : from->rows) {
    Head *row = new Head(rowFrom->represent);
    rows.push_back(row);

    for (Cell *cell : rowFrom->cells) {
      head_const_iterator col_it =
          std::find(from->cols.cbegin(), from->cols.cend(), cell->colHead);
      int col_index = std::distance(from->cols.cbegin(), col_it);

      head_const_iterator it = cols.cbegin();
      std::advance(it, col_index);
      Head *col = *it;
      Cell *temp = new Cell(row, col);
      row->cells.push_back(temp);
      col->cells.push_back(temp);
      col->count++;
    }
  }

  nbElement = cols.size();
  nbGroup = rows.size();
}

SparseMatrix::~SparseMatrix() {
  Head* head;
  while (head = rows.front()) {
    std::cout << "clean " << head->represent << std::endl;
    delete head;
    head = nullptr;
    rows.pop_front();
  }

  while (head = cols.front())
  {
    std::cout << "clean " << head->represent << " count " << head->count << std::endl;
    // Should call this to free the col, but cause double free
    //free(head);
    head = nullptr;
    cols.pop_front();
  }
}

void SparseMatrix::print() const {
  std::cout << "   ";
  for (Head *col : cols) {
    std::cout << " " << std::setw(3) << col->represent << " ";
  }
  std::cout << std::endl << std::endl;

  for (Head *row : rows) {
    std::cout << " " << row->represent << "  ";
    head_const_iterator col = cols.cbegin();
    for (Cell *cell : row->cells) {

      while (*col != cell->colHead) {
        std::cout << "     ";
        col++;
      }
      std::cout << "  X  ";
      col++;
    }
    std::cout << std::endl << std::endl;
  }
}

struct CountComparator {
  bool operator()(const Head *a, const Head *b) const {
    return a->count < b->count;
  }
};

void SparseMatrix::resolve() {
  if (cols.size())
    selectCol();
  else {
    std::cout << "A Solution was found" << std::endl;
    for (std::string str : solution)
      std::cout << str << std::endl;
  }
}

void SparseMatrix::selectCol() {
  head_iterator col =
      std::min_element(cols.begin(), cols.end(), CountComparator());

  std::cout << std::endl
            << "===================" << std::endl
            << "REMOVE ALL COLUMN " << (*col)->represent << std::endl
            << "===================" << std::endl
            << std::endl;

  if ((*col)->count == 0) {
    std::cout << "Can't work" << std::endl;
  } else {
    for (Cell *cell : (*col)->cells) {
      head_const_iterator row_it =
          std::find(rows.cbegin(), rows.cend(), cell->rowHead);
      int row_index = std::distance(rows.cbegin(), row_it);
      SparseMatrix newMat = SparseMatrix(this);
      head_const_iterator it = newMat.rows.cbegin();
      std::advance(it, row_index);
      newMat.removeRow(*it);
    }

    std::cout << "=======================" << std::endl
              << "END REMOVE ALL COLUMN  " << (*col)->represent << std::endl
              << "=======================" << std::endl
              << std::endl;
  }
}

void SparseMatrix::removeRow(Head *row) {
  std::string rowRepresent = row->represent;

  std::cout << std::endl
            << "===================" << std::endl
            << "REMOVE ALL ROW " << rowRepresent << std::endl
            << "===================" << std::endl
            << std::endl;

  print();

  std::string result = row->represent;
  for (Cell *cell : row->cells) {
    Head *col = cell->colHead;
    result += " " + col->represent;
    removeCol(col, row);
    print();
  }
  std::cout << std::endl
            << "=======================" << std::endl
            << "END REMOVE ALL ROW " << rowRepresent << std::endl
            << "======================" << std::endl
            << std::endl;

  // delete the row of origin here
  std::cout << "delete " << row->represent << std::endl;
  delete row;
  row = nullptr;
  solution.push_back(result);
  resolve();
}

void SparseMatrix::removeCol(Head *col, Head *rowOfOrigin) {
  std::cout << "=======================" << std::endl
            << "REMOVE COL " << col->represent << std::endl
            << "=======================" << std::endl
            << std::endl;

  Cell *cellCol;
  while (col->cells.size() != 0) {
    cellCol = col->cells.front();
    Head *row = cellCol->rowHead;
    std::cout << cellCol->rowHead->represent << ":"
              << cellCol->colHead->represent << std::endl;
    for (Cell *cell : row->cells) {
      cell->colHead->count--;
      //delete in col (even the row of origin)
      cell->colHead->cells.remove(cell);
    }

    rows.remove(row);
    //delete all row (except if we still need it to continue the algo)
    if (row != rowOfOrigin)
    {
      std::cout << "delete :" << row->represent << std::endl; 
      delete row;
      row = nullptr;
    }

  }

  cols.remove(col);
  // same as destructor
  // free(col);
}