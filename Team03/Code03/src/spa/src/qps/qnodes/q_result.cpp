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

QResult QResult::Join(const QResult& other_result) {
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
  std::vector<Synonym> new_synonyms = GenerateSynonymList(
      other_result, common_indexes, common_indexes_second_set);

  RowColumn new_rows;
  if (common_indexes.empty()) {
    new_rows = CrossJoin(other_result);
  } else {
    //    new_rows = HashJoin(other_result, common_indexes,
    //    common_indexes_second_set,
    //                        (int)new_synonyms.size());
    new_rows =
        SortMergeJoin(other_result, common_indexes, common_indexes_second_set,
                      (int)new_synonyms.size());
  }
  return {new_rows, new_synonyms};
}

std::vector<Synonym> QResult::GenerateSynonymList(
    const QResult& other_result,
    const std::vector<std::pair<int, int>>& common_indexes,
    const std::unordered_set<int>& common_indexes_second_set) const {
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
  return new_synonyms;
}

RowColumn QResult::SortMergeJoin(
    const QResult& other_result,
    const std::vector<std::pair<int, int>>& common_indexes,
    const std::unordered_set<int>& common_indexes_second_set,
    int n_cols) const {
  RowColumn new_rows;
  std::vector<int> common_indexes1, common_indexes2;
  common_indexes1.reserve(common_indexes.size());
  common_indexes2.reserve(common_indexes.size());

  std::vector<std::pair<int, int>> common_indexes1_pair, common_indexes2_pair;
  for (auto [idx1, idx2] : common_indexes) {
    common_indexes1.emplace_back(idx1);
    common_indexes2.emplace_back(idx2);
    common_indexes1_pair.emplace_back(idx1, idx1);
    common_indexes2_pair.emplace_back(idx2, idx2);
  }
  RowColumn sorted_rows1 = Sort(common_indexes1).GetRows();
  RowColumn sorted_rows2 = other_result.Sort(common_indexes2).GetRows();
  int row1_counter = 0, row2_counter = 0;
  while ((row1_counter < (int)sorted_rows1.size()) &&
         (row2_counter < (int)sorted_rows2.size())) {
    auto row1 = sorted_rows1[row1_counter];
    auto row2 = sorted_rows2[row2_counter];
    int comparator = CompareRow(row1, row2, common_indexes);
    if (comparator == -1) {
      row1_counter++;
    } else if (comparator == 1) {
      row2_counter++;
    } else {
      int row1_endpoint = row1_counter, row2_endpoint = row2_counter;
      while (row1_endpoint < (int)(sorted_rows1.size() - 1)) {
        // Find cluster of same keys result1
        row1_endpoint++;
        if (CompareRow(row1, sorted_rows1[row1_endpoint],
                       common_indexes1_pair) != 0) {
          row1_endpoint--;
          break;
        }
      }
      while (row2_endpoint < (int)(sorted_rows2.size() - 1)) {
        // Find cluster of same keys for result2
        row2_endpoint++;
        if (CompareRow(row2, sorted_rows2[row2_endpoint],
                       common_indexes2_pair) != 0) {
          row2_endpoint--;
          break;
        }
      }
      for (int row1_join_idx = row1_counter; row1_join_idx < row1_endpoint + 1;
           row1_join_idx++) {
        for (int row2_join_idx = row2_counter;
             row2_join_idx < row2_endpoint + 1; row2_join_idx++) {
          auto row1_to_be_joined = sorted_rows1[row1_join_idx];
          auto row2_to_be_joined = sorted_rows2[row2_join_idx];
          // Add to new_rows if it reaches here
          // Check for next
          std::vector<std::string> new_row;
          new_row.reserve(n_cols);
          for (const auto& entry : row1_to_be_joined) {
            new_row.emplace_back(entry);
          }
          for (int i = 0; i < (int)row2_to_be_joined.size(); i++) {
            if (common_indexes_second_set.count(i)) {
              continue;
            }
            new_row.emplace_back(row2_to_be_joined.at(i));
          }
          new_rows.push_back(new_row);
        }
      }
      row1_counter = row1_endpoint + 1;
      row2_counter = row2_endpoint + 1;
    }
  }
  return new_rows;
}

