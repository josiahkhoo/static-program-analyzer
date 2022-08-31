//
// Created by Josiah Khoo on 31/8/22.
//

#ifndef SPA_DESIGN_EXTRACTOR_H
#define SPA_DESIGN_EXTRACTOR_H

#include "design_extractor_result.h"

class DesignExtractor {
 public:
  virtual DesignExtractorResult Extract(TNode ast) const = 0;
};

#endif  // SPA_DESIGN_EXTRACTOR_H
