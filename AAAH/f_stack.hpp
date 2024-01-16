/**
 * \file f_stack.hpp
 * \brief Template for a stack with extension
 * \author Cliquot Théo
 * \date 28/01/2023
 */

#include <deque>
#include <stack>

/**
 *
 * \class f_stack
 * \brief stack with a find function for our A algorithm
 *
 **/

template <class Type> class f_stack : public std::stack<Type> {
public:
  // IMPORTANT TO UNDERSTAND
  // the attribute c is the underlying container for the stack (vector, ...)

  /**
   *
   * \fn bool find(const Type &val) const
   * \brief return if our val is inside the stack
   * \param const Type & val: the val to test
   * \return bool: if the val is inside our not
   *
   **/
  bool find(const Type &val) const {
    auto first = this->c.cbegin();
    auto last = this->c.cend();

    while (first != last) {
      if (*first == val)
        return true;
      ++first;
    }
    return false;
  }
};
