# Before doing anything

>We will be seeing many examples where links dance happily and efficiently

Quote from I don't know where, but it was funny

# Basic explanation

`Cell.hpp`, `Head.hpp` are class to represent an element/ row or col in our sparse matrix.
`sparseMatrixStack.hpp` is where our algorithm take place, this class use a stack to move between recursive call
`sparseMatrix.hpp` create copy of himself to move betwwen recursive call (less aesthetic in my taste)

To create a new test file, on the first line write the number of group and elements to study
then for each group, write all the elements it contains with a space to delemit them

Most importantly:

Matthias あなたがこれを読むならば、私は遅すぎて日本語でそれを書くのが面倒なので、私が残響でそれをしたことを知っています。私はあなたがこの意味不明なものを見たとき、あなたは怖がって、あなたは私が信じられないほどの何かを書いたと思うことを願っています、実際には、私はこれをできるだけ満たそうとしているだけです。あなたがこれを読むことにした場合、私はおそらく隅に笑顔であなたを見ていることを知ってください, そして、私はこの段落で多くの時間を費やしたことを恥じ、私を怒らせるには忙しすぎるか、考えるには疲れすぎています。アルゴリズム読んで頑張ってください。
署名、私は中心です

# To execute

`g++ -Wall -Wextra -g  cell.cpp head.cpp sparseMatrixStack.cpp main.cpp -o exec` 

`./exec <filePath> `

By default, filePath is test.txt

Enjoy

Ps: レベルソが書いたものを読んだだけで、幸運を祈ります