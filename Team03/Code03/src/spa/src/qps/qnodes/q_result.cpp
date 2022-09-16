//
// Created by Josiah Khoo on 17/9/22.
//

#include "q_result.h"

#include <cassert>
#include <unordered_set>
#include <utility>

QResult::QResult(std::vector<std::vector<std::string>> rows,
                 std::vector<Synonym> synonyms)
    : rows_(std::move(rows)), synonyms_(std::move(synonyms)) {}

std::vector<Synonym> QResult::GetSynonyms() const { return synonyms_; }

std::vector<std::vector<std::string>> QResult::GetRows() const { return rows_; }

QResult QResult::Join(const QResult& other_result) const {
  // Get all common synonyms
  std::vector<std::pair<int, int>> common_indexes;
  for (int i = 0; i < GetSynonyms().size(); i++) {
    for (int j = 0; j < other_result.GetSynonyms().size(); j++) {
      if (GetSynonyms().at(i) == other_result.GetSynonyms().at(j)) {
        common_indexes.emplace_back(i, j);
      }
    }
  }
  assert(!common_indexes.empty());
  // Create new merge synonyms list
  std::vector<Synonym> new_syns;
  int n_cols = GetSynonyms().size() + other_result.GetSynonyms().size() -
               common_indexes.size();
  new_syns.reserve(n_cols);
  for (const auto& syn : GetSynonyms()) {
    new_syns.emplace_back(syn);
  }
  for (int i = 0; i < other_result.GetSynonyms().size(); i++) {
    for (auto [_, idx] : common_indexes) {
      if (idx == i) {
        // Skip if idx matches (which means included already)
        continue;
      }
    }
    new_syns.emplace_back(other_result.GetSynonyms().at(i));
  }

  // Merge join algorithm (can be optimised into sort merge join in the future)
  std::vector<std::vector<std::string>> new_rows;
  for (auto row1 : GetRows()) {
    for (auto row2 : GetRows()) {
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
        for (auto [_, idx] : common_indexes) {
          if (idx == i) {
            // Skip if idx matches (which means included already)
            continue;
          }
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
  std::vector<int> indexes;
  for (int i = 0; i < GetSynonyms().size(); i++) {
    for (const auto& syn : synonyms) {
      if (GetSynonyms().at(i) == syn) {
        indexes.emplace_back(i);
      }
    }
  }
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
