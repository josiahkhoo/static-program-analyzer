#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_Q_RESULT_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_Q_RESULT_H_

#include <vector>

#include "common/reference/synonym.h"

/// The QResult is designed like a table. The synonyms represent the column
/// names while the rows represent the rows.
/// E.g. Synonym = {a1, a2} / Rows = {{1,2}, {1,3}, {2,3}}
class QResult {
 public:
  QResult(std::vector<std::vector<std::string>> rows,
          std::vector<Synonym> synonyms);
  [[nodiscard]] std::vector<std::vector<std::string>> GetRows() const;
  [[nodiscard]] std::vector<Synonym> GetSynonyms() const;

  /// Get rows operation.
  /// \param synonyms Only retrieve rows from specified synonyms.
  /// \return Unique rows.
  [[nodiscard]] std::vector<std::vector<std::string>> GetRows(
      const std::vector<Synonym>& synonyms) const;

  /// Joins a separate result with the current result and returns a new result.
  /// Things join considers:
  /// <br/>1. Whether or not different synonyms have the same type (exclusive)
  /// <br/>2. Whether or not there are common synonyms (inclusive merge)
  /// \param other_result Other result to join with.
  /// \return New result set.
  [[nodiscard]] QResult Join(const QResult& other_result) const;

  /// Intersects a separate result with the current result and returns a new
  /// result.
  /// !Warning: Only works if they have the same synonyms.
  /// \param other_result Other result to intersect with.
  /// \return New result set.
  [[nodiscard]] QResult Intersect(const QResult& other_result) const;
  bool operator==(const QResult& rhs) const;
  bool operator!=(const QResult& rhs) const;

 private:
  std::vector<std::vector<std::string>> rows_;
  std::vector<Synonym> synonyms_;

  struct VectorHash {
    size_t operator()(const std::vector<std::string>& v) const {
      std::hash<std::string> hasher;
      size_t seed = 0;
      for (const auto& str : v) {
        seed ^= hasher(str) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      }
      return seed;
    }
  };
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_QPS_QNODES_Q_RESULT_H_
