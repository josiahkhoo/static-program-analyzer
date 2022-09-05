#include "design_extractor_result.h"

#include <utility>

DesignExtractorResult::DesignExtractorResult(
    AbstractionExtractorResult abstraction_extractor_result,
    EntityExtractorResult entity_extractor_result)
    : abstraction_extractor_result_(std::move(abstraction_extractor_result)),
      entity_extractor_result_(std::move(entity_extractor_result)) {}

AbstractionExtractorResult
DesignExtractorResult::GetAbstractionExtractorResult() const {
  return abstraction_extractor_result_;
}

EntityExtractorResult DesignExtractorResult::GetEntityExtractorResult() const {
  return entity_extractor_result_;
}
