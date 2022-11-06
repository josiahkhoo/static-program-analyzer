#ifndef SPA_RELATIONSHIP_ABSTRACTION_STORABLE_H
#define SPA_RELATIONSHIP_ABSTRACTION_STORABLE_H

#include "pkb/relationship_store/relationship_manager.h"

class RelationshipAbstractionStorable {
 protected:
  explicit RelationshipAbstractionStorable(
      RelationshipManager &relationship_manager_);
  RelationshipManager &relationship_manager_;
};

#endif  // SPA_RELATIONSHIP_ABSTRACTION_STORABLE_H
