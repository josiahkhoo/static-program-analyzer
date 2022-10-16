#include "q_result.h"

#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <utility>

QResult::QResult(RowColumn rows, std::vector<Synonym> synonyms)
    : rows_(std::move(rows)),
      synonyms_(std::move(synonyms)),
      has_been_queried_(true) {}

QResult::QResult(bool has_been_queried) : has_been_queried_(has_been_queried) {}

std::vector<Synonym> QResult::GetSynonyms() const { return synonyms_; }

int QResult::GetSynonymsSize() const { return (int)synonyms_.size(); }

bool QResult::IsSynonymsEmpty() const { return synonyms_.empty(); }

Synonym QResult::GetSynonymAt(int index) const { return synonyms_.at(index); }

RowColumn QResult::GetRows() const { return rows_; }

bool QResult::HasBeenQueried() const { return has_been_queried_; }

QResult QResult::Join(const QResult& other_result) const {
  // Return either one if one is empty
  if (IsSynonymsEmpty()) {
    return other_result;
  } else if (other_result.IsSynonymsEmpty()) {
    return {GetRows(), GetSynonyms()};
  }

  // Get all common synonyms
  // Convert current results into hashmap
  std::unordered_map<Synonym, int> syn_index_map;
  for (int i = 0; i < GetSynonymsSize(); i++) {
    Synonym key = GetSynonymAt(i);
    syn_index_map.emplace(key, i);
  }
  // List of index pairs where syn is in A and B
  std::vector<std::pair<int, int>> common_indexes;
  std::unordered_set<int> common_indexes_second_set;
  for (int j = 0; j < other_result.GetSynonymsSize(); j++) {
    Synonym key = other_result.GetSynonymAt(j);
    if (syn_index_map.count(key)) {
      int i = syn_index_map.find(key)->second;
      common_indexes.emplace_back(i, j);
      common_indexes_second_set.emplace(j);
    }
  }

  // Create new merge synonyms list
  std::vector<Synonym> new_synonyms;
  int n_cols = GetSynonymsSize() + other_result.GetSynonymsSize() -
               (int)common_indexes.size();
  new_synonyms.reserve(n_cols);

  // Populate new syn with result
  for (const auto& syn : GetSynonyms()) {
    new_synonyms.emplace_back(syn);
  }
  for (int i = 0; i < other_result.GetSynonymsSize(); i++) {
    if (common_indexes_second_set.count(i)) {
      continue;
    }
    new_synonyms.emplace_back(other_result.GetSynonymAt(i));
  }

  auto a = GetRows();
  auto b = other_result.GetRows();

//  std::unordered_set<std::string> hashset;
//  for (auto [idx1, _] : common_indexes) {
//    for (auto& i : a) {
//      hashset.insert(i[idx1]);
//    }
//  }

  //  for (auto [idx1, idx2] : common_indexes) {
  //    auto res = HashJoin(a, idx1, b, idx2, hashset);
  //    return {res, new_synonyms};
  //  }
  auto new_new_rows = HashJoin(a, b, common_indexes);

  // Nested-Loop Join
  RowColumn new_rows;
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
      for (int i = 0; i < (int)row2.size(); i++) {
        if (common_indexes_second_set.count(i)) {
          continue;
        }
        new_row.emplace_back(row2.at(i));
      }
      new_rows.push_back(new_row);
    }
  }
  return {new_new_rows, new_synonyms};
}

RowColumn QResult::HashJoin(RowColumn a, RowColumn b,
                            std::vector<std::pair<int, int>> common_indexes) {
  std::unordered_multimap<std::string, int> hashmap;
  // hash
  for (auto item: common_indexes) {
    for (size_t i = 0; i < a.size(); ++i) {
      hashmap.insert(std::make_pair(a[i][item.first], i));
    }
  }

  // map
  RowColumn result;
  for (const auto& i : b) {
    auto range = hashmap.equal_range(i[common_indexes[0].second]);
    for (auto it = range.first; it != range.second; ++it) {
      RowColumn::value_type row;
      row.insert(row.end(), a[it->second].begin(), a[it->second].end());
      for (const auto& e : i) {
        if (!hashmap.count(e)) {
          row.insert(row.end(), e);
        }
      }
      result.push_back(std::move(row));
    }
  }
  return result;
}

RowColumn QResult::GetRows(const std::vector<Synonym>& synonyms) const {
  // Retrieve index of synonym table
  std::vector<int> indexes;
  for (const auto& syn : synonyms) {
    for (int i = 0; i < GetSynonymsSize(); i++) {
      if (GetSynonymAt(i) == syn) {
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
  RowColumn new_rows;
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
    set.emplace(row);
  }
  RowColumn intersections;
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
