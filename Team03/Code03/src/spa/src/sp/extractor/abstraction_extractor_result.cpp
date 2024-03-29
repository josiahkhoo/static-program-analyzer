#include "abstraction_extractor_result.h"

#include <utility>

#include "common/abstraction/calls_abstraction.h"
#include "common/abstraction/calls_t_abstraction.h"

AbstractionExtractorResult::AbstractionExtractorResult(
    std::vector<FollowsAbstraction> follows_abstractions,
    std::vector<FollowsTAbstraction> follows_t_abstractions,
    std::vector<ParentAbstraction> parent_abstractions,
    std::vector<ParentTAbstraction> parent_t_abstractions,
    std::vector<CallsAbstraction> calls_abstractions,
    std::vector<CallsTAbstraction> calls_t_abstractions,
    std::vector<UsesSAbstraction> uses_s_abstractions,
    std::vector<UsesPAbstraction> uses_p_abstractions,
    std::vector<ModifiesSAbstraction> modifies_s_abstractions,
    std::vector<ModifiesPAbstraction> modifies_p_abstractions,
    std::vector<IfPatternAbstraction> if_pattern_abstractions,
    std::vector<WhilePatternAbstraction> while_pattern_abstractions)
    : follows_abstractions_(std::move(follows_abstractions)),
      follows_t_abstractions_(std::move(follows_t_abstractions)),
      parent_abstractions_(std::move(parent_abstractions)),
      parent_t_abstractions_(std::move(parent_t_abstractions)),
      calls_abstractions_(std::move(calls_abstractions)),
      calls_t_abstractions_(std::move(calls_t_abstractions)),
      uses_s_abstractions_(std::move(uses_s_abstractions)),
      uses_p_abstractions_(std::move(uses_p_abstractions)),
      modifies_s_abstractions_(std::move(modifies_s_abstractions)),
      modifies_p_abstractions_(std::move(modifies_p_abstractions)),
      if_pattern_abstractions_(std::move(if_pattern_abstractions)),
      while_pattern_abstractions_(std::move(while_pattern_abstractions)) {}

std::vector<FollowsAbstraction>
AbstractionExtractorResult::GetFollowsAbstractions() const {
  return follows_abstractions_;
}

std::vector<FollowsTAbstraction>
AbstractionExtractorResult::GetFollowsTAbstractions() const {
  return follows_t_abstractions_;
}

std::vector<ParentAbstraction>
AbstractionExtractorResult::GetParentAbstractions() const {
  return parent_abstractions_;
}

std::vector<ParentTAbstraction>
AbstractionExtractorResult::GetParentTAbstractions() const {
  return parent_t_abstractions_;
}

std::vector<CallsAbstraction> AbstractionExtractorResult::GetCallsAbstractions()
    const {
  return calls_abstractions_;
}

std::vector<CallsTAbstraction>
AbstractionExtractorResult::GetCallsTAbstractions() const {
  return calls_t_abstractions_;
}

std::vector<UsesSAbstraction> AbstractionExtractorResult::GetUsesSAbstractions()
    const {
  return uses_s_abstractions_;
}

std::vector<UsesPAbstraction> AbstractionExtractorResult::GetUsesPAbstractions()
    const {
  return uses_p_abstractions_;
}

std::vector<ModifiesSAbstraction>
AbstractionExtractorResult::GetModifiesSAbstractions() const {
  return modifies_s_abstractions_;
}

std::vector<ModifiesPAbstraction>
AbstractionExtractorResult::GetModifiesPAbstractions() const {
  return modifies_p_abstractions_;
}

std::vector<IfPatternAbstraction>
AbstractionExtractorResult::GetIfPatternAbstractions() const {
  return if_pattern_abstractions_;
}

std::vector<WhilePatternAbstraction>
AbstractionExtractorResult::GetWhilePatternAbstractions() const {
  return while_pattern_abstractions_;
}