RowColumn QResult::HashJoin(
    const QResult& other_result,
    const std::vector<std::pair<int, int>>& common_indexes,
    const std::unordered_set<int>& common_indexes_second_set,
    int n_cols) const {
  RowColumn new_rows;
  std::unordered_map<std::vector<std::string>,
                     std::vector<std::vector<std::string>>, VectorHash>
      key_to_row_column_map;

  // Iterate over smaller amount of rows where possible
  RowColumn hashed_rows, iterate_rows;
  std::vector<int> hashed_key_indexes, iterate_key_indexes;
  hashed_key_indexes.reserve(common_indexes.size());
  iterate_key_indexes.reserve(common_indexes.size());
  if (other_result.GetRows().size() < GetRows().size()) {
    hashed_rows = other_result.GetRows();
    iterate_rows = GetRows();

    for (const auto& [idx, other_idx] : common_indexes) {
      hashed_key_indexes.emplace_back(other_idx);
      iterate_key_indexes.emplace_back(idx);
    }
  } else {
    hashed_rows = GetRows();
    iterate_rows = other_result.GetRows();

    for (const auto& [idx, other_idx] : common_indexes) {
      hashed_key_indexes.emplace_back(idx);
      iterate_key_indexes.emplace_back(other_idx);
    }
  }

  for (const auto& hashed_row : hashed_rows) {
    std::vector<std::string> key;
    key.reserve(hashed_key_indexes.size());
    for (int hashed_key_index : hashed_key_indexes) {
      key.emplace_back(hashed_row[hashed_key_index]);
    }
    if (!key_to_row_column_map.count(key)) {
      key_to_row_column_map[key] = {hashed_row};
    } else {
      key_to_row_column_map[key].emplace_back(hashed_row);
    }
  }

  for (const auto& iterate_row : iterate_rows) {
    std::vector<std::string> key;
    key.reserve(common_indexes.size());
    for (int iterate_key_index : iterate_key_indexes) {
      key.emplace_back(iterate_row[iterate_key_index]);
    }
    if (!key_to_row_column_map.count(key)) {
      continue;
    }
    for (const auto& matched_row : key_to_row_column_map[key]) {
      std::vector<std::string> new_row;
      new_row.reserve(n_cols);
      auto lhs_row = matched_row;
      auto rhs_row = iterate_row;
      // Swap sides based on initial state
      if (other_result.GetRows().size() < GetRows().size()) {
        lhs_row = iterate_row;
        rhs_row = matched_row;
      }
      for (const auto& entry : lhs_row) {
        new_row.emplace_back(entry);
      }
      for (int i = 0; i < (int)rhs_row.size(); i++) {
        if (common_indexes_second_set.count(i)) {
          continue;
        }
        new_row.emplace_back(rhs_row.at(i));
      }
      new_rows.push_back(new_row);
    }
  }
  return new_rows;
}

RowColumn QResult::CrossJoin(const QResult& other_result) const {
  RowColumn new_rows;
  new_rows.reserve(GetRows().size() * other_result.GetRows().size());
  int n_col = GetSynonymsSize() + other_result.GetSynonymsSize();
  for (const auto& row : GetRows()) {
    for (const auto& other_row : other_result.GetRows()) {
      std::vector<std::string> new_row;
      new_row.reserve(n_col);
      for (const auto& entry : row) {
        new_row.emplace_back(entry);
      }
      for (const auto& entry : other_row) {
        new_row.emplace_back(entry);
      }
      new_rows.emplace_back(new_row);
    }
  }
  return new_rows;
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

QResult QResult::Sort(const std::vector<int>& key_indexes) const {
  auto sorted_rows = RowColumn(rows_);
  std::vector<std::pair<int, int>> key_indexes_pair;
  key_indexes_pair.reserve(key_indexes.size());
  for (auto idx : key_indexes) {
    key_indexes_pair.emplace_back(idx, idx);
  }
  std::sort(sorted_rows.begin(), sorted_rows.end(),
            [&key_indexes_pair, this](const auto& a, const auto& b) {
              return this->CompareRow(a, b, key_indexes_pair) == -1;
            });
  return {sorted_rows, synonyms_};
}

int QResult::CompareRow(
    const std::vector<std::string>& row1, const std::vector<std::string>& row2,
    const std::vector<std::pair<int, int>>& key_indexes) const {
  for (auto [idx1, idx2] : key_indexes) {
    // Checks if they are not equivalent
    if (row1[idx1] < row2[idx2]) {
      return -1;
    } else if (row1[idx1] > row2[idx2]) {
      return 1;
    }
  }
  // When all indexes are equal
  return 0;
}
