#ifndef SPA_QUERY_PATTERN_PROCESSOR_H
#define SPA_QUERY_PATTERN_PROCESSOR_H

#include "string"

class QueryPatternProcessor {
 public:
  std::string ProcessAssignPattern(std::string exp);

 private:
  bool CheckContains(std::string exp, char *arr, unsigned int n);
};

#endif  // SPA_QUERY_PATTERN_PROCESSOR_H
