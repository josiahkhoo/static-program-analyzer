#include "q_result.h"

#include <cassert>
#include <unordered_set>
#include <utility>

QResult::QResult(std::vector<std::vector<std::string>> rows,
                 std::vector<Synonym> synonyms)
    : rows_(std::move(rows)),
      synonyms_(std::move(synonyms)),
      has_been_queried_(true) {}

QResult::QResult(bool has_been_queried) : has_been_queried_(has_been_queried) {}

std::vector<Synonym> QResult::GetSynonyms() const { return synonyms_; }

std::vector<std::vector<std::string>> QResult::GetRows() const { return rows_; }

bool QResult::HasBeenQueried() const { return has_been_queried_; }

QResult QResult::Join(const QResult& other_result) const {
  // Return either one if one is empty
  if (GetSynonyms().empty()) {
    return other_result;
  } else if (other_result.GetSynonyms().empty()) {
    return {GetRows(), GetSynonyms()};
  }

  // Get all common synonyms
  std::vector<std::pair<int, int>> common_indexes;
  for (int i = 0; i < GetSynonyms().size(); i++) {
    for (int j = 0; j < other_result.GetSynonyms().size(); j++) {
      if (GetSynonyms().at(i) == other_result.GetSynonyms().at(j)) {
        common_indexes.emplace_back(i, j);
      }
    }
  }
  // Create new merge synonyms list
  std::vector<Synonym> new_syns;
  int n_cols = GetSynonyms().size() + other_result.GetSynonyms().size() -
               common_indexes.size();
  new_syns.reserve(n_cols);
  for (const auto& syn : GetSynonyms()) {
    new_syns.emplace_back(syn);
  }
  for (int i = 0; i < other_result.GetSynonyms().size(); i++) {
    bool match = false;
    for (auto [_, idx] : common_indexes) {
      if (idx == i) {
        // Skip if idx matches (which means included already)
        match = true;
        continue;
      }
    }
    if (match) {
      continue;
    }
    new_syns.emplace_back(other_result.GetSynonyms().at(i));
  }

  // Merge join algorithm (can be optimised into sort merge join in the future)
  std::vector<std::vector<std::string>> new_rows;
  for (auto row1 : GetRows()) {
    for (auto row2 : other_result.GetRows()) {
      // Check if row1 == row2 on common indexes
      bool match = true;
      for (auto [idx1, idx2] : common_indexes) {
        if (row1[idx1] != row2[idx2]) {
          match = false;
          break;
        }
      }
      if (!match) {
        // Break if it doesn't
        continue;
      }

      // Add to new_rows if it reaches here
      std::vector<std::string> new_row;
      new_row.reserve(n_cols);
      for (const auto& entry : row1) {
        new_row.emplace_back(entry);
      }
      for (int i = 0; i < row2.size(); i++) {
        bool match_idx = false;
        for (auto [_, idx] : common_indexes) {
          if (idx == i) {
            // Skip if idx matches (which means included already)
            match_idx = true;
            continue;
          }
        }
        if (match_idx) {
          continue;
        }
        new_row.emplace_back(row2.at(i));
      }
      new_rows.push_back(new_row);
    }
  }
  return {new_rows, new_syns};
}

std::vector<std::vector<std::string>> QResult::GetRows(
    const std::vector<Synonym>& synonyms) const {
  // Retrieve index of synonym table
  std::vector<int> indexes;
  for (const auto& syn : synonyms) {
    for (int i = 0; i < GetSynonyms().size(); i++) {
      if (GetSynonyms().at(i) == syn) {
        indexes.emplace_back(i);
      }
    }
  }
  // Return empty if indexes size != synonyms
  if (indexes.size() != synonyms.size()) return {};
  std::unordered_set<std::vector<std::string>, VectorHash> new_rows_set;
  for (auto row : GetRows()) {
    std::vector<std::string> new_row;
    new_row.reserve(indexes.size());
    for (auto index : indexes) {
      new_row.push_back(row[index]);
    }
    new_rows_set.insert(new_row);
  }
  // Optimise later
  std::vector<std::vector<std::string>> new_rows;
  new_rows.reserve(new_rows_set.size());
  for (const auto& new_row : new_rows_set) {
    new_rows.push_back(new_row);
  }
  return new_rows;
}

QResult QResult::Intersect(const QResult& other_result) const {
  assert(GetSynonyms() == other_result.GetSynonyms());
  if (GetRows().empty() || other_result.GetRows().empty()) {
    return {{}, GetSynonyms()};
  }
  std::unordered_set<std::vector<std::string>, VectorHash> set;
  for (const auto& row : GetRows()) {
    set.insert(row);
  }
  std::vector<std::vector<std::string>> intersections;
  intersections.reserve(std::min(GetRows().size(), GetRows().size()));
  for (const auto& row : other_result.GetRows()) {
    if (set.erase(row) > 0) {  // if n exists in set, then 1 is returned and n
                               // is erased; otherwise, 0.
      intersections.push_back(row);
    }
  }
  return {intersections, GetSynonyms()};
}

bool QResult::operator==(const QResult& rhs) const {
  return rows_ == rhs.rows_ && synonyms_ == rhs.synonyms_;
}

bool QResult::operator!=(const QResult& rhs) const { return !(rhs == *this); }
