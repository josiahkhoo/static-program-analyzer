#ifndef SPA_TEAM03_CODE03_SRC_SPA_SRC_COMMON_ENTITY_PATTERN_STATEMENT_ENTITY_H_
#define SPA_TEAM03_CODE03_SRC_SPA_SRC_COMMON_ENTITY_PATTERN_STATEMENT_ENTITY_H_

#include "statement_entity.h"

class PatternStatementEntity : public StatementEntity {
 public:
  /// Constructs a pattern statement entity.
  /// \param node Reference to TNode.
  /// \param statement_number Statement number.
  PatternStatementEntity(const TNode& node, int statement_number);

  /// Retrieves the left hand side string pattern.
  /// \return String representation.
  [[nodiscard]] std::string GetLeftHandSidePattern() const;

  /// Recursively retrieves the right hand side string pattern.
  /// !Warning: This can be computationally expensive because of the traversal.
  /// \return String representation.
  [[nodiscard]] std::string GetRightHandSidePattern() const;

 private:
  std::string RecursivelyFlatten(const TNode& node) const;
};

#endif  // SPA_TEAM03_CODE03_SRC_SPA_SRC_COMMON_ENTITY_PATTERN_STATEMENT_ENTITY_H_
