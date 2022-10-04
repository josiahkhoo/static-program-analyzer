#ifndef SPA_CFG_EXTRACTOR_IMPL_H
#define SPA_CFG_EXTRACTOR_IMPL_H

#include "cfg.h"
#include "cfg_extractor.h"

class CFGExtractorImpl : public CFGExtractor {
 public:
  CFGExtractorImpl();

  [[nodiscard]] std::vector<CFG> Extract(const TNode &ast) const override;

 private:
  [[nodiscard]] CFG CreateCFG(const TNode &node) const;
};
#endif  // SPA_CFG_EXTRACTOR_IMPL_H
