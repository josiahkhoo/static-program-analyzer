#ifndef SPA_CFG_EXTRACTOR_H
#define SPA_CFG_EXTRACTOR_H

#include <memory>

#include "common/cfg_node.h"
#include "common/t_node.h"
#include "cfg.h"

class CFGExtractor {
 public:
  virtual CFG Extract(const TNode &ast) const = 0;
};
#endif  // SPA_CFG_EXTRACTOR_H
