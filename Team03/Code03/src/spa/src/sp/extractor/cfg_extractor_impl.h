#ifndef SPA_CFG_EXTRACTOR_IMPL_H
#define SPA_CFG_EXTRACTOR_IMPL_H

#include "cfg_extractor.h"
#include "cfg.h"

class CFGExtractorImpl : public CFGExtractor {
 public:
  CFGExtractorImpl();

  [[nodiscard]] CFG Extract(const TNode &ast) const override;
}
#endif  // SPA_CFG_EXTRACTOR_IMPL_H
