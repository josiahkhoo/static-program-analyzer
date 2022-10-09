#ifndef SPA_MODIFIES_ABSTRACTION_EXTRACTOR_H
#define SPA_MODIFIES_ABSTRACTION_EXTRACTOR_H

#include "common/abstraction/modifies_p_abstraction.h"
#include "common/abstraction/modifies_s_abstraction.h"
#include "sp/extractor/bi_sub_abstraction_extractor.h"

class ModifiesAbstractionExtractor
    : public BiSubAbstractionExtractor<ModifiesSAbstraction,
                                       ModifiesPAbstraction> {
 public:
  [[nodiscard]] virtual std::pair<std::vector<ModifiesSAbstraction>,
                                  std::vector<ModifiesPAbstraction>>
  Extract(const SubAbstractionExtractorContext& context) const = 0;
};

#endif  // SPA_MODIFIES_ABSTRACTION_EXTRACTOR_H
