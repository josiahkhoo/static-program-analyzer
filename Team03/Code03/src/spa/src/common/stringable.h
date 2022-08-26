#include <string>
#ifndef SPA_STRINGABLE_H
#define SPA_STRINGABLE_H

class Stringable {
 public:
  virtual std::string ToString() const = 0;
};

#endif  // SPA_STRINGABLE_H
