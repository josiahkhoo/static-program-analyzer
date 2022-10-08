#include "query_pattern_processor.h"

std::string QueryPatternProcessor::ProcessAssignPattern(std::string exp) const {
  if (exp.find('(') == std::string::npos) {
    return ProcessAssignPatternHelper(exp);
  } else {
    char high_operators[] = {'*', '/', '%'};
    char low_operators[] = {'+', '-'};
    // TODO: Remove this if not used
    //    char operators[] = {'+', '-', '*', '/', '%'};

    unsigned int high_operators_n = sizeof(high_operators) / sizeof(char);
    unsigned int low_operators_n = sizeof(low_operators) / sizeof(char);
    // TODO: Remove this if not used
    //    unsigned int operators_n = sizeof(operators) / sizeof(char);

    std::vector<std::pair<int, int>> pairs = {};
    int counter = 0;
    for (int i = 0; i < (int)exp.length(); i++) {
      int open_bracket_pos;
      int close_bracket_pos;
      if (exp.at(i) == '(') {
        counter++;
        if (counter == 1) {
          open_bracket_pos = i;
        }
      }
      if (exp.at(i) == ')') {
        counter--;
        if (counter == 0) {
          close_bracket_pos = i;
          pairs.emplace_back(open_bracket_pos, close_bracket_pos);
        }
      }
    }

    // Case: Check if there is a big bracket encapsulating the whole expression
    if (pairs.size() == 1 && pairs.front().first == 0 &&
        pairs.front().second == (int)exp.length() - 1) {
      return ProcessAssignPattern(exp.substr(1, exp.length() - 2));
    }

    std::set<int> outer_bracket_indexes =
        GetOuterBracketIndexes(exp.length(), pairs);

    // Case: Check if outer exp does not contain any low_operators
    if (!CheckContains(exp, outer_bracket_indexes, low_operators,
                       low_operators_n)) {
      for (int j = exp.length() - 1; j >= 0; j--) {
        if (outer_bracket_indexes.find(j) != outer_bracket_indexes.end()) {
          for (int k = 0; k < (int)high_operators_n; k++) {
            if (exp.at(j) == high_operators[k]) {
              std::string lhs = exp.substr(0, j);
              std::string rhs = exp.substr(j + 1);
              return "(" + ProcessAssignPattern(lhs) + exp.at(j) +
                     ProcessAssignPattern(rhs) + ")";
            }
          }
        }
      }
    } else {
      for (int j = exp.length() - 1; j >= 0; j--) {
        if (outer_bracket_indexes.find(j) != outer_bracket_indexes.end()) {
          for (int k = 0; k < (int)low_operators_n; k++) {
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
  }
  assert(!"Should not reach here");
}

std::string QueryPatternProcessor::ProcessAssignPatternHelper(
    std::string exp) const {
  char high_operators[] = {'*', '/', '%'};
  char low_operators[] = {'+', '-'};
  char operators[] = {'+', '-', '*', '/', '%'};

  unsigned int high_operators_n = sizeof(high_operators) / sizeof(char);
  unsigned int low_operators_n = sizeof(low_operators) / sizeof(char);
  unsigned int operators_n = sizeof(operators) / sizeof(char);

  if (exp.empty()) {
    return exp;
  }
  // Base case: Check if exp does not contain any operators
  else if (!CheckContains(exp, operators, operators_n)) {
    return "(" + exp + ")";
  }
  // Case: Check if exp does not contain any low_operators
  else if (!CheckContains(exp, low_operators, low_operators_n)) {
    for (int j = exp.length() - 1; j >= 0; j--) {
      for (int k = 0; k < (int)high_operators_n; k++) {
        if (exp.at(j) == high_operators[k]) {
          std::string lhs = exp.substr(0, j);
          std::string rhs = exp.substr(j + 1);
          return "(" + ProcessAssignPatternHelper(lhs) + exp.at(j) +
                 ProcessAssignPatternHelper(rhs) + ")";
        }
      }
    }
  } else {
    for (int j = exp.length() - 1; j >= 0; j--) {
      for (int k = 0; k < (int)low_operators_n; k++) {
        if (exp.at(j) == low_operators[k]) {
          std::string lhs = exp.substr(0, j);
          std::string rhs = exp.substr(j + 1);
          return "(" + ProcessAssignPatternHelper(lhs) + exp.at(j) +
                 ProcessAssignPatternHelper(rhs) + ")";
        }
      }
    }
  }
  assert(!"Should not reach here");
}

bool QueryPatternProcessor::CheckContains(std::string exp, char *arr,
                                          unsigned int n) const {
  for (int i = 0; i < (int)n; i++) {
    if (exp.find(arr[i]) != std::string::npos) {
      return true;
    }
  }
  return false;
}

bool QueryPatternProcessor::CheckContains(std::string exp,
                                          std::set<int> outer_bracket_indexes,
                                          char *arr, unsigned int n) const {
  for (int index : outer_bracket_indexes) {
    for (int i = 0; i < (int)n; i++) {
      if (exp.at(index) == arr[i]) {
        return true;
      }
    }
  }
  return false;
}

std::set<int> QueryPatternProcessor::GetOuterBracketIndexes(
    int exp_length, std::vector<std::pair<int, int>> pairs) const {
  std::set<int> res;
  for (int i = 0; i < exp_length; i++) {
    res.emplace(i);
  }
  for (auto p : pairs) {
    for (int j = p.first; j <= p.second; j++) {
      res.erase(j);
    }
  }
  return res;
}
