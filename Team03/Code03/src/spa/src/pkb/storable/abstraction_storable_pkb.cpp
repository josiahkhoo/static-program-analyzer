//
// Created by kohha on 4/11/2022.
//

#include "abstraction_storable_pkb.h"

AbstractionStorablePkb::AbstractionStorablePkb(
    RelationshipManager& relationship_manager_,
    PatternManager& pattern_manager_)
    : follows_storable_(FollowsStorable(relationship_manager_)),
      follows_t_storable_(FollowsTStorable(relationship_manager_)),
      parent_storable_(ParentStorable(relationship_manager_)),
      parent_t_storable_(ParentTStorable(relationship_manager_)),
      modifies_p_storable_(ModifiesPStorable(relationship_manager_)),
      modifies_s_storable_(ModifiesSStorable(relationship_manager_)),
      uses_s_storable_(UsesPStorable(relationship_manager_)),
      uses_p_storable_(UsesSStorable(relationship_manager_)),
      calls_storable_(CallsStorable(relationship_manager_)),
      calls_t_storable_(CallsTStorable(relationship_manager_)),
      if_pattern_storable_(IfPatternStorable(pattern_manager_)),
      while_pattern_storable_(WhilePatternStorable(pattern_manager_)),
      cfg_storable_(CfgStorable(relationship_manager_)) {}

/// Get FollowsStorable
/// \return FollowsStorable
FollowsStorable AbstractionStorablePkb::GetFollowsStorable() const {
  return follows_storable_;
}

/// Get FollowsTStorable
/// \return FollowsTStorable
FollowsTStorable AbstractionStorablePkb::GetFollowsTStorable() const {
  return follows_t_storable_;
}

/// Get ParentStorable
/// \return ParentStorable
ParentStorable AbstractionStorablePkb::GetParentStorable() const {
  return parent_storable_;
}

/// Get ParentTStorable
/// \return ParentTStorable
ParentTStorable AbstractionStorablePkb::GetParentTStorable() const {
  return parent_t_storable_;
}

/// Get ModifiesPStorable
/// \return ModifiesPStorable
ModifiesPStorable AbstractionStorablePkb::GetModifiesPStorable() const {
  return modifies_p_storable_;
}

/// Get ModifiesSStorable
/// \return ModifiesSStorable
ModifiesSStorable AbstractionStorablePkb::GetModifiesSStorable() const {
  return modifies_s_storable_;
}

/// Get UsesPStorable
/// \return UsesPStorable
UsesPStorable AbstractionStorablePkb::GetUsesPStorable() const {
  return uses_s_storable_;
}

/// Get UsesSStorable
/// \return UsesSStorable
UsesSStorable AbstractionStorablePkb::GetUsesSStorable() const {
  return uses_p_storable_;
}

/// Get CallsStorable
/// \return CallsStorable
CallsStorable AbstractionStorablePkb::GetCallsStorable() const {
  return calls_storable_;
}

/// Get CallsTStorable
/// \return CallsTStorable
CallsTStorable AbstractionStorablePkb::GetCallsTStorable() const {
  return calls_t_storable_;
}

/// Get IfPatternStorable
/// \return IfPatternStorable
IfPatternStorable AbstractionStorablePkb::GetIfPatternStorable() const {
  return if_pattern_storable_;
}

/// Get WhilePatternStorable
/// \return WhilePatternStorable
WhilePatternStorable AbstractionStorablePkb::GetWhilePatternStorable() const {
  return while_pattern_storable_;
}

/// Get CfgStorable
/// \return CfgStorable
CfgStorable AbstractionStorablePkb::GetCfgStorable() const {
  return cfg_storable_;
}