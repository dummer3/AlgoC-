#include "sparseMatrixStack.hpp"
#include <unistd.h>

SparseMatrixStack::SparseMatrixStack(std::string fileName) {

  rows = std::list<Head *>();
  cols = std::list<Head *>();
  solution = std::list<std::string>();

  // stack to undo the change done to out matrix
  stack = std::stack<StackElement>();

  std::fstream my_file;
  my_file.open(fileName, std::ios::in);

  if (my_file) {
    my_file >> nbGroup >> nbElement;
    std::cout << "GROUP: " << nbGroup << " ELEMENT: " << nbElement << std::endl;

    std::string line;
    int element;

    // List == LinkedList, so don't care if we push front or back
    for (int i = 0; i < nbElement; i++) {
      cols.push_back(new Head(std::to_string(i)));
    }

    std::getline(my_file, line);
    int i = 0;

    // for each group
    while (std::getline(my_file, line)) {
      char c = 'A' + i;
      std::cout << "read Group " << c << std::endl;

      Head *row = new Head(std::string(1, c));
      rows.push_back(row);
      std::stringstream ss(line);

      // for each element
      while (ss >> element) {
        std::cout << "    readElement " << element << std::endl;
        head_const_iterator it = cols.cbegin();
        std::advance(it, element);
        Head *col = *it;

        // we create the cell, and we add it to the row and col
        Cell temp = Cell(row, col);
        row->cells.push_back(temp);
        col->cells.push_back(temp);
        col->count++;
      }
      i++;
    }
  }
  std::cout << std::endl;
}

SparseMatrixStack::~SparseMatrixStack() {
  // Clean everything
  Head *head;
  while (head = rows.front()) {
    std::cout << "clean " << head->represent << std::endl;
    delete head;
    rows.pop_front();
  }

  while (head = cols.front()) {
    std::cout << "clean " << head->represent << " count " << head->count
              << std::endl;
    cols.pop_front();
  }

  while (!stack.empty()) {
    head = stack.top().element;
    delete head;
    stack.pop();
  }

  // rows.clear();
  // cols.clear();
}

// Just a print
void SparseMatrixStack::print() const {
  std::cout << "   ";
  for (Head *col : cols) {
    std::cout << " " << std::setw(3) << col->represent << " ";
  }
  std::cout << std::endl << std::endl;

  for (Head *row : rows) {
    std::cout << " " << row->represent << "  ";
    head_const_iterator col = cols.cbegin();

    // no sort anymore since we add the col/row at the end, so we have to check
    // everyCols
    for (Head *col : cols) {
      if (std::find_if(row->cells.begin(), row->cells.end(), [col](Cell cell) {
            return cell.colHead == col;
          }) != row->cells.end())
        std::cout << "  X  ";
      else
        std::cout << "     ";
    }
    std::cout << std::endl << std::endl;
  }
}

struct CountComparator {
  bool operator()(const Head *a, const Head *b) const {
    return a->count < b->count;
  }
};

// Main recursive function, until our matrix is not null, we try to remove a col
void SparseMatrixStack::resolve() {
  if (cols.size())
    selectCol();
  else {
    std::cout << "A Solution was found" << std::endl;
    for (std::string str : solution)
      std::cout << str << std::endl;
  }
}

// Function where we choose the column with the less element, and we remove it
// If the column is empty, it's mean our current solution can't be done, so we
// have to undo all the previous change to the mat
void SparseMatrixStack::selectCol() {
  head_iterator col =
      std::min_element(cols.begin(), cols.end(), CountComparator());

  std::cout << std::endl
            << "===================" << std::endl
            << "REMOVE ALL COLUMN " << (*col)->represent << std::endl
            << "===================" << std::endl
            << std::endl;
  std::cout << "count " << (*col)->count << std::endl;

  // Current solution impossible
  if ((*col)->count == 0) {
    std::cout << "Can't work" << std::endl;

    // We undo all the change
    // (index==-1 is a tag we placed to mark off all the change we need to undo
    while (stack.size() && stack.top().index != -1) {
      StackElement el = stack.top();

      // If our head remove was a column
      if (el.listToAdd == &cols) {
        cols.push_back(el.element);
        std::cout << "col " << el.element->represent << " : " << el.element
                  << std::endl;
      }
      // It was a row
      else {
        rows.push_back(el.element);

        // we replace the cells in the correct column
        for (Cell cell : el.element->cells) {
          std::cout << "row " << el.element->represent << " col "
                    << cell.colHead->represent << " : " << cell.colHead
                    << std::endl;
          cell.colHead->cells.push_front(cell);
          cell.colHead->count++;
        }
      }
      stack.pop();
    }
    // remove the last group in our solution
    solution.pop_back();
    // remove the mark (index=-1)
    stack.pop();
  } else {
    // We save our col here, so it want change if we modify the matrix col/row
    // order
    Head col2 = **col;
    for (Cell cell : col2.cells) {
      print();
      // we try to remove a row, if it's not working with this row, we test with
      // another;
      removeRow(cell.rowHead);
    }

    std::cout << "=======================" << std::endl
              << "END REMOVE ALL COLUMN  " << col2.represent << std::endl
              << "=======================" << std::endl
              << std::endl;
  }
}

// remove all row/col connect to this row
void SparseMatrixStack::removeRow(Head *row) {
  std::string rowRepresent = row->represent;

  std::cout << std::endl
            << "===================" << std::endl
            << "REMOVE ALL ROW " << rowRepresent << std::endl
            << "===================" << std::endl
            << std::endl;

  print();

  // It's our mark, to separate between the previous test, and the current one
  stack.push({nullptr, nullptr, -1});
  std::string result = row->represent;

  // For each col in our row
  for (Cell cell : row->cells) {
    Head *col = cell.colHead;
    result += " " + col->represent;
    removeCol(col);
    print();
  }
  std::cout << std::endl
            << "=======================" << std::endl
            << "END REMOVE ALL ROW " << rowRepresent << std::endl
            << "======================" << std::endl
            << std::endl;

  solution.push_back(result);

  // We try to resolve the new matrix we got
  resolve();
}

void SparseMatrixStack::removeCol(Head *col) {
  std::cout << "=======================" << std::endl
            << "REMOVE COL " << col->represent << std::endl
            << "=======================" << std::endl
            << std::endl;

  // for each element in our col
  while (col->cells.size() != 0) {
    Cell cellCol = col->cells.front();

    // we want to erase all this row
    Head *row = cellCol.rowHead;
    std::cout << cellCol.rowHead->represent << ":" << cellCol.colHead->represent
              << std::endl;

    // we remove all the cells connect to this row from all the col
    for (Cell cell : row->cells) {
      cell.colHead->count--;
      cell.colHead->cells.remove(cell);
    }

    // and we remove our row from the matrice
    rows.remove(row);
    // but we save it in our stack (so that we can undo the change)
    stack.push({row, &rows, 1});
  }

  /// we remove the col
  cols.remove(col);
  // and we save it
  stack.push({col, &cols, 1});
}