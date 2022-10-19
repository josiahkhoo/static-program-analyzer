#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_Q_RESULT_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_Q_RESULT_H_

#include <unordered_set>
#include <vector>

#include "common/reference/synonym.h"

typedef std::vector<std::vector<std::string>> RowColumn;

/// The QResult is designed like a table. The synonyms represent the column
/// names while the rows represent the rows.
/// E.g. Synonym = {a1, a2} / Rows = {{1,2}, {1,3}, {2,3}}
class QResult {
 public:
  /// Instantiates a QResult that has been queried on before.
  QResult(RowColumn rows, std::vector<Synonym> synonyms);

  /// Instantiates an empty QResult and set a flag whether it has been queried
  /// on or not.
  explicit QResult(bool has_been_queried);

  [[nodiscard]] RowColumn GetRows() const;
  [[nodiscard]] std::vector<Synonym> GetSynonyms() const;
  [[nodiscard]] bool HasBeenQueried() const;

  /// Get rows operation.
  /// \param synonyms Only retrieve rows from specified synonyms.
  /// \return Unique rows.
  [[nodiscard]] RowColumn GetRows(const std::vector<Synonym>& synonyms) const;

  /// Joins a separate result with the current result and returns a new result.
  /// Things join considers:
  /// <br/>1. Whether or not different synonyms have the same type (exclusive)
  /// <br/>2. Whether or not there are common synonyms (inclusive merge)
  /// \param other_result Other result to join with.
  /// \return New result set.
  [[nodiscard]] QResult Join(const QResult& other_result);

  /// Intersects a separate result with the current result and returns a new
  /// result.
  /// !Warning: Only works if they have the same synonyms.
  /// \param other_result Other result to intersect with.
  /// \return New result set.
  [[nodiscard]] QResult Intersect(const QResult& other_result) const;

  [[nodiscard]] QResult Sort(const std::vector<int>& key_indexes) const;

  bool operator==(const QResult& rhs) const;

  bool operator!=(const QResult& rhs) const;

 private:
  RowColumn rows_;
  std::vector<Synonym> synonyms_;
  bool has_been_queried_;

  struct VectorHash {
    long long operator()(const std::vector<std::string>& v) const {
      int prime = 31;
      long long mod = 1e9 + 9;
      long long hash = 0;
      for (auto s : v) {
        long long string_hash{};
        long long pow = 1;
        for (int i = 0; i < (int)s.length(); ++i) {
          string_hash = (string_hash + (s[i] - '0' + 1) * pow) % mod;
          pow = (prime * pow) % mod;
        }
        hash = (hash + string_hash + (prime * hash) % mod) % mod;
      }
      return hash;
    }
  };

  [[nodiscard]] int GetSynonymsSize() const;
  [[nodiscard]] bool IsSynonymsEmpty() const;
  [[nodiscard]] Synonym GetSynonymAt(int index) const;
  [[nodiscard]] int CompareRow(
      const std::vector<std::string>& row1,
      const std::vector<std::string>& row2,
      const std::vector<std::pair<int, int>>& key_indexes) const;
  [[nodiscard]] std::vector<Synonym> GenerateSynonymList(
      const QResult& other_result,
      const std::vector<std::pair<int, int>>& common_indexes,
      const std::unordered_set<int>& common_indexes_second_set) const;
  [[nodiscard]] RowColumn SortMergeJoin(
      const QResult& other_result,
      const std::vector<std::pair<int, int>>& common_indexes,
      const std::unordered_set<int>& common_indexes_second_set,
      int n_cols) const;
  [[nodiscard]] RowColumn HashJoin(
      const QResult& other_result,
      const std::vector<std::pair<int, int>>& common_indexes,
      const std::unordered_set<int>& common_indexes_second_set,
      int n_cols) const;
  [[nodiscard]] RowColumn CrossJoin(const QResult& other_result) const;
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_Q_RESULT_H_
