#ifndef SPA_CFG_EXTRACTOR_H
#define SPA_CFG_EXTRACTOR_H

#include <memory>

#include "cfg.h"
#include "common/cfg_node.h"
#include "common/t_node.h"

class CFGExtractor {
 public:
  virtual CFG Extract(const TNode &ast) const = 0;
};
#endif  // SPA_CFG_EXTRACTOR_H
