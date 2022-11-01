#ifndef SPA_TEAM03_CODE03_SRC_UNIT_TESTING_SRC_HELPER_HPP_
#define SPA_TEAM03_CODE03_SRC_UNIT_TESTING_SRC_HELPER_HPP_

#include <algorithm>

template <class Container>
bool contains(const Container& container,
              const typename Container::value_type& element) {
  return std::find(container.begin(), container.end(), element) !=
         container.end();
}

#endif  // SPA_TEAM03_CODE03_SRC_UNIT_TESTING_SRC_HELPER_HPP_
