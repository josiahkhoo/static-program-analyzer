#ifndef SPA_STATEMENT_ENTITY_H
#define SPA_STATEMENT_ENTITY_H

#include "common/stringable.h"
#include "entity.h"

/// Represents an entity that contains a statement number.
class StatementEntity : public Entity, public Stringable {
 public:
  /// Constructs a statement entity.
  /// \param node Node reference.
  /// \param statement_number  Statement number.
  StatementEntity(const TNode &node, int statement_number);

  /// Gets statement number.
  /// \return Statement number.
  [[nodiscard]] int GetStatementNumber() const;

  /// Gets string representation of statement number.
  /// \return String representation of statement number.
  [[nodiscard]] std::string ToString() const override;

 protected:
  int statement_number_;
};

#endif  // SPA_STATEMENT_ENTITY_H