bool AbstractionExtractorResult::operator==(
    const AbstractionExtractorResult &rhs) const {
  return follows_abstractions_ == rhs.follows_abstractions_ &&
         follows_t_abstractions_ == rhs.follows_t_abstractions_ &&
         parent_abstractions_ == rhs.parent_abstractions_ &&
         parent_t_abstractions_ == rhs.parent_t_abstractions_ &&
         calls_abstractions_ == rhs.calls_abstractions_ &&
         calls_t_abstractions_ == rhs.calls_t_abstractions_ &&
         uses_s_abstractions_ == rhs.uses_s_abstractions_ &&
         uses_p_abstractions_ == rhs.uses_p_abstractions_ &&
         modifies_s_abstractions_ == rhs.modifies_s_abstractions_ &&
         modifies_p_abstractions_ == rhs.modifies_p_abstractions_;
}

bool AbstractionExtractorResult::operator!=(
    const AbstractionExtractorResult &rhs) const {
  return !(rhs == *this);
}

AbstractionExtractorResult::Builder::Builder() = default;

AbstractionExtractorResult::Builder
AbstractionExtractorResult::Builder::FollowsAbstractions(
    std::vector<FollowsAbstraction> *follows_abstractions) {
  follows_abstractions_ = follows_abstractions;
  return *this;
}

AbstractionExtractorResult::Builder
AbstractionExtractorResult::Builder::FollowsTAbstractions(
    std::vector<FollowsTAbstraction> *follows_t_abstractions) {
  follows_t_abstractions_ = follows_t_abstractions;
  return *this;
}

AbstractionExtractorResult::Builder
AbstractionExtractorResult::Builder::ParentAbstractions(
    std::vector<ParentAbstraction> *parent_abstractions) {
  parent_abstractions_ = parent_abstractions;
  return *this;
}

AbstractionExtractorResult::Builder
AbstractionExtractorResult::Builder::ParentTAbstractions(
    std::vector<ParentTAbstraction> *parent_t_abstractions) {
  parent_t_abstractions_ = parent_t_abstractions;
  return *this;
}

AbstractionExtractorResult::Builder
AbstractionExtractorResult::Builder::CallsAbstractions(
    std::vector<CallsAbstraction> *calls_abstractions) {
  calls_abstractions_ = calls_abstractions;
  return *this;
}

AbstractionExtractorResult::Builder
AbstractionExtractorResult::Builder::CallsTAbstractions(
    std::vector<CallsTAbstraction> *calls_t_abstractions) {
  calls_t_abstractions_ = calls_t_abstractions;
  return *this;
}

AbstractionExtractorResult::Builder
AbstractionExtractorResult::Builder::UsesSAbstractions(
    std::vector<UsesSAbstraction> *uses_s_abstractions) {
  uses_s_abstractions_ = uses_s_abstractions;
  return *this;
}

AbstractionExtractorResult::Builder
AbstractionExtractorResult::Builder::UsesPAbstractions(
    std::vector<UsesPAbstraction> *uses_p_abstractions) {
  uses_p_abstractions_ = uses_p_abstractions;
  return *this;
}

AbstractionExtractorResult::Builder
AbstractionExtractorResult::Builder::ModifiesSAbstractions(
    std::vector<ModifiesSAbstraction> *modifies_s_abstractions) {
  modifies_s_abstractions_ = modifies_s_abstractions;
  return *this;
}

AbstractionExtractorResult::Builder
AbstractionExtractorResult::Builder::ModifiesPAbstractions(
    std::vector<ModifiesPAbstraction> *modifies_p_abstractions) {
  modifies_p_abstractions_ = modifies_p_abstractions;
  return *this;
}

AbstractionExtractorResult::Builder
AbstractionExtractorResult::Builder::IfPatternAbstractions(
    std::vector<IfPatternAbstraction> *if_pattern_abstractions) {
  if_pattern_abstractions_ = if_pattern_abstractions;
  return *this;
}

AbstractionExtractorResult::Builder
AbstractionExtractorResult::Builder::WhilePatternAbstractions(
    std::vector<WhilePatternAbstraction> *while_pattern_abstractions) {
  while_pattern_abstractions_ = while_pattern_abstractions;
  return *this;
}

AbstractionExtractorResult AbstractionExtractorResult::Builder::Build() {
  return {*follows_abstractions_,    *follows_t_abstractions_,
          *parent_abstractions_,     *parent_t_abstractions_,
          *calls_abstractions_,      *calls_t_abstractions_,
          *uses_s_abstractions_,     *uses_p_abstractions_,
          *modifies_s_abstractions_, *modifies_p_abstractions_,
          *if_pattern_abstractions_, *while_pattern_abstractions_};
}
