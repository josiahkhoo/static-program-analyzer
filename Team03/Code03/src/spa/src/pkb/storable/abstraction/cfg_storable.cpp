//
// Created by kohha on 5/11/2022.
//

#include "cfg_storable.h"

CfgStorable::CfgStorable() = default;

/// Store CFGs
/// \param abstractions List of Cfgs
void CfgStorable::Store(std::vector<CFG> cfgs) {
  for (const CFG& cfg : cfgs) {
    relationship_manager_.AddCFG(cfg);
  }
}
