//
// Created by kohha on 4/11/2022.
//

#include "abstraction_storable_pkb_strategy.h"

template<class T>
void AbstractionStorablePkb<T>::Store(std::vector<T> abstractions) {
  for (const T& abstraction : abstractions) {
    relationship_manager_.AddAbstraction(abstraction);
  }
}
//
///// Store Follows Abstractions
///// \param abstractions List of abstractions
//template<>
//void AbstractionStorablePkb<FollowsAbstraction>::Store(std::vector<FollowsAbstraction> abstractions) {
//  for (const FollowsAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store FollowsT Abstractions
///// \param abstractions List of abstractions
//template<>
//void AbstractionStorablePkb<FollowsTAbstraction>::Store(std::vector<FollowsTAbstraction> abstractions) {
//  for (const FollowsTAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store Parent Abstractions
///// \param abstractions List of abstractions
//template<>
//void AbstractionStorablePkb<ParentAbstraction>::Store(std::vector<ParentAbstraction> abstractions) {
//  for (const ParentAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store ParentT Abstractions
///// \param abstractions List of abstractions
//template<>
//void AbstractionStorablePkb<ParentTAbstraction>::Store(std::vector<ParentTAbstraction> abstractions) {
//  for (const ParentTAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store Calls Abstractions
///// \param abstractions List of abstractions
//template<>
//void AbstractionStorablePkb<CallsAbstraction>::Store(std::vector<CallsAbstraction> abstractions) {
//  for (const CallsAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store CallsT Abstractions
///// \param abstractions List of abstractions
//template<>
//void AbstractionStorablePkb<CallsTAbstraction>::Store(std::vector<CallsTAbstraction> abstractions) {
//  for (const CallsTAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store UsesS Abstractions
///// \param abstractions List of abstractions
//template<>
//void AbstractionStorablePkb<UsesSAbstraction>::Store(std::vector<UsesSAbstraction> abstractions) {
//  for (const UsesSAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store UsesP Abstractions
///// \param abstractions List of abstractions
//template<>
//void AbstractionStorablePkb<UsesPAbstraction>::Store(std::vector<UsesPAbstraction> abstractions) {
//  for (const UsesPAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store ModifiesS Abstractions
///// \param abstractions List of abstractions
//template<>
//void AbstractionStorablePkb<ModifiesSAbstraction>::Store(std::vector<ModifiesSAbstraction> abstractions) {
//  for (const ModifiesSAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//
///// Store ModifiesP Abstractions
///// \param abstractions List of abstractions
//template<>
//void AbstractionStorablePkb<ModifiesPAbstraction>::Store(std::vector<ModifiesPAbstraction> abstractions) {
//  for (const ModifiesPAbstraction& abstraction : abstractions) {
//    relationship_manager_.AddAbstraction(abstraction);
//  }
//}
//

/// Store While Pattern Abstractions
/// \param abstractions List of abstractions
template<>
void AbstractionStorablePkb<WhilePatternAbstraction>::Store(std::vector<WhilePatternAbstraction> abstractions) {
  for (const WhilePatternAbstraction& abstraction : abstractions) {
    pattern_manager_.AddWhilePattern(abstraction);
  }
}

/// Store If Pattern Abstractions
/// \param abstractions List of abstractions
template<>
void AbstractionStorablePkb<IfPatternAbstraction>::Store(std::vector<IfPatternAbstraction> abstractions) {
  for (const IfPatternAbstraction& abstraction : abstractions) {
    pattern_manager_.AddIfPattern(abstraction);
  }
}

/// Store CFGs
/// \param abstractions List of Cfgs
template<>
void AbstractionStorablePkb<CFG>::Store(std::vector<CFG> cfgs) {
  for (const CFG& cfg : cfgs) {
    relationship_manager_.AddCFG(cfg);
  }
}