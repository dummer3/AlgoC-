#include <queue>

/**
 *
 * \class p_queue
 * \brief Priority queue with a specific find function for our A algorithm
 *
 **/

template <class T, class Compare, class Container = std::vector<T>>
class p_queue : public std::priority_queue<T, Container, Compare> {

public:
  // IMPORTANT TO UNDERSTAND
  // the attribute c is the underlying container for the stack (vector, ...)

  /**
   *
   * \fn bool find(const Type &val)
   * \brief return true if our val is inside the queue.
   * But,if the new tile weight is better, we erase the one store and return
   *false \param const Type & val: the val to test \return bool: if the val is
   *inside or not
   *
   **/
  bool find(const T &val) {
    auto first = this->c.cbegin();
    auto last = this->c.cend();

    while (first != last) {
      if (*first == val) {

        // if the weight of our new value is less than the one store
        // ==> We find a better path to this tile
        if (val < *first) {
          this->c.erase(first);

          // return false to add the new one
          return false;
        }
        return true;
      }
      ++first;
    }
    return false;
  }
};
