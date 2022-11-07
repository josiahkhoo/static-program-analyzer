#include "abstraction_storable_pkb.h"

AbstractionStorablePkb::AbstractionStorablePkb(
    RelationshipManager& relationship_manager_,
    PatternManager& pattern_manager_)
    : relationship_manager_(relationship_manager_),
      pattern_manager_(pattern_manager_) {}

/// Store Follows Abstractions
/// \param abstractions List of abstractions
void AbstractionStorablePkb::Store(
    std::vector<FollowsAbstraction> abstractions) {
  for (const FollowsAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

/// Store FollowsT Abstractions
/// \param abstractions List of abstractions
void AbstractionStorablePkb::Store(
    std::vector<FollowsTAbstraction> abstractions) {
  for (const FollowsTAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

/// Store Parent Abstractions
/// \param abstractions List of abstractions
void AbstractionStorablePkb::Store(
    std::vector<ParentAbstraction> abstractions) {
  for (const ParentAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

/// Store ParentT Abstractions
/// \param abstractions List of abstractions
void AbstractionStorablePkb::Store(
    std::vector<ParentTAbstraction> abstractions) {
  for (const ParentTAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

/// Store Calls Abstractions
/// \param abstractions List of abstractions
void AbstractionStorablePkb::Store(std::vector<CallsAbstraction> abstractions) {
  for (const CallsAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

/// Store CallsT Abstractions
/// \param abstractions List of abstractions
void AbstractionStorablePkb::Store(
    std::vector<CallsTAbstraction> abstractions) {
  for (const CallsTAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

/// Store UsesS Abstractions
/// \param abstractions List of abstractions
void AbstractionStorablePkb::Store(std::vector<UsesSAbstraction> abstractions) {
  for (const UsesSAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

/// Store UsesP Abstractions
/// \param abstractions List of abstractions
void AbstractionStorablePkb::Store(std::vector<UsesPAbstraction> abstractions) {
  for (const UsesPAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

/// Store ModifiesS Abstractions
/// \param abstractions List of abstractions
void AbstractionStorablePkb::Store(
    std::vector<ModifiesSAbstraction> abstractions) {
  for (const ModifiesSAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

/// Store ModifiesP Abstractions
/// \param abstractions List of abstractions
void AbstractionStorablePkb::Store(
    std::vector<ModifiesPAbstraction> abstractions) {
  for (const ModifiesPAbstraction& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}

/// Store While Pattern Abstractions
/// \param abstractions List of abstractions
void AbstractionStorablePkb::Store(
    std::vector<WhilePatternAbstraction> abstractions) {
  for (const WhilePatternAbstraction& abstraction : abstractions) {
    pattern_manager_.AddWhilePattern(abstraction);
  }
}

/// Store If Pattern Abstractions
/// \param abstractions List of abstractions
void AbstractionStorablePkb::Store(
    std::vector<IfPatternAbstraction> abstractions) {
  for (const IfPatternAbstraction& abstraction : abstractions) {
    pattern_manager_.AddIfPattern(abstraction);
  }
}

/// Store CFGs
/// \param abstractions List of Cfgs
void AbstractionStorablePkb::Store(std::vector<CFG> cfgs) {
  for (const CFG& cfg : cfgs) {
    relationship_manager_.AddCFG(cfg);
  }
}
