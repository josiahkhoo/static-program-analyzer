#ifndef SPA_DESIGN_EXTRACTOR_IMPL_H
#define SPA_DESIGN_EXTRACTOR_IMPL_H

#include <unordered_map>

#include "abstraction_extractor_impl.h"
#include "common/t_node.h"
#include "design_extractor.h"
#include "design_extractor_result.h"
#include "entity_extractor_impl.h"

class DesignExtractorImpl : public DesignExtractor {
public:
    DesignExtractorImpl(const EntityExtractor &entity_extractor,
                        const AbstractionExtractor &abstraction_extractor);

    [[nodiscard]] DesignExtractorResult Extract(TNode ast) const override;

public:
private:
    const EntityExtractor &entity_extractor_;
    const AbstractionExtractor &abstraction_extractor_;
};

#endif  // SPA_DESIGN_EXTRACTOR_IMPL_H
