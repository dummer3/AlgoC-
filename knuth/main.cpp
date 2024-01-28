#include "sparseMatrix.hpp"

int main(int argc, char const *argv[])
{
    SparseMatrix mat = SparseMatrix("test.txt");
    mat.print();
    mat.resolve();
    return 0;
}
