#include "assign_pattern_storage.h"

#include <stdexcept>

void AssignPatternStorage::AddAssignPattern(int statement_number,
                                            std::string lhs, std::string rhs) {
  patterns_map_.emplace(statement_number,
                        std::pair<std::string, std::string>(lhs, rhs));
}

std::unordered_set<std::string> AssignPatternStorage::GetAllPattern(
    std::string pattern, bool front_wildcard, bool back_wildcard) const {
  std::string::size_type pattern_start_pos = 0;
  std::string::size_type pattern_end_pos = 0;
  for (int i = 0; i < (int)pattern.size(); i++) {
    if (pattern[i] == '(') {
      pattern_start_pos++;
    } else {
      break;
    }
  }
  for (int i = pattern.size() - 1; i >= 0; i--) {
    if (pattern[i] == ')') {
      pattern_end_pos++;
    } else {
      break;
    }
  }

  std::unordered_set<std::string> res;

  if (!front_wildcard && !back_wildcard) {
    for (auto i : patterns_map_) {
      if (i.second.second.compare(pattern) == 0) {
        res.emplace(std::to_string(i.first));
      }
    }
  } else if (front_wildcard && back_wildcard) {
    for (auto i : patterns_map_) {
      if (i.second.second.find(pattern) != std::string::npos) {
        res.emplace(std::to_string(i.first));
      }
    }
  } else if (!front_wildcard && back_wildcard) {
    for (auto i : patterns_map_) {
      if (i.second.second.length() >= pattern.length()) {
        std::string::size_type string_start_pos = 0;
        for (int j = 0; j < (int)i.second.second.size(); j++) {
          if (i.second.second[j] == '(') {
            string_start_pos++;
          } else {
            break;
          }
        }
        if (string_start_pos >= pattern_start_pos) {
          if (i.second.second.substr(string_start_pos - pattern_start_pos)
                  .rfind(pattern, 0) == 0) {
            res.emplace(std::to_string(i.first));
          }
        }
      }
    }
  } else if (front_wildcard && !back_wildcard) {
    for (auto i : patterns_map_) {
      if (i.second.second.length() >= pattern.length()) {
        std::string::size_type string_end_pos = 0;
        for (int j = i.second.second.size() - 1; j >= 0; j--) {
          if (i.second.second[j] == ')') {
            string_end_pos++;
          } else {
            break;
          }
        }
        if (string_end_pos >= pattern_end_pos) {
          std::string trimmed = i.second.second.substr(
              0, i.second.second.size() - string_end_pos + pattern_end_pos);
          if (trimmed.size() >= pattern.size()) {
            if (trimmed.compare(trimmed.size() - pattern.size(), pattern.size(),
                                pattern) == 0) {
              res.emplace(std::to_string(i.first));
            }
          }
        }
      }
    }
  } else {
    throw std::invalid_argument("Missing wildcard booleans");
  }
  return res;
}

//(i.second.first.compare(lhs) == 0)

std::unordered_set<std::string> AssignPatternStorage::GetPattern(
    std::string lhs, std::string pattern, bool front_wildcard,
    bool back_wildcard) const {
  std::string::size_type pattern_start_pos = 0;
  std::string::size_type pattern_end_pos = 0;
  for (int i = 0; i < (int)pattern.size(); i++) {
    if (pattern[i] == '(') {
      pattern_start_pos++;
    } else {
      break;
    }
  }
  for (int i = pattern.size() - 1; i >= 0; i--) {
    if (pattern[i] == ')') {
      pattern_end_pos++;
    } else {
      break;
    }
  }

  std::unordered_set<std::string> res;

  if (!front_wildcard && !back_wildcard) {
    for (auto i : patterns_map_) {
      if ((i.second.first.compare(lhs) == 0) &&
          (i.second.second.compare(pattern) == 0)) {
        res.emplace(std::to_string(i.first));
      }
    }
  } else if (front_wildcard && back_wildcard) {
    for (auto i : patterns_map_) {
      if ((i.second.first.compare(lhs) == 0) &&
          (i.second.second.find(pattern) != std::string::npos)) {
        res.emplace(std::to_string(i.first));
      }
    }
  } else if (!front_wildcard && back_wildcard) {
    for (auto i : patterns_map_) {
      if (i.second.second.length() >= pattern.length()) {
        std::string::size_type string_start_pos = 0;
        for (int j = 0; j < (int)i.second.second.size(); j++) {
          if (i.second.second[j] == '(') {
            string_start_pos++;
          } else {
            break;
          }
        }
        if (string_start_pos >= pattern_start_pos) {
          if ((i.second.first.compare(lhs) == 0) &&
              (i.second.second.substr(string_start_pos - pattern_start_pos)
                   .rfind(pattern, 0) == 0)) {
            res.emplace(std::to_string(i.first));
          }
        }
      }
    }
  } else if (front_wildcard && !back_wildcard) {
    for (auto i : patterns_map_) {
      if (i.second.second.length() >= pattern.length()) {
        std::string::size_type string_end_pos = 0;
        for (int j = i.second.second.size() - 1; j >= 0; j--) {
          if (i.second.second[j] == ')') {
            string_end_pos++;
          } else {
            break;
          }
        }
        if (string_end_pos >= pattern_end_pos) {
          std::string trimmed = i.second.second.substr(
              0, i.second.second.size() - string_end_pos + pattern_end_pos);
          if (trimmed.size() >= pattern.size()) {
            if ((i.second.first.compare(lhs) == 0) &&
                (trimmed.compare(trimmed.size() - pattern.size(),
                                 pattern.size(), pattern) == 0)) {
              res.emplace(std::to_string(i.first));
            }
          }
        }
      }
    }
  } else {
    throw std::invalid_argument("Missing wildcard booleans");
  }
  return res;
}

void AssignPatternStorage::Clear() { patterns_map_.clear(); }
