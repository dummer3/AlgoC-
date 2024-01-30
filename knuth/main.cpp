#include "sparseMatrixStack.hpp"

int main(int argc, char const *argv[]) {
  std::string filePath = "test2.txt";
  if (argc > 1)
    filePath = argv[1];
  SparseMatrixStack mat(filePath);
  mat.print();
  mat.resolve();
  return 0;
}
