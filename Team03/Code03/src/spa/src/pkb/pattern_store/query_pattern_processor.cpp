#include "query_pattern_processor.h"

std::string QueryPatternProcessor::ProcessAssignPattern(std::string exp) const {
  char high_operators[] = {'*', '/', '%'};
  char low_operators[] = {'+', '-'};
  char operators[] = {'+', '-', '*', '/', '%'};

  unsigned int high_operators_n = sizeof(high_operators) / sizeof(char);
  unsigned int low_operators_n = sizeof(low_operators) / sizeof(char);
  unsigned int operators_n = sizeof(operators) / sizeof(char);

  // Base case: Check if exp does not contain any operators
  if (!CheckContains(exp, operators, operators_n)) {
    return "(" + exp + ")";
  }
  // Sub case: Check if exp does not contain any low_operators
  else if (!CheckContains(exp, low_operators, low_operators_n)) {
    for (int j = exp.length() - 1; j >= 0; j--) {
      for (int k = 0; k < high_operators_n; k++) {
        if (exp.at(j) == high_operators[k]) {
          std::string lhs = exp.substr(0, j);
          std::string rhs = exp.substr(j + 1);
          return "(" + ProcessAssignPattern(lhs) + exp.at(j) +
                 ProcessAssignPattern(rhs) + ")";
        }
      }
    }
  } else {
    for (int j = exp.length() - 1; j >= 0; j--) {
      for (int k = 0; k < low_operators_n; k++) {
        if (exp.at(j) == low_operators[k]) {
          std::string lhs = exp.substr(0, j);
          std::string rhs = exp.substr(j + 1);
          return "(" + ProcessAssignPattern(lhs) + exp.at(j) +
                 ProcessAssignPattern(rhs) + ")";
        }
      }
    }
  }
}

bool QueryPatternProcessor::CheckContains(std::string exp, char *arr,
                                          unsigned int n) const {
  for (int i = 0; i < n; i++) {
    if (exp.find(arr[i]) != std::string::npos) {
      return true;
    }
  }
  return false;
}
