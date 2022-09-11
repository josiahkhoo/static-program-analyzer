#include "assign_pattern_storage.h"

std::unordered_map<int, std::pair<std::string, std::string>>
    AssignPatternStorage::patterns_map_;

void AssignPatternStorage::AddAssignPattern(AssignEntity assignEntity) {
  int statement_number = assignEntity.GetStatementNumber();
  std::string lhs = assignEntity.GetLeftHandSidePattern();
  std::string rhs = assignEntity.GetRightHandSidePattern();
  patterns_map_.emplace(statement_number,
                        std::pair<std::string, std::string>(lhs, rhs));
}

std::unordered_set<std::string> AssignPatternStorage::GetAllPattern(
    std::string pattern, bool front_wildcard, bool back_wildcard) const {
  std::unordered_set<std::string> res;
  if (!front_wildcard && !back_wildcard) {
    for (auto i : patterns_map_) {
      if (i.second.second.compare(pattern) == 0) {
        res.emplace(std::to_string(i.first));
      }
    }
  }
  if (front_wildcard && back_wildcard) {
    for (auto i : patterns_map_) {
      if (i.second.second.find(pattern) != std::string::npos) {
        res.emplace(std::to_string(i.first));
      }
    }
  }
  if (front_wildcard && !back_wildcard) {
    for (auto i : patterns_map_) {
      if (i.second.second.rfind(pattern, 0) == 0) {
        res.emplace(std::to_string(i.first));
      }
    }
  }
  if (!front_wildcard && back_wildcard) {
    for (auto i : patterns_map_) {
      if (i.second.second.length() >= pattern.length()) {
        if (i.second.second.compare(i.second.second.length() - pattern.length(),
                                    pattern.length(), pattern) == 0) {
          res.emplace(std::to_string(i.first));
        }
      }
    }
  }
  return res;
}

std::unordered_set<std::string> AssignPatternStorage::GetPattern(
    std::string lhs, std::string pattern, bool front_wildcard,
    bool back_wildcard) const {
  std::unordered_set<std::string> res;
  if (!front_wildcard && !back_wildcard) {
    for (auto i : patterns_map_) {
      if ((i.second.first.compare(lhs) == 0) &&
          (i.second.second.compare(pattern) == 0)) {
        res.emplace(std::to_string(i.first));
      }
    }
  }
  if (front_wildcard && back_wildcard) {
    for (auto i : patterns_map_) {
      if ((i.second.first.compare(lhs) == 0) &&
          (i.second.second.find(pattern) != std::string::npos)) {
        res.emplace(std::to_string(i.first));
      }
    }
  }
  if (front_wildcard && !back_wildcard) {
    for (auto i : patterns_map_) {
      if ((i.second.first.compare(lhs) == 0) &&
          (i.second.second.rfind(pattern, 0) == 0)) {
        res.emplace(std::to_string(i.first));
      }
    }
  }
  if (!front_wildcard && back_wildcard) {
    for (auto i : patterns_map_) {
      if (i.second.second.length() >= pattern.length()) {
        if ((i.second.first.compare(lhs) == 0) &&
            (i.second.second.compare(
                 i.second.second.length() - pattern.length(), pattern.length(),
                 pattern) == 0)) {
          res.emplace(std::to_string(i.first));
        }
      }
    }
  }
  return res;
}

void AssignPatternStorage::Clear() { patterns_map_.clear(); }
