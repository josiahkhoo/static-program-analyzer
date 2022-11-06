//
// Created by kohha on 4/11/2022.
//

#include "pkb/impl/storable/abstraction/calls_storable.h"
#include "pkb/impl/storable/abstraction/calls_t_storable.h"
#include "pkb/impl/storable/abstraction/cfg_storable.h"
#include "pkb/impl/storable/abstraction/follows_storable.h"
#include "pkb/impl/storable/abstraction/follows_t_storable.h"
#include "pkb/impl/storable/abstraction/if_pattern_storable.h"
#include "pkb/impl/storable/abstraction/modifies_p_storable.h"
#include "pkb/impl/storable/abstraction/modifies_s_storable.h"
#include "pkb/impl/storable/abstraction/parent_storable.h"
#include "pkb/impl/storable/abstraction/parent_t_storable.h"
#include "pkb/impl/storable/abstraction/uses_p_storable.h"
#include "pkb/impl/storable/abstraction/uses_s_storable.h"
#include "pkb/impl/storable/abstraction/while_pattern_storable.h"

#ifndef SPA_RELATIONSHIP_STORABLE_PKB_STRATEGY_H
#define SPA_RELATIONSHIP_STORABLE_PKB_STRATEGY_H

class AbstractionStorablePkb {
 public:
  AbstractionStorablePkb(RelationshipManager& relationship_manager_,
                         PatternManager& pattern_manager_);

  [[nodiscard]] FollowsStorable& GetFollowsStorable();

  [[nodiscard]] FollowsTStorable& GetFollowsTStorable();

  [[nodiscard]] ParentStorable& GetParentStorable();

  [[nodiscard]] ParentTStorable& GetParentTStorable();

  [[nodiscard]] ModifiesPStorable& GetModifiesPStorable();

  [[nodiscard]] ModifiesSStorable& GetModifiesSStorable();

  [[nodiscard]] UsesPStorable& GetUsesPStorable();

  [[nodiscard]] UsesSStorable& GetUsesSStorable();

  [[nodiscard]] CallsStorable& GetCallsStorable();

  [[nodiscard]] CallsTStorable& GetCallsTStorable();

  [[nodiscard]] IfPatternStorable& GetIfPatternStorable();

  [[nodiscard]] WhilePatternStorable& GetWhilePatternStorable();

  [[nodiscard]] CfgStorable& GetCfgStorable();

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
