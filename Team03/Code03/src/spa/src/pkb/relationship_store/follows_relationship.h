#ifndef SPA_FOLLOWS_RELATIONSHIP_H
#define SPA_FOLLOWS_RELATIONSHIP_H

#include "common/stringable.h"

class FollowsRelationship : public Stringable {
public:
  explicit FollowsRelationship(int follows_statement_number_, int follow_by_statement_number_);

  [[nodiscard]] int GetFollows() const;

  [[nodiscard]] int GetFollowBy() const;

  //need to string method?
  //[[nodiscard]] std::string ToString() const override;

private:
  int follows_statement_number_;
  int follow_by_statement_number_;
};

#endif  // SPA_FOLLOWS_ABSTRACTION_H
