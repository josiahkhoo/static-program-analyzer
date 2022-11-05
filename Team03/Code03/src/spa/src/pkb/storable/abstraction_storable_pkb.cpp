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
FollowsStorable& AbstractionStorablePkb::GetFollowsStorable() {
  return follows_storable_;
}

/// Get FollowsTStorable
/// \return FollowsTStorable
FollowsTStorable& AbstractionStorablePkb::GetFollowsTStorable() {
  return follows_t_storable_;
}

/// Get ParentStorable
/// \return ParentStorable
ParentStorable& AbstractionStorablePkb::GetParentStorable() {
  return parent_storable_;
}

/// Get ParentTStorable
/// \return ParentTStorable
ParentTStorable& AbstractionStorablePkb::GetParentTStorable() {
  return parent_t_storable_;
}

/// Get ModifiesPStorable
/// \return ModifiesPStorable
ModifiesPStorable& AbstractionStorablePkb::GetModifiesPStorable() {
  return modifies_p_storable_;
}

/// Get ModifiesSStorable
/// \return ModifiesSStorable
ModifiesSStorable& AbstractionStorablePkb::GetModifiesSStorable() {
  return modifies_s_storable_;
}

/// Get UsesPStorable
/// \return UsesPStorable
UsesPStorable& AbstractionStorablePkb::GetUsesPStorable() {
  return uses_s_storable_;
}

/// Get UsesSStorable
/// \return UsesSStorable
UsesSStorable& AbstractionStorablePkb::GetUsesSStorable() {
  return uses_p_storable_;
}

/// Get CallsStorable
/// \return CallsStorable
CallsStorable& AbstractionStorablePkb::GetCallsStorable() {
  return calls_storable_;
}

/// Get CallsTStorable
/// \return CallsTStorable
CallsTStorable& AbstractionStorablePkb::GetCallsTStorable() {
  return calls_t_storable_;
}

/// Get IfPatternStorable
/// \return IfPatternStorable
IfPatternStorable& AbstractionStorablePkb::GetIfPatternStorable() {
  return if_pattern_storable_;
}

/// Get WhilePatternStorable
/// \return WhilePatternStorable
WhilePatternStorable& AbstractionStorablePkb::GetWhilePatternStorable() {
  return while_pattern_storable_;
}

/// Get CfgStorable
/// \return CfgStorable
CfgStorable& AbstractionStorablePkb::GetCfgStorable() {
  return cfg_storable_;
}