//
// Created by kohha on 4/11/2022.
//

#include "pkb/storable/abstraction/calls_storable.h"
#include "pkb/storable/abstraction/calls_t_storable.h"
#include "pkb/storable/abstraction/cfg_storable.h"
#include "pkb/storable/abstraction/follows_storable.h"
#include "pkb/storable/abstraction/follows_t_storable.h"
#include "pkb/storable/abstraction/if_pattern_storable.h"
#include "pkb/storable/abstraction/modifies_p_storable.h"
#include "pkb/storable/abstraction/modifies_s_storable.h"
#include "pkb/storable/abstraction/parent_storable.h"
#include "pkb/storable/abstraction/parent_t_storable.h"
#include "pkb/storable/abstraction/uses_p_storable.h"
#include "pkb/storable/abstraction/uses_s_storable.h"
#include "pkb/storable/abstraction/while_pattern_storable.h"

#ifndef SPA_RELATIONSHIP_STORABLE_PKB_STRATEGY_H
#define SPA_RELATIONSHIP_STORABLE_PKB_STRATEGY_H

class AbstractionStorablePkb {
 public:
  AbstractionStorablePkb(RelationshipManager &relationship_manager_, PatternManager &pattern_manager_);

  [[nodiscard]] FollowsStorable GetFollowsStorable() const;

  [[nodiscard]] FollowsTStorable GetFollowsTStorable() const;

  [[nodiscard]] ParentStorable GetParentStorable() const;

  [[nodiscard]] ParentTStorable GetParentTStorable() const;

  [[nodiscard]] ModifiesPStorable GetModifiesPStorable() const;

  [[nodiscard]] ModifiesSStorable GetModifiesSStorable() const;

  [[nodiscard]] UsesPStorable GetUsesPStorable() const;

  [[nodiscard]] UsesSStorable GetUsesSStorable() const;

  [[nodiscard]] CallsStorable GetCallsStorable() const;

  [[nodiscard]] CallsTStorable GetCallsTStorable() const;

  [[nodiscard]] IfPatternStorable GetIfPatternStorable() const;

  [[nodiscard]] WhilePatternStorable GetWhilePatternStorable() const;

  [[nodiscard]] CfgStorable GetCfgStorable() const;

 private:
  FollowsStorable follows_storable_;
  FollowsTStorable follows_t_storable_;
  ParentStorable parent_storable_;
  ParentTStorable parent_t_storable_;
  ModifiesPStorable modifies_p_storable_;
  ModifiesSStorable modifies_s_storable_;
  UsesPStorable uses_s_storable_;
  UsesSStorable uses_p_storable_;
  CallsStorable calls_storable_;
  CallsTStorable calls_t_storable_;
  IfPatternStorable if_pattern_storable_;
  WhilePatternStorable while_pattern_storable_;
  CfgStorable cfg_storable_;

};

#endif  // SPA_RELATIONSHIP_STORABLE_PKB_STRATEGY_H
