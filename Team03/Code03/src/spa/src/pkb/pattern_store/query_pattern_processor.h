#ifndef SPA_QUERY_PATTERN_PROCESSOR_H
#define SPA_QUERY_PATTERN_PROCESSOR_H

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "string"

class QueryPatternProcessor {
 public:
  std::string ProcessAssignPattern(std::string exp) const;

 private:
  std::string ProcessAssignPatternHelper(std::string exp) const;
  std::set<int> GetOuterBracketIndexes(int exp_length, std::vector<std::pair<int, int>> pairs) const;
  bool CheckContains(std::string exp, char *arr, unsigned int n) const;
  bool CheckContains(std::string exp, std::set<int> outer_bracket_indexes, char *arr, unsigned int n) const;
  bool IsOperator(char c) const;
};

#endif  // SPA_QUERY_PATTERN_PROCESSOR_H
